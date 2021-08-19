#!/bin/bash
set -e

if [ "$(id -u)" != 0 ]; then
    echo "Please run as root"
    exit 1
fi

echo "Creating empty 100MB image"
dd if=/dev/zero of=duckOS.img count=100 bs=1M

echo "Creating loopback device"
dev=$(losetup --find --partscan --show duckOS.img)
echo "done, mounted at ${dev}"

echo "Creating partition table"
parted -s "${dev}" mklabel msdos mkpart primary ext2 1MiB 100% -a minimal set 1 boot on
echo "done"

echo "Creating fs"
mkfs.ext2 "${dev}p1"
echo "done"

echo "Making tmp dir"
tmpdir=$(mktemp -d)
echo "done, at ${tmpdir}"

echo "Mounting ${dev}p1 to ${tmpdir}"
mount "${dev}p1" "${tmpdir}"
echo "done"

echo "Installing GRUB"
grub-install --boot-directory="${tmpdir}/boot" --target=i386-pc --modules="ext2 part_msdos" "${dev}"
cp ./grub.cfg "${tmpdir}/boot/grub/grub.cfg"
echo "done"

echo "Copying Image"
cp ../build/kernel/DuckOS "${tmpdir}/boot/DuckOS"
echo "done"

echo "Unmounting loopback device"
umount "${tmpdir}"
echo "done"

echo "Removing tmp dir"
rmdir "${tmpdir}"
echo "done"

echo "Removing loop device $dev"
losetup -d "${dev}"
echo "done"

echo "chown image"
sudo chown $SUDO_USER:$SUDO_USER ./duckOS.img
echo "done"
