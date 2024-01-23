source_files = [
    'main.cpp',
    'config.cpp',
    'termcolor.cpp',
    'termFuncs.cpp',
    'commands.cpp',
    'danbooru.cpp',
    'download.cpp'
]

boorudownloader = executable('boorudownloader',
    source_files,
    include_directories : inc,
    dependencies : [thread_dep, curl_dep, jsoncpp_dep],
    install : true
    )
