source_files = [
    'main.cpp', 
    'term.cpp',
    'args.cpp',
    'download.cpp',
    'config.cpp'
]

boorudownloader = executable('boorudownloader',
    source_files,
    include_directories : inc,
    dependencies : [thread_dep, curl_dep, jsoncpp_dep],
    install : true,
    cpp_args : '-O',
    )
