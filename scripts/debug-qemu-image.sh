#!/bin/bash

REPO_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." &> /dev/null && pwd )"
IMAGE_PATH="${REPO_DIR}/build/duckOS.img"

qemu-system-x86_64 -s -drive "file=${IMAGE_PATH},cache=directsync,format=raw,id=disk,if=ide" -m 512M -enable-kvm -serial stdio -action reboot=shutdown -action shutdown=pause -S
