list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
include(Catch)

set(TEST_SOURCES
        ApiResponseTest.cpp
        CommandLineParserTest.cpp
)
set(TEST_INCLUDES "./")

add_executable(${TEST_EXE_NAME} ${TEST_SOURCES})
target_include_directories(${TEST_EXE_NAME} PUBLIC ${TEST_INCLUDES})
target_link_libraries(${TEST_EXE_NAME} PUBLIC ${LIB_NAME} Catch2::Catch2WithMain)

# Gives CTest the ability to discover all defined tests
catch_discover_tests(${TEST_EXE_NAME})
