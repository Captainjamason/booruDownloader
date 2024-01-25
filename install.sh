#!/usr/bin/env bash

#	boorudownloader
#	install.sh
#	Jamason P Davis
#	Copyright 2024.

if [[ $1 == "--clean-build" ]]; then
	echo "Cleaning build directory..."
	rm -rf ./build/
	echo "Done! Proceeding to build..."
fi

if [[ $1 == "--clean" ]]; then
	echo "Cleaning build directory..."
	rm -rf ./build/
	echo "Done!"
	exit
fi

if [[ $OSTYPE == freebsd* ]]; then
	echo "OS: FreeBSD, setting CC to clang17..."
	export CC=clang17 
fi

if ! [ -d ./build/ ]; then
	echo "Build directory not found, Setting up now..."
	meson setup build && cd ./build
else 
	echo "Build directory found, Starting compilation..."
	cd ./build
fi

meson compile

if [[  $1 == "--only-build" ]];  then
	echo "All done."
else
	echo "Installing the /usr/local/bin/, Requiring elevation to install."
	sudo cp ./src/boorudownloader /usr/local/bin/boorudownloader
	echo "Installed!"
fi
