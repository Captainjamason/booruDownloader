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
- Clone the repository.  
- Easy way (under development):
  - `./install.sh`
- Manual Route:
  - `meson setup build && cd build`
  - `meson compile`
  - Output will be in `build/src/boorudownloader`.

### Build Cleanup:
  - `./install.sh --clean` OR `rm -rf ./build/`

---

## Configuration:
Configuration is handled inside one of three `json` formatted configuration files.
- `~./config/booruDownloader/config` *(preferred)*
- `~./config/booruDownloader.conf`
- `/etc/booruDownloader/conf` *(example configuration)*

Please copy the example configuration to one of these folders; like so:
`mkdir ~./config/booruDownloader && cp /etc/booruDownloader/conf ~/.config/booruDownloader/conf`

### Options:
- `user`: Allows for input of username and API key for danbooru, Not currently used, May be handy to be integrated in future...
- `testbooru`: Enables or disables the use of testbooru in favor of danbooru. Mainly useful for debugging and development.

--- 

<3

Copyright 2024 - JPD/hurbIndustries
