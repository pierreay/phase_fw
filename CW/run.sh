#!/bin/bash

CW_USB=$(lsusb | grep "2b3e:ace2")

if [ "$CW_USB" != "" ]; then
    echo "Found ChipWhisperer"
else
    echo -e "ChipWhisperer not found in host\nExiting.."
    exit
fi

echo $CW_USB

BUS_ID=$(echo $CW_USB | awk '{print $2}')
DEVICE_ID=$(echo $CW_USB | awk '{print $4}') | sed 's/://'

docker run -i -t -p 8888:8888 \
    -v /dev/bus/usb/$BUS_ID/$DEVICE_ID:/dev/bus/usb/$BUS_ID/$DEVICE_ID \
    --device /dev/bus/usb/$BUS_ID/$DEVICE_ID \
    -u cw \
    -v ./work:/home/cw/work \
    cw
