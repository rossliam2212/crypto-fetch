set(LIB_HEADERS
    ../../include/cf/ApiClient.hpp
	../../include/cf/ApiResponse.hpp
	../../include/cf/CommandLineParser.hpp
	../../include/cf/Formatter.hpp
)

set(LIB_SOURCES
        ApiClient.cpp
        ApiResponse.cpp
        CommandLineParser.cpp
        Formatter.cpp
)

set(LIB_INCLUDES
		./
		../../include/
        ${CURLPP_INCLUDE_DIRS}
        ${CMAKE_BINARY_DIR}/configured_files/include
)

add_library(${LIB_NAME} STATIC
        ${LIB_SOURCES}
)
target_link_libraries(${LIB_NAME} PUBLIC
        spdlog::spdlog
        nlohmann_json::nlohmann_json
	    cxxopts::cxxopts
        ${CURLPP_LIBRARIES}
)
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDES})
target_link_directories(${LIB_NAME} PUBLIC ${CURLPP_LIBRARY_DIRS})

if(${ENABLE_WARNINGS})
	target_set_warnings(${LIB_NAME} ${ENABLE_WARNINGS} ${ENABLE_WARNINGS_AS_ERRORS})
endif()
