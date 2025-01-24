cmake_minimum_required(VERSION 3.29)

if (NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif ()

project(
		crypto-fetch
		VERSION 1.0.0
		DESCRIPTION "A simple command line tool to fetch cryptocurrency prices."
		LANGUAGES C CXX
)

set(LIB_NAME      crypto-fetch-lib)
set(EXE_NAME      crypto-fetch)
set(TEST_EXE_NAME crypto-fetch-tests)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_BUILD_TYPE            Debug)
set(CMAKE_MODULE_PATH           ${PROJECT_SOURCE_DIR}/cmake/)

option(ENABLE_WARNINGS           "Enable warnings"             ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable a unit testing build" OFF)

include(Dependencies)
setup_dependencies()

if (ENABLE_WARNINGS)
	include(Warnings)
endif()

add_subdirectory(configured)
add_subdirectory(src)

include(CTest)
enable_testing()
add_subdirectory(tests)
