project('tinyxpc', 'c')

includes = include_directories('include')

txpc_main = library('tinyxpc', 'src/tinyxpc.c',
            include_directories: includes,
            install: true)

install_headers(['include/tinyxpc/tinyxpc.h'])
