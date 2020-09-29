project('tinyxpc', 'c')

# ========= BUILDING CONTROL =========
# Build tests?
should_build_tests = false
if get_option('build_tests') == 'yes'
    should_build_tests = true
elif get_option('build_tests') == 'not_subproject'
    should_build_tests = not meson.is_subproject()
endif
# ========= END BUILDING CONTROL =========

includes = include_directories('include')

sl_relay = library('xpc_relay', 'src/xpc_relay.c',
            include_directories: includes
)

dep_relay = declare_dependency(
    include_directories: includes,
    link_with: sl_relay
) 

if should_build_tests
    # test targets
    exe_relay_test = executable(
        'test_relay',
        [
            'tests/test_relay.c',
            'tests/support/crc.c'
        ],
        include_directories: [includes, include_directories('tests/support')],
        link_with: sl_relay
    )

    # test run targets
    test('test_relay', exe_relay_test)
endif
