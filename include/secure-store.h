#ifndef H_SECURE_STORE
#define H_SECURE_STORE

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 2

// #define DEBUG_LOGGER

// type: stdout(1), file(2)
#define DEBUG_LOGGER_TYPE 2
#define DEBUG_LOGGER_FILE_PATH "./debug.log"

#include <secure-store/app.h>
#include <secure-store/app/add_secret.h>
#include <secure-store/app/show.h>
#include <secure-store/menu.h>
#include <secure-store/storage.h>
#include <secure-store/data-pack.h>
#include <secure-store/crypto.h>
#include <secure-store/utils.h>

#endif
