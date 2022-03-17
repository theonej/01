#!/bin/bash

#call sudo modprobe nbd to fix /dev/nbd0p1 mount point error

SDNAME="$1"
UIMGNAME="$2"

if [ "$#" -ne 2 ]; then
    echo "Usage: "$0" sdimage uimage"
    exit 1
fi

command -v qemu-img >/dev/null || { echo "qemu-img not installed"; exit 1; }
command -v qemu-nbd >/dev/null || { echo "qemu-nbd not installed"; exit 1; }

echo -e 'creating qemu image\n'
qemu-img create "$SDNAME" 64M

echo -e 'mounting disk\n'
sudo qemu-nbd -c /dev/nbd0 "$SDNAME"

echo -e 'formatting disk using fdisk\n'
(echo o;
echo n; echo p
echo 1
echo ; echo
echo w; echo p) | sudo fdisk /dev/nbd0

echo -e 'disk formatted\n'

sudo mkfs.ext2 /dev/nbd0p1
echo -e 'file system created'

mkdir tmp || true
sudo mount -o user /dev/nbd0p1 tmp/
sudo cp "$UIMGNAME" tmp/
sudo umount /dev/nbd0p1
rmdir tmp || true
sudo qemu-nbd -d /dev/nbd0
echo 'sd image file created'