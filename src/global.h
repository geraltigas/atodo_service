//
// Created by jb030 on 28/04/2024.
//

#ifndef ATODO_SERVICE_GLOBAL_H
#define ATODO_SERVICE_GLOBAL_H

#include <sqlite3.h>

namespace global {
    extern char * database_file_path;
    extern sqlite3 * db;
    extern const char * app_db_init_sql;
}

#endif //ATODO_SERVICE_GLOBAL_H
