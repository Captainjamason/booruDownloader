project('boorudownloader', 'cpp',
    version : '0.1.4',
    license : 'GPL3',
    default_options : ['c_std=c17','cpp_std=c++17'])
add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

## Dependencies
curl_dep = dependency('libcurl')
jsoncpp_dep = dependency('jsoncpp')
thread_dep = dependency('threads')
opencli_dep = dependency('opencxx-cli', version:'>=0.0.3')


inc = include_directories('include')

subdir('src')
