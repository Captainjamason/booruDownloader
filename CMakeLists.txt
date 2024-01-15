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

install(TARGETS boorudownloader DESTINATION bin)

target_include_directories(boorudownloader PRIVATE include)

target_link_libraries(boorudownloader jsoncpp curl)

