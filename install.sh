#!/bin/bash

#	boorudownloader
#	install.sh
#	Jamason P Davis
#	Copyright 2024.

if [[ $OSTYPE == freebsd* ]]; then
	echo "OS: FreeBSD, setting CC to clang17..."
	CC=clang17 meson setup build && cd build
	meson compile
	echo "Installing boorudownloader to /usr/local/bin/, Please provide elevation..."
	sudo cp ./src/boorudownloader /usr/local/bin/boorudownloader
fi

