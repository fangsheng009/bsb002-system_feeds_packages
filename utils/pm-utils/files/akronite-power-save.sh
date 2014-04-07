#!/bin/sh

ac_power()
{
	echo "Entering AC-Power Mode"
# Krait Power-UP Sequence
	/etc/init.d/powerctl restart

# Clocks Power-UP Sequence
	echo 400000000 > /sys/kernel/debug/clk/afab_a_clk/rate
	echo 64000000 > /sys/kernel/debug/clk/dfab_a_clk/rate
	echo 64000000 > /sys/kernel/debug/clk/sfpb_a_clk/rate
	echo 64000000 > /sys/kernel/debug/clk/cfpb_a_clk/rate
	echo 400000000 > /sys/kernel/debug/clk/nssfab0_a_clk/rate
	echo 200000000 > /sys/kernel/debug/clk/nssfab1_a_clk/rate
	echo 400000000 > /sys/kernel/debug/clk/ebi1_a_clk/rate

# Enabling Auto scale on NSS cores
	echo 1 > /proc/sys/dev/nss/clock/auto_scale

# PCIe Power-UP Sequence
	echo 1 > /sys/bus/pci/rcrescan
	sleep 2
	echo 1 > /sys/bus/pci/rescan

# NSS Power-UP Sequence

# Load connection manager module
	[ -d /sys/module/qca_nss_connmgr_ipv4 ] || insmod qca-nss-connmgr-ipv4
	sleep 1
	[ -d /sys/module/qca_nss_connmgr_ipv6 ] || insmod qca-nss-connmgr-ipv6

# Bringing Up LAN Interface
	ifup lan

# Wifi power up sequence
	wifi up


# Sata Power-UP Sequence
	echo "0"> /sys/devices/platform/msm_sata.0/ahci.0/sata_suspend
	sleep 1
	echo "- - -" > /sys/class/scsi_host/host0/scan

# USB Power-UP Sequence
	[ -d /sys/module/dwc3_ipq ] || insmod dwc3-ipq

	exit 0
}

battery_power()
{
	echo "Entering Battery Mode..."

# Wifi Power-down Sequence
	wifi down

# NSS Power-down Sequence

# Bringing Down LAN Interface
	ifdown lan

# Stop and Unload connection manager module

	[ -d /sys/module/qca_nss_connmgr_ipv6 ] && {
		echo 1 > /sys/nom_v6/stop
		sleep 1
		echo f > /proc/net/nf_conntrack
		sleep 3
		echo 1 > /sys/nom_v6/terminate
		sleep 2
		rmmod qca_nss_connmgr_ipv6
	}

	[ -d /sys/module/qca_nss_connmgr_ipv4 ] && {
		echo 1 > /sys/nom_v4/stop
		sleep 1
		echo f > /proc/net/nf_conntrack
		sleep 3
		echo 1 > /sys/nom_v4/terminate
		sleep 2
		rmmod qca_nss_connmgr_ipv4
	}

# Scaling Down UBI Cores
	echo 110000000 > /proc/sys/dev/nss/clock/current_freq

# Disabling Auto scale on NSS cores
	echo 0 > /proc/sys/dev/nss/clock/auto_scale

# Clocks Power-down Sequence

	echo 400000000 > /sys/kernel/debug/clk/afab_a_clk/rate
	echo 32000000 > /sys/kernel/debug/clk/dfab_a_clk/rate
	echo 32000000 > /sys/kernel/debug/clk/sfpb_a_clk/rate
	echo 32000000 > /sys/kernel/debug/clk/cfpb_a_clk/rate
	echo 133000000 > /sys/kernel/debug/clk/nssfab0_a_clk/rate
	echo 133000000 > /sys/kernel/debug/clk/nssfab1_a_clk/rate
	echo 400000000 > /sys/kernel/debug/clk/ebi1_a_clk/rate

# Find scsi devices and remove it

	partition=`cat /proc/partitions | awk -F " " '{print $4}'`

	for entry in $partition; do
		sd_entry=$(echo $entry | head -c 2)

		if [ "$sd_entry" = "sd" ]; then
			[ -f /sys/block/$entry/device/delete ] && {
				echo 1 > /sys/block/$entry/device/delete
			}
		fi
	done

# Sata Power-Down Sequence
	[ -f /sys/devices/platform/msm_sata.0/ahci.0/sata_suspend ] && {
		echo "1"> /sys/devices/platform/msm_sata.0/ahci.0/sata_suspend
	}

# USB Power-down Sequence
	[ -d /sys/module/dwc3_ipq ] && rmmod dwc3-ipq

# PCIe Power-Down Sequence

# Remove devices
	for i in `ls /sys/bus/pci/devices/`; do
		d=/sys/bus/pci/devices/${i}
		v=`cat ${d}/vendor`
		[ "xx${v}" != "xx0x17cb" ] && echo 1 > ${d}/remove
	done

	sleep 2

# Remove Buses
	for i in `ls /sys/bus/pci/devices/`; do
		d=/sys/bus/pci/devices/${i}
		echo 1 > ${d}/remove
	done

# Remove RC

	[ -f /sys/devices/pci0000:00/pci_bus/0000:00/rcremove ] && {
		echo 1 > /sys/devices/pci0000:00/pci_bus/0000:00/rcremove
	}

# Krait Power-down Sequence

	echo 384000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq
	echo 384000 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_min_freq
	echo "powersave" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
	echo "powersave" > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor
}

case "$1" in
	false) ac_power ;;
	true) battery_power ;;
esac
