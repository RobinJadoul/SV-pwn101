#!/usr/bin/env bash
set -euo pipefail

cd /mnt
make build
make mkdist
make copy DEST=/
make clean
cd /
cp -r /mnt/dist dist
rm -rf /mnt/
