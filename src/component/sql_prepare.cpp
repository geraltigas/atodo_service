//
// Created by jb030 on 29/04/2024.
//

#include "sql_prepare.h"
#include <map>
#include <string>
#include <glog/logging.h>

sqlite3 *_db = nullptr;

const char* key_sql_map[][2] = {
        {"test", "select * from task;"},
        {"set_root_task", "update app_state set root_task = ? where id = 0;"},
        {"get_root_task", "select root_task from app_state where id = 0;"},
        {"set_now_viewing_task", "update app_state set now_viewing_task = ? where id = 0;"},
        {"get_now_viewing_task", "select now_viewing_task from app_state where id = 0;"},
        {"set_now_selected_task", "update app_state set now_selected_task = ? where id = 0;"},
        {"get_now_selected_task", "select now_selected_task from app_state where id = 0;"},
        {"get_all_root_tasks", "select id from root_task;"},
        {"insert_root_task", "insert into root_task (id) values (?);"},
        {"delete_root_task", "delete from root_task where id = ?;"},
        {"insert_task", "insert into task (root_task, name, goal, dealine, in_work_time, status, parent_task) values (?,?,?,?,?,?,?);"},


};

std::map<std::string, sqlite3_stmt *> sql_stmt_map;

bool sql_prepare::set_db(sqlite3 *db) {
    if (db == nullptr) {
        LOG(ERROR) << "db is nullptr";
        throw std::runtime_error("db is nullptr");
    }
    _db = db;
    return true;
}

bool sql_prepare::sql_precompile() {
    if (_db == nullptr) {
        LOG(ERROR) << "db is nullptr";
        return false;
    }
    for (auto &i : key_sql_map) {
        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(_db, i[1], -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            LOG(ERROR) << "sqlite3_prepare_v2 failed: " << sqlite3_errmsg(_db) << " " << i[1];
            throw std::runtime_error("sqlite3_prepare_v2 failed");
        }
        sql_stmt_map[i[0]] = stmt;
    }
    return true;
}

sqlite3_stmt *sql_prepare::get_stmt(const char *key) {
    if (sql_stmt_map.find(key) != sql_stmt_map.end()) {
        return sql_stmt_map[key];
    }
    LOG(ERROR) << "key not found";
    if (sql_stmt_map.empty()) {
        LOG(ERROR) << "sql_stmt_map is empty, run app init first";
    }
    throw std::runtime_error("sql map key not found");
}

bool sql_prepare::sql_finalize() {
    for (auto &i : sql_stmt_map) {
        int rc = sqlite3_finalize(i.second);
        if (rc != SQLITE_OK) {
            LOG(ERROR) << "sqlite3_finalize failed: " << sqlite3_errmsg(_db);
            throw std::runtime_error("sqlite3_finalize failed");
        }
    }
    sql_stmt_map.clear();
    return true;
}


