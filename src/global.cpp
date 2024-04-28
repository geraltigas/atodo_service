//
// Created by jb030 on 28/04/2024.
//

#include <global.h>

char * global::database_file_path = "./atodo.db";
sqlite3 * global::db = nullptr;

const char * global::app_db_init_sql = "";
