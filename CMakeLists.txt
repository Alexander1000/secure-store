cmake_minimum_required(VERSION 3.7)

project(secure-store)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

set(SECURE_STORE_SOURCES_SHARED
    src/config.cpp
    src/config/load_config.cpp
    src/menu/main.cpp
    src/storage/main.cpp
    src/storage/create_empty.cpp
    src/storage/data_pack.cpp
    src/storage/pack.cpp
    src/storage/unpack.cpp
    src/storage/record.cpp
    src/storage/db_record.cpp
    src/storage/db_encode.cpp
)

set(SECURE_STORE_SOURCES
    src/main.cpp
    ${SECURE_STORE_SOURCES_SHARED}
)

include_directories(
    include
    /usr/local/include
)

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SECURE_STORE_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    OpenSSL::Crypto
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

#############
### TESTS ###
#############

project(secure-store-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SECURE_STORE_SOURCES_TEST
    tests/src/main.cpp
    ${SECURE_STORE_SOURCES_SHARED}
    tests/src/pack_tests/case0.cpp
    tests/src/pack_tests/case01.cpp
)

include_directories(
    include
    tests/include
    /usr/local/include
)

find_library(CPP_UNIT_TEST libcpp-unit-test.a)
message(STATUS "Found cpp-unit-test: ${CPP_UNIT_TEST}")

add_executable(
    ${PROJECT_NAME} tests/src/main.cpp
    ${SECURE_STORE_SOURCES_TEST}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    ${CPP_UNIT_TEST}
    OpenSSL::Crypto
)
