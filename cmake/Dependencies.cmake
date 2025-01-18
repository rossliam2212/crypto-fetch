include(cmake/CPM.cmake)

function(setup_dependencies)
    find_package(spdlog REQUIRED)
    find_package(nlohmann_json REQUIRED)
    find_package(cxxopts REQUIRED)

    # curlpp
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(CURLPP REQUIRED curlpp)

    # Catch2
    CPMAddPackage(
            NAME Catch2
            GITHUB_REPOSITORY catchorg/Catch2
            VERSION 3.0.1
    )

    if (Catch2_ADDED)
        list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
    endif()
endfunction()