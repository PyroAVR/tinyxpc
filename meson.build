project('tinyxpc', 'c')

includes = include_directories('include')

txpc_main = library('tinyxpc', 'src/tinyxpc.c',
            include_directories: includes,
            install: true)

dep_txpc = declare_dependency(
    include_directories: includes,
    link_with: txpc_main
) 

install_headers(['include/tinyxpc/tinyxpc.h'])
