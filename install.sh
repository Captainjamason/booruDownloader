#!/usr/bin/env bash

#	boorudownloader
#	install.sh
#	Jamason P Davis
#	Copyright 2024.

# Check for `sudo` or running as root.
if [[ $EUID == 0 ]]; then
	echo "No reason to run as root, exiting"
	exit 1
fi

# Check variables, I don't like specifiying only one location but it will have to do.
if [[ $1 == "--uninstall" ]]; then
	echo "Uninstalling..."
	sudo rm -rf /usr/local/bin/boorudownloader
	sudo rm -rf /etc/boorudownloader
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


# Check OS types and change variables as needed.
if [[ $OSTYPE == freebsd* ]]; then
	echo "OS: FreeBSD"
	echo "setting CC to clang17..."
	export CC=clang17
	echo "setting CXX to clang++17..."
	export CXX=clang++17
elif [[ $OSTYPE == linux* ]]; then
	echo "OS: Linux" 
elif [[ $OSTYPE == darwin* ]]; then 
	echo "OS: darwin"
else 
	echo "OS: `$OSTYPE`"
	echo "OS is not defined in ./install.sh, Using default values..."
	echo "If there is issues building please make an issue on github with your OS information..."
fi



# Build dependancy checking, woooo!

CC --version
if ! [[ $? == 0 ]]; then
	# This is specific to freeBSD as it requires clang17 to build.
	if [[ $OSTYPE == freebsd* ]]; then
		echo "llvm17 environment not found. Install?"
		read -p '(y/n): ' installClangAnswer
		if [[ $installClangAnswer == "y" ]]; then
			sudo pkg install llvm17
		elif [[ $installClangAnswer == "n" ]]; then
			exit 1
		else 
			echo "Answer cannot be blank, Exiting"
			exit 1
		fi
	else
		echo "C/CXX compiler not found. Exiting..."
		exit 1
	fi
fi

meson --version 
if ! [[ $? == 0 ]]; then 
	echo "'meson' not found, Exiting..."
	exit 1
fi



# Check for build directory.
if ! [[ -d ./build/ ]]; then
	echo "Build directory not found, Setting up now..."
	meson setup build && cd ./build
else 
	echo "Build directory found, Starting compilation..."
	cd ./build
fi

# Compile and check for erorrs.
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
	if ! [[ $? == 0 ]]; then 
		exit 1
	fi

	if ! [ -d /etc/boorudownloader ]; then
		sudo mkdir /etc/boorudownloader
	fi
	if ! [ -f /etc/boorudownloader ]; then
		sudo cp ../exampleConfig.json /etc/boorudownloader/config.json
	fi
	echo "Installed!"
	echo "Please copy example configuration from /etc/booruDownloader/config to ~/.config/booruDownloader/config"
fi
