#!/bin/sh
set -e

# Install required python packages into the container's Python
/opt/uv/tools/qmk/bin/python3 -m pip install -r /qmk_firmware/requirements.txt

# Run make to build the specified keymap
make beekeeb/piantor:rafanovim
