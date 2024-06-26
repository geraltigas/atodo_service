//
// Created by jb030 on 28/04/2024.
//

#include "meta.h"
#include <map>
#include <filesystem>
#include <sqlite3.h>
#include <glog/logging.h>

const std::string meta_database_file_path = "./meta.db";
std::map<std::string, std::string> meta_kv_name_type = {
        {"id", "integer primary key check ( id = 0 )"},
        {"now_app_database_file_path", "text"},
        {"future_app_database_file_path", "text"}
};

bool meta::create_meta_database() {
        sqlite3 * db;
        int rc = sqlite3_open(meta_database_file_path.c_str(), &db);
        if (rc) {
            return false;
        }
        std::string sql = "CREATE TABLE meta (";
        for (auto &kv : meta_kv_name_type) {
            sql += kv.first + " " + kv.second + ",";
        }
        sql.pop_back();
        sql += ");";
        char *zErrMsg = nullptr;
        rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);
        if (rc != SQLITE_OK) {
            LOG(ERROR) << "SQL error: " << zErrMsg;
            return false;
        }
        sql = "insert into meta (id, now_app_database_file_path) values (0, './app.db');";
        zErrMsg = nullptr;
        rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);
        if (rc != SQLITE_OK) {
            LOG(ERROR) << "SQL error: " << zErrMsg;
            return false;
        }
        sql = "update meta set future_app_database_file_path = './app.db' where id = 0;";
        zErrMsg = nullptr;
        rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);
        if (rc != SQLITE_OK) {
            LOG(ERROR) << "SQL error: " << zErrMsg;
            return false;
        }
        sqlite3_close(db);
        return true;
}

std::string meta::get_now_app_database_file_path() {
    sqlite3 * db;
    int rc = sqlite3_open(meta_database_file_path.c_str(), &db);
    if (rc) {
        return {};
    }
    std::string sql = "select now_app_database_file_path from meta where id = 0;";
    char *zErrMsg = nullptr;
    char **result;
    int row, column;
    rc = sqlite3_get_table(db, sql.c_str(), &result, &row, &column, &zErrMsg);
    if (rc != SQLITE_OK) {
        LOG(ERROR) << "SQL error: " << zErrMsg;
        return {};
    }
    std::string app_database_file_path = result[1];
    sqlite3_free_table(result);
    sqlite3_close(db);
    return app_database_file_path;
}

std::string meta::get_future_app_database_file_path() {
    sqlite3 * db;
    int rc = sqlite3_open(meta_database_file_path.c_str(), &db);
    if (rc) {
        return {};
    }
    std::string sql = "select future_app_database_file_path from meta where id = 0;";
    char *zErrMsg = nullptr;
    char **result;
    int row, column;
    rc = sqlite3_get_table(db, sql.c_str(), &result, &row, &column, &zErrMsg);
    if (rc != SQLITE_OK) {
        LOG(ERROR) << "SQL error: " << zErrMsg;
        return {};
    }
    std::string app_database_file_path = result[1];
    sqlite3_free_table(result);
    sqlite3_close(db);
    return app_database_file_path;
}


bool meta::set_future_app_database_file_path(const std::string& file_path) {
    sqlite3 * db;
    int rc = sqlite3_open(meta_database_file_path.c_str(), &db);
    if (rc) {
        return false;
    }
    std::string sql = "update meta set future_app_database_file_path = '" + file_path + "' where id = 0;";
    char *zErrMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        LOG(ERROR) << "SQL error: " << zErrMsg;
        return false;
    }
    sqlite3_close(db);
    return true;
}

bool meta::set_now_app_database_file_path(const std::string& file_path) {
    sqlite3 * db;
    int rc = sqlite3_open(meta_database_file_path.c_str(), &db);
    if (rc) {
        return false;
    }
    std::string sql = "update meta set now_app_database_file_path = '" + file_path + "' where id = 0;";
    char *zErrMsg = nullptr;
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        LOG(ERROR) << "SQL error: " << zErrMsg;
        return false;
    }
    sqlite3_close(db);
    return true;
}

bool meta::delete_meta_database() {
    if (std::filesystem::exists(meta_database_file_path)) {
        std::filesystem::remove(meta_database_file_path);
    }
    return true;
}

bool meta::create_if_not_exist() {
    if (!check_meta_database_existence()) {
        return create_meta_database();
    }
    return true;
}

bool meta::check_meta_database_existence() {
    return std::filesystem::exists(meta_database_file_path);
}



