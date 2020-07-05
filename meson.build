project('tinyxpc', 'c')
# ========= INSTALLATION CONTROL =========
# Install headers?
should_install_headers = false
if get_option('install_headers') == 'not_subproject'
    should_install_headers = not meson.is_subproject()
else
    should_install_headers = (get_option('install_headers') == 'yes')
endif
# ========= END INSTALLATION CONTROL =========

# ========= DEPENDENCY OBJECTS FOR SUPERPROJECT BUILDS =========

dep_txpc = declare_dependency(
    include_directories: include_directories('include')
) 
# ========= END DEPENDENCY OBJECTS FOR SUPERPROJECT BUILDS =========

# ========= HEADER INSTALLATION CONFIG =========
if should_install_headers
    install_subdir(
        get_option('includedir'),
        strip_directory: true,
        install_dir: join_paths(get_option('prefix'), 'include')
    )
endif
# ======== END HEADER INSTALLATION CONFIG ========
