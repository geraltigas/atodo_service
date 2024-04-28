//
// Created by jb030 on 28/04/2024.
//

#include <interface/database.h>
#include <filesystem>
#include <meta/meta.h>
#include <sqlite3.h>
#include <global.h>

bool database::check_database_existence() {
    meta::create_meta_database();
    return std::filesystem::exists(meta::get_app_database_file_path());
}

std::string database::get_database_file_path() {
    meta::create_meta_database();
    return meta::get_app_database_file_path();
}

void database::set_database_file_path(std::string file_path) {
    meta::create_meta_database();
    meta::set_app_database_file_path(file_path);
}

bool initialize_database(sqlite3 *db) {
    if (db == nullptr) {
        return false;
    } else {
        char *zErrMsg = 0;
        const char *sql = global::app_db_init_sql;
        int rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            return false;
        }
        return true;
    }
}

bool database::create_database() {
    meta::create_meta_database();
    std::string file_path = meta::get_app_database_file_path();
    if (std::filesystem::exists(file_path)) {
        return false;
    }else {
        sqlite3 *db;
        int rc = sqlite3_open(file_path.c_str(), &db);
        if (rc) {
            return false;
        } else {
            bool result = initialize_database(db);
            sqlite3_close(db);
            if (result) {
                return true;
            } else {
                throw std::runtime_error("Failed to initialize database");
            }
        }
    }
}