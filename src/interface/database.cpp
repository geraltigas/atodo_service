//
// Created by jb030 on 28/04/2024.
//

#include <interface/database.h>
#include <filesystem>
#include <meta/meta.h>
#include <sqlite3.h>
#include <global.h>
#include <glog/logging.h>

sqlite3 *database::g_db = nullptr;

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
    LOG(INFO) << "Creating database at " << file_path;
    if (std::filesystem::exists(file_path)) {
        return true;
    }else {
        sqlite3 *db;
        int rc = sqlite3_open(file_path.c_str(), &db);
        if (rc) {
            return false;
        } else {
            bool result = initialize_database(db);
            sqlite3_close(db);
            return result;
        }
    }
}

bool database::delete_database() {
    meta::create_meta_database();
    std::string file_path = meta::get_app_database_file_path();
    if (std::filesystem::exists(file_path)) {
        std::filesystem::remove(file_path);
        return true;
    }
    return true;
}

sqlite3 *database::get_sqlite_db() {
    if (check_database_existence()) {
        int rc = sqlite3_open(get_database_file_path().c_str(), &g_db);
        if (rc) {
            return nullptr;
        } else {
            return g_db;
        }
    }
    return nullptr;
}

bool database::create_if_not_exist() {
    if (check_database_existence()) {
        return true;
    } else {
        return create_database();
    }
}
