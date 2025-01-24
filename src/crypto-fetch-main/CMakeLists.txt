set(EXE_SOURCES
        main.cpp
)

add_executable(${EXE_NAME} ${EXE_SOURCES})
target_link_libraries(${EXE_NAME} PUBLIC ${LIB_NAME})

if(${ENABLE_WARNINGS})
    target_set_warnings(${EXE_NAME} ${ENABLE_WARNINGS} ${ENABLE_WARNINGS_AS_ERRORS})
endif()
