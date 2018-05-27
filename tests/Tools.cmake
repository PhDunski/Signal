option(BUILD_TESTS_TOOLS "Should we build the tools sub projects unit tests?" TRUE)
if(BUILD_TESTS_TOOLS)
    add_subdirectory(Tools)
endif()
