#ifndef DB_DEFINES_H
#define DB_DEFINES_H

#include <string>

typedef struct Error {
    int error_code_;
    std::string error_explain;
} Error;

#endif
