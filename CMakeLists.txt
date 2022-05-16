cmake_minimum_required(VERSION 3.7)

project(secure-store)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (APPLE)
    # brew --prefix openssl
    set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)
endif(APPLE)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

set(SECURE_STORE_SOURCES_SHARED
    src/app/init.cpp
    src/app/get_app.cpp
    src/app/switch_to_show_frame.cpp
    src/app/main_frame_init.cpp
    src/app/set_file_name.cpp
    src/app/events/event_table.cpp
    src/app/events/on_password_enter.cpp
    src/app/events/on_file_browse_click.cpp
    src/app/events/on_click_select_directory.cpp
    src/app/events/on_click_create_file.cpp
    src/app/add_secret/init.cpp
    src/app/add_secret/initialize.cpp
    src/app/add_secret/on_click_save_button.cpp
    src/app/add_secret/on_click_cancel_button.cpp
    src/app/main/get_panel_open_file.cpp
    src/app/main/get_panel_new_file.cpp
    src/app/show/init.cpp
    src/app/show/reload_content.cpp
    src/app/show/get_selected_secret.cpp
    src/app/show/render_storage_records.cpp
    src/app/show/events/on_save_secret_click.cpp
    src/app/show/events/on_add_secret_click.cpp
    src/app/show/events/on_select_item.cpp
    src/app/show/events/on_click_remove_secret.cpp
    src/menu/main.cpp
    src/crypto/encrypt_decrypt.cpp
    src/crypto/hash_md5.cpp
    src/crypto/hash_sha3_512.cpp
    src/crypto/prepare_credentials.cpp
    src/data_pack.cpp
    src/storage/main.cpp
    src/storage/create_empty.cpp
    src/storage/pack.cpp
    src/storage/unpack.cpp
    src/storage/record.cpp
    src/storage/db_record.cpp
    src/storage/db_save.cpp
    src/storage/db_open.cpp
    src/storage/db_save_current.cpp
)

set(SECURE_STORE_SOURCES
    src/main.cpp
    ${SECURE_STORE_SOURCES_SHARED}
)

include_directories(
    include
    /usr/local/include
)

find_library(IO_BUFFER libio-buffer.a)
message(STATUS "Found io-buffer library: ${IO_BUFFER}")

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${SECURE_STORE_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${IO_BUFFER}
    OpenSSL::Crypto
    ncurses
    ${wxWidgets_LIBRARIES}
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

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

set(SECURE_STORE_SOURCES_TEST
    tests/src/main.cpp
    ${SECURE_STORE_SOURCES_SHARED}
    tests/src/pack_tests/case0.cpp
    tests/src/pack_tests/case01.cpp
    tests/src/ciper_tests/case02.cpp
    tests/src/save/case01.cpp
    tests/src/save/save_multi_records.cpp
    tests/src/save/case03.cpp
    tests/src/open/case01.cpp
    tests/src/open/case02.cpp
    tests/src/open/case03.cpp
    tests/src/open/case04.cpp
    tests/src/open/case05.cpp
    tests/src/hash_tests/case01.cpp
    tests/src/prepare_credentials/case01.cpp
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
    ${IO_BUFFER}
    ${CPP_UNIT_TEST}
    OpenSSL::Crypto
    ncurses
    ${wxWidgets_LIBRARIES}
)
