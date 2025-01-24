find_package(Doxygen)

if (DOXYGEN_FOUND)
    add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
#            COMMAND dot -Tpng html/graph.dot -o html/graphImage.png
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
            COMMENT "Generating HTML documentation with Doxygen"
    )
endif()
