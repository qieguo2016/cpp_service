include(ExternalProject)

# set(BRPC_CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -Wno-narrowing)
# set(BRPC_CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wno-narrowing)

# if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
#     set(OPENSSL_ROOT_DIR
#         "/usr/local/opt/openssl"    # Homebrew installed OpenSSL
#         )
# endif()
# find_package(OpenSSL REQUIRED)
# add_library(ssl SHARED IMPORTED GLOBAL)
# set_property(TARGET ssl PROPERTY IMPORTED_LOCATION ${OPENSSL_SSL_LIBRARY})

# add_library(crypto SHARED IMPORTED GLOBAL)
# set_property(TARGET crypto PROPERTY IMPORTED_LOCATION ${OPENSSL_CRYPTO_LIBRARY})

set(BRPC_INSTALL_DIR ${THIRD_PARTY_PATH}/install/brpc)
set(BRPC_EXTERN_REPO_DIR  ${THIRD_PARTY_PATH}/brpc/)
SET(BRPC_INCLUDE_DIR ${BRPC_INSTALL_DIR}/include CACHE PATH "brpc include directory." FORCE)
SET(BRPC_LIBRARIES ${BRPC_INSTALL_DIR}/lib/libbrpc.a CACHE FILEPATH "brpc library." FORCE)
ExternalProject_Add(
    extern_brpc
    GIT_REPOSITORY https://github.com/apache/brpc.git
    GIT_TAG 1.4.0
    PREFIX          ${BRPC_EXTERN_REPO_DIR}
    CMAKE_ARGS       -DCMAKE_INSTALL_PREFIX=${BRPC_INSTALL_DIR}
                     -DTHIRD_PARTY_PATH=${THIRD_PARTY_PATH}
    CMAKE_CACHE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${BRPC_INSTALL_DIR}
)
INCLUDE_DIRECTORIES(${BRPC_INCLUDE_DIR})
ADD_LIBRARY(brpc STATIC IMPORTED GLOBAL)
SET_PROPERTY(TARGET brpc PROPERTY IMPORTED_LOCATION ${BRPC_LIBRARIES})
ADD_DEPENDENCIES(brpc INTERFACE extern_bprc)
target_link_libraries(brpc INTERFACE protobuf ssl crypto leveldb gflags glog snappy)
add_definitions(-DBRPC_WITH_GLOG)
LIST(APPEND external_project_dependencies brpc)
