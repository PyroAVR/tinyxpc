project('tinyxpc', 'c')

includes = include_directories('include')

txpc_main = library('tinyxpc', 'src/tinyxpc.c',
            include_directories: includes
)

dep_txpc = declare_dependency(
    include_directories: includes,
    link_with: txpc_main
) 
