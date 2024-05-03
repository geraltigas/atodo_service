//
// Created by jb030 on 30/04/2024.
//

#include "root_task.h"
#include "component/sql_prepare.h"
#include "glog/logging.h"
#include "interface/database.h"

std::vector<int64_t> root_task::get_all_root_tasks() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_all_root_tasks");
    std::vector<int64_t> root_tasks;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        root_tasks.push_back(sqlite3_column_int64(stmt, 0));
    }
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db());
        throw std::runtime_error("sqlite3_step failed");
    }
    sqlite3_reset(stmt);
    return root_tasks;
}

bool root_task::insert_root_task(int64_t root_task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("insert_root_task");
    sqlite3_bind_int64(stmt, 1, root_task_id);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db());
        throw std::runtime_error("sqlite3_step failed");
    }
    sqlite3_reset(stmt);
    return true;
}

bool root_task::delete_root_task(int64_t root_task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_root_task");
    sqlite3_bind_int64(stmt, 1, root_task_id);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db());
        throw std::runtime_error("sqlite3_step failed");
    }
    sqlite3_reset(stmt);
    return true;
}

bool root_task::clear_all_root_tasks() {
    std::vector<int64_t> root_tasks = get_all_root_tasks();
    for (auto &i : root_tasks) {
        delete_root_task(i);
    }
    return true;
}
