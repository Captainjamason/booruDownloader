#!/usr/bin/env bash

#	boorudownloader
#	install.sh
#	Jamason P Davis
#	Copyright 2024.


#	Check variables, I don't like specifiying only one location but it will have to do.
if [[ $1 == "--uninstall" ]]; then
	echo "Uninstalling..."
	if ! [[ $EUID = 0 ]]; then
		echo "Requiring elevation."
		sudo rm -rf /usr/local/bin/boorudownloader
	else
		rm -rf /usr/local/bin/boorudownloader
	fi
	exit 0
fi

if [[ $1 == "--rebuild" ]]; then
	echo "Cleaning build directory..."
	rm -rf ./build/
	echo "Done! Proceeding to build..."
fi

if [[ $1 == "--clean" ]]; then
	echo "Cleaning build directory..."
	rm -rf ./build/
	echo "Done!"
	exit 0;
fi

if [[ $OSTYPE == freebsd* ]]; then
	echo "OS: FreeBSD, setting CC to clang17..."
	export CC=clang17
	echo "setting CXX to clang++17"
	export CXX=clang++17

	clang17 --version
	if ! [[ $? == 0 ]]; then
		echo "'clang17' environment not found. Install?"
		read -p '(y/n): ' installClangAnswer
		if [[ installClangAnswer == "y" ]]; then
			sudo pkg install clang17
		elif [[ installClangAnswer == "n" ]]; then
			exit 1
		else 
			echo "Answer cannot be blank, Exiting"
			exit 1
		fi
	fi
fi

if ! [[ -d ./build/ ]]; then
	echo "Build directory not found, Setting up now..."
	meson setup build && cd ./build
else 
	echo "Build directory found, Starting compilation..."
	cd ./build
fi

meson compile
if ! [[ $? == 0 ]]; then
	echo "[ERROR] Build failed"
	exit 1
fi


if [[  $1 == "--only-build" ]];  then
	echo "All done."
else
	echo "Installing, Requiring elevation to install to /usr/local/bin/ and /etc/."
	sudo cp ./src/boorudownloader /usr/local/bin/boorudownloader
	if ! [ -d /etc/boorudownloader ]; then
		sudo mkdir /etc/boorudownloader
	fi
	if ! [ -f /etc/boorudownloader ]; then
		sudo cp ../exampleConfig.json /etc/boorudownloader/config.json
	fi
	echo "Installed!"
	echo "Please copy example configuration from /etc/booruDownloader/config to ~/.config/booruDownloader/config"
fi
