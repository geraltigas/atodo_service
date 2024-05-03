//
// Created by jb030 on 28/04/2024.
//

#ifndef ATODO_SERVICE_DATABASE_H
#define ATODO_SERVICE_DATABASE_H

#include <string>
#include <sqlite3.h>

namespace database {
    bool check_database_existence();
    std::string get_database_file_path();
    bool set_database_file_path(std::string file_path);
    bool create_database();
    bool create_if_not_exist();
    bool delete_database();
    sqlite3 *get_sqlite_db();
    extern sqlite3 *g_db;
}

#endif //ATODO_SERVICE_DATABASE_H
