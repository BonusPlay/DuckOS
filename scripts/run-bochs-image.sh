#!/bin/bash

REPO_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." &> /dev/null && pwd )"

IMAGE_PATH="${REPO_DIR}/build/duckOS.img" bochs -f "$REPO_DIR/scripts/bochs.conf"
