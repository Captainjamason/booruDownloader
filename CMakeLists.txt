cmake_minimum_required(VERSION 3.27) # Note, This is the most recent cmake version, I have not tested anything older...
project(boorudownloader)

add_custom_target(installScript ALL
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND src/installScript.sh
    VERBATIM
)

add_executable(boorudownloader
    src/main.cpp 
    src/termcolor.cpp
    src/termFuncs.cpp
    src/download.cpp
    src/danbooru.cpp
    src/commands.cpp
    src/config.cpp
)

set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake)
if(WIN32)
    include_directories(./vcpkg/installed/x64-windows/include)
    link_directories(./vcpkg/installed/x64-windows/lib)
endif(WIN32)
if(LINUX)
    include_directories(./vcpkg/installed/x64-linux/include)
    link_directories(./vcpkg/installed/x64-linux/lib)
endif(LINUX)

install(TARGETS boorudownloader DESTINATION bin)

target_include_directories(boorudownloader PRIVATE include)

target_link_libraries(boorudownloader jsoncpp curl)

