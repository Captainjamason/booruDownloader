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
	echo "setting CXX to clang++17"
	export CXX=clang++17
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
	echo "Installing, Requiring elevation to install to /usr/local/bin/ and /etc/."
	sudo cp ./src/boorudownloader /usr/local/bin/boorudownloader
	if ! [ -d /etc/boorudownloader ]; then
		sudo mkdir /etc/boorudownloader
	fi
	if ! [ -f /etc/boorudownloader ]; then
		sudo cp ../exampleConfig /etc/boorudownloader/config
	fi
	echo "Installed!"
	echo "Please copy example configuration from /etc/boorudownloader/config to ~/.config/boorDownloader/config"
fi
