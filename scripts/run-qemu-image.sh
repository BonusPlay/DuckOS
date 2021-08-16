#!/bin/bash
qemu-system-x86_64 -s -kernel TODO -drive file=duckOS.img,cache=directsync,format=raw,id=disk,if=ide -m 512M -enable-kvm -serial stdio
