//
// Created by jb030 on 29/04/2024.
//

#ifndef ATODO_SERVICE_SQL_PREPARE_H
#define ATODO_SERVICE_SQL_PREPARE_H

#include <sqlite3.h>

namespace sql_prepare {
    bool set_db(sqlite3 *db);
    bool sql_precompile();
    sqlite3_stmt *get_stmt(const char *key);
    bool sql_finalize();
}

#define CHECK_ERROR_SELECT(func) \
    int rc = func;                   \
    while (rc == SQLITE_BUSY) {       \
        rc = func;                   \
    }                                \
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) { \
        LOG(ERROR) << "SQL error: " << sqlite3_errmsg((sqlite3 *)database::g_db); \
        throw std::runtime_error("SQL error"); \
    }

#define CHECK_ERROR(func) \
    int rc = func;                   \
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) { \
        LOG(ERROR) << "SQL error: " << sqlite3_errmsg((sqlite3 *)database::g_db); \
        throw std::runtime_error("SQL error"); \
    }


#endif //ATODO_SERVICE_SQL_PREPARE_H
