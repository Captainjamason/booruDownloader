#!/bin/sh

#   booruDownloader
#   installScript.sh
#   Jamason P Davis
#   Copyright 2024
#   <3

if ! [ -d /etc/boorudownloader ]; then
    echo "'/etc/boorudownloader' not found, Making folder now"
    mkdir /etc/boorudownloader/
fi

if ! [ -f /etc/boorudownloader/config ]; then
    echo "'/etc/boorudownloader/config' not found... Copying example configuration"
    cp ./exampleConfig /etc/boorudownloader/config
fi