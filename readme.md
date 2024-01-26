# booruDownloader

A lightweight cross-platform C++ program for downloading images in bulk from imageboard sites.

### Features:

* [X] Meson integrated build system.
* [ ] Danbooru support.
* [ ] Gelbooru support.
* [ ] More site support (Hopefully module flexibility?)
* [ ] Basic GUI done in `wxwidgets`
* [ ] Real time progress outputs in a non-invasive way.
* [ ] Multithreading
* [X] Sorting by `tag` or `rating` into folders
* [ ] Customizable config


### Requirements

* `libcurl >= 8.5.0`
* `jsoncpp >= 1.9.5`
* `clang >= 17` (Primary compiler choice, May work with GCC)
* `meson >= 1.3.1`


### Build Instructions
- Clone the repository.  
- Easy way (under development):
  - `./install.sh`
- Manual Route:
  - `meson setup build && cd build`
  - `meson compile`
  - Output will be in `build/src/boorudownloader`.

Cleanup:
  - `./install.sh --clean` OR `rm -rf ./build/`
--- 

<3

Copyright 2024 - JPD/hurbIndustries
