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

#endif //ATODO_SERVICE_SQL_PREPARE_H
