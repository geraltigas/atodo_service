//
// Created by jb030 on 28/04/2024.
//

#include <interface/database.h>
#include <filesystem>
#include <meta/meta.h>
#include <sqlite3.h>
#include <global.h>
#include <glog/logging.h>
#include <component/sql_prepare.h>

sqlite3 *database::g_db = nullptr;

bool database::check_database_existence() {
    meta::create_if_not_exist();
    return std::filesystem::exists(meta::get_now_app_database_file_path());
}

std::string database::get_database_file_path() {
    meta::create_if_not_exist();
    return meta::get_now_app_database_file_path();
}

bool database::set_database_file_path(const std::string& file_path) {
    return meta::create_if_not_exist() && meta::set_future_app_database_file_path(file_path);
}

bool initialize_database(sqlite3 *db) {
    if (db == nullptr) {
        return false;
    } else {
        char *zErrMsg = 0;
        const char *sql = global::app_db_init_sql;
        int rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            LOG(ERROR) << "SQL error: " << zErrMsg;
            return false;
        }
        return true;
    }
}

bool database::create_database() {
    std::string now_file_path = meta::get_now_app_database_file_path();
    std::string future_file_path = meta::get_future_app_database_file_path();

    if (std::filesystem::exists(now_file_path)) {
        if (now_file_path == future_file_path) {
            return true;
        } else {
            if (g_db != nullptr) {
                sql_prepare::sql_finalize();
                sqlite3_close(g_db);
                g_db = nullptr;
            }
            std::filesystem::rename(now_file_path, future_file_path);
            return meta::set_now_app_database_file_path(future_file_path) && get_sqlite_db() && sql_prepare::set_db(g_db) && sql_prepare::sql_precompile();
        }
    } else {
        sqlite3 *db;
        int rc = sqlite3_open(now_file_path.c_str(), &db);
        if (rc) {
            return false;
        } else {
            bool result = initialize_database(db);
            sqlite3_close(db);
            if (result) {
                return meta::set_now_app_database_file_path(now_file_path) &&
                       meta::set_future_app_database_file_path(future_file_path);
            } else {
                return false;
            }
        }
    }

}
#include <iostream>

bool database::delete_database() {
    meta::create_if_not_exist();
    std::string file_path = meta::get_now_app_database_file_path();
    if (!std::filesystem::exists(file_path)) {
        return true;
    }
    // release the database
    if (g_db != nullptr) {
        sql_prepare::sql_finalize();
        sqlite3_close(g_db);
        g_db = nullptr;
    }
    std::filesystem::remove(file_path);
    return true;
}

sqlite3 *database::get_sqlite_db() {
    if (g_db != nullptr) {
        return g_db;
    }
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
