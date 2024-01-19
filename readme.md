# booruDownloader

A lightweight cross-platform C++ program for downloading images in bulk from imageboard sites.

### Planned Features:

* [X] CLI Interface.
* [X] ~~Fledged Build System with `cmake`~~ Build system is being integrated with Meson instead.
* [ ] Full Danbooru support.
* [ ] Gelbooru support.
* [ ] Basic GUI done in `wxwidgets`
* [ ] Multithreading
* [X] Sorting by `tag` or `rating` into folders
* [ ] Customizable config


### Requirements

* `libcurl >= 8.5.0`
* `jsoncpp >= 1.9.5`

### Build Instructions
- Clone the repository.
- `meson setup build && cd build`
- `meson compile`

Output will be in `build/src/boorudownloader`.

--- 

<3

Copyright 2024 - JPD/hurbIndustries
