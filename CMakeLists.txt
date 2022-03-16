cmake_minimum_required(VERSION 3.7)

project(secure-store)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SECURE_STORE_SOURCES
    src/main.cpp
    src/config.cpp
    src/config/load_config.cpp
    src/menu/main.cpp
    src/storage/main.cpp
    src/storage/create_empty.cpp
    src/storage/data_pack.cpp
    src/storage/pack.cpp
    src/storage/record.cpp
)

include_directories(
    include
    /usr/local/include
)

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SECURE_STORE_SOURCES}
)
