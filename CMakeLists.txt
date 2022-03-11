cmake_minimum_required(VERSION 3.7)

project(secure-store)

set(SECURE_STORE_SOURCES
    src/main.cpp
    src/config.cpp
    src/config/load_config.cpp
)

include_directories(
    include
    /usr/local/include
)

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SECURE_STORE_SOURCES}
)
