#pragma once
#include "fileloader.h"

typedef enum {
    LOAD_OK,
    LOAD_ERR_FILE_NOT_FOUND,
    LOAD_ERR_TOO_LONG_LINE,
    LOAD_ERR_FORMAT_INVALID
} LoadError;


const char* load_error_to_string(LoadError err);
