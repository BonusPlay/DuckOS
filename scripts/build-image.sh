#!/bin/sh
set -e

if [ "$(id -u)" != 0 ]; then
    echo "[!] Please run as root"
    exit 1
fi

REPO_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." &> /dev/null && pwd )"
echo "[-] repo dir set to ${REPO_DIR}"

mkdir -p "${REPO_DIR}/build"
IMAGE_PATH="${REPO_DIR}/build/duckOS.img"

echo "[-] Creating empty 100MB image"
dd if=/dev/zero of="${IMAGE_PATH}" count=100 bs=1M

echo "[-] Creating loopback device"
dev=$(losetup --find --partscan --show "${IMAGE_PATH}")
echo "[-] done, mounted at ${dev}"

echo "[-] Creating partition table"
parted -s "${dev}" mklabel msdos mkpart primary ext2 1MiB 100% -a minimal set 1 boot on

echo "[-] Creating fs"
mkfs.ext2 "${dev}p1"

echo "[-] Making tmp dir"
tmpdir=$(mktemp -d)
echo "[-] tmpdir at ${tmpdir}"

echo "[-] Mounting ${dev}p1 to ${tmpdir}"
mount "${dev}p1" "${tmpdir}"

echo "[-] Installing GRUB"
grub-install --boot-directory="${tmpdir}/boot" --target=i386-pc --modules="ext2 part_msdos" "${dev}"
cp "${REPO_DIR}/scripts/grub.cfg" "${tmpdir}/boot/grub/grub.cfg"

echo "[-] Copying Image"
cp "${REPO_DIR}/build/kernel/DuckOS" "${tmpdir}/boot/DuckOS"

echo "[-] Unmounting loopback device"
umount "${tmpdir}"

echo "[-] Removing tmp dir"
rmdir "${tmpdir}"

echo "[-] Removing loop device $dev"
losetup -d "${dev}"

echo "[-] chown image"
sudo chown $SUDO_UID:$SUDO_GID "${IMAGE_PATH}"
