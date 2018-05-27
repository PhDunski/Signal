option(BUILD_TESTS_SIGNAL "Should we build the signa unit tests?" TRUE)
if(BUILD_TESTS_SIGNAL)
    add_subdirectory(Signal)
endif()
