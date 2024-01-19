project('boorudownloader', 'cpp',
    version : '0.1.2',
    license : 'GPL3')
add_global_arguments('-DSOME_TOKEN=value', language : 'cpp')

## Dependencies
curl_dep = dependency('libcurl')
jsoncpp_dep = dependency('jsoncpp')

inc = include_directories('include')

subdir('src')