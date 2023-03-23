set(DOCKER_PREBUILD_DIR /opt/)
# pre build lib
include_directories(${DOCKER_PREBUILD_DIR}/brpc/include)
include_directories(${DOCKER_PREBUILD_DIR}/gflags/include)
include_directories(${DOCKER_PREBUILD_DIR}/glog/include)
include_directories(${DOCKER_PREBUILD_DIR}/jemalloc/include)

link_directories(${DOCKER_PREBUILD_DIR}/brpc/lib)
link_directories(${DOCKER_PREBUILD_DIR}/gflags/lib)
link_directories(${DOCKER_PREBUILD_DIR}/glog/lib)
link_directories(${DOCKER_PREBUILD_DIR}/jemalloc/lib)

set(EXTERN_LIB
    # librdkafka++.a librdkafka.a liblua.a 
    libbrpc.a 
    # fmt::fmt 
    libzstd.a
    libglog.so libgflags.a libprotobuf.a libleveldb.a 
    # libzookeeper_mt.a
    -lcurl
    -lconfig++ -lsnappy -lpthread -lcrypto -lm -lrt -lssl -ldl -lz -lbz2 -ltbb
)

# source code
FILE(GLOB source_codes
    ${CMAKE_CURRENT_LIST_DIR}/*/*.cc
)
FILE(GLOB header_codes
    ${CMAKE_CURRENT_LIST_DIR}/*/*.h
)
add_library(service_src STATIC ${source_codes} ${header_codes})
target_link_libraries(service_src ${EXTERN_LIB})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/main.cc)
target_link_libraries(${PROJECT_NAME} -Wl,--whole-archive service_src -Wl,--no-whole-archive)
target_link_libraries(${PROJECT_NAME} libjemalloc.a)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dist/bin
        ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dist/lib
        LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/dist/so
        )
