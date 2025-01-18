set(EXE_SOURCES
        main.cpp
)

add_executable(${EXE_NAME} ${EXE_SOURCES})
target_link_libraries(${EXE_NAME} PUBLIC ${LIB_NAME})