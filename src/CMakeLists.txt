FILE(GLOB source_codes
    ${CMAKE_CURRENT_LIST_DIR}/*/*.cpp
)
FILE(GLOB header_codes
    ${CMAKE_CURRENT_LIST_DIR}/*/*.h
)
add_library(service_src STATIC ${source_codes} ${header_codes})

add_executable(cpp_service ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_link_libraries(cpp_service -Wl,--whole-archive service_src -Wl,--no-whole-archive)

install(TARGETS cpp_service
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin
        ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dist/lib
        LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dist/so
        )
