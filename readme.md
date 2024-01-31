# booruDownloader

A lightweight cross-platform C++ program for downloading images in bulk from imageboard sites.

## Features:

* [X] Meson integrated build system.
* [ ] Danbooru support.
* [ ] Gelbooru support.
* [ ] More site support (Hopefully module flexibility?)
* [ ] Basic GUI done in `wxwidgets`
* [ ] Real time progress outputs in a non-invasive way.
* [ ] Multithreading
* [X] Sorting by `tag` or `rating` into folders
* [ ] Customizable config

---

## Requirements

* `libcurl >= 8.5.0`
* `jsoncpp >= 1.9.5`
* `clang >= 17` (My primary compiler choice, May work with GCC...)
* `meson >= 1.3.1`


## Build Instructions:
### Auto Route:
`./install.sh` is a script written to check for dependencies and build as necessary. along with installing the binary to `/usr/local/bin`. 
Other options available with `./install.sh`:
- `--only-build`: Will only output to `./build/src/boorudownloader`, Won't install binary anywhere.
- `--clean`: Will clean the repository folder of any build remnants.
- `--rebuild`: Same idea as `--clean` but will also rebuild in the process.
- `--uninstall`: Will remove the binary from `/usr/local/bin` and delete `/etc/boorudownloader/`
- ***IN DEV:*** `--portable`: Will put the binary and config in `./bin`, Handy for moving things around to different systems.

### Manual Route:
- `meson setup build && cd build`
- `meson compile`
Output will be in `build/src/boorudownloader` by default. This is useful for debugging any issues related to `./install.sh`.

---

## Configuration:
Configuration is handled inside one of three `json` formatted configuration files.
- `~./config/booruDownloader/config.json` *(preferred)*
- `/etc/booruDownloader/conf` *(example configuration)*

It will also look for `conf.json` in the same folder as the binary. Useful for portable installs.

Please copy the example configuration to one of these folders; like so:
`mkdir ~./config/booruDownloader && cp /etc/booruDownloader/conf.json ~/.config/booruDownloader/conf.json`

### Options:
- `user`: Allows for input of username and API key for danbooru, Not currently used, May be handy to be integrated in future...
- `testbooru`: Enables or disables the use of testbooru in favor of danbooru. Mainly useful for debugging and development.

--- 

<3

Copyright 2024 - JPD/hurbIndustries
