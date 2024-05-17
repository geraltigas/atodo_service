//
// Created by jb030 on 17/05/2024.
//

#include "task_constraint.h"
#include <sqlite3.h>
#include <component/sql_prepare.h>
#include <glog/logging.h>
#include <interface/database.h>

bool task_constraint::set_task_constraint(const task_constraint::task_constraint_t &task_constraint) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("set_task_constraint");
    sqlite3_bind_int64(stmt, 1, task_constraint.id);
    sqlite3_bind_text(stmt, 2, task_constraint.dependency_constraint.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, task_constraint.subtask_constraint.c_str(), -1, SQLITE_STATIC);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " " << rc;
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

task_constraint::task_constraint_t task_constraint::get_task_constraint(int64_t id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_task_constraint");
    sqlite3_bind_int64(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " " << rc;
        return {};
    }
    task_constraint_t task_constraint;
    task_constraint.id = sqlite3_column_int64(stmt, 0);
    task_constraint.dependency_constraint = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    task_constraint.subtask_constraint = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
    sqlite3_reset(stmt);
    return task_constraint;
}

bool task_constraint::delete_task_constraint(int64_t id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_task_constraint");
    sqlite3_bind_int64(stmt, 1, id);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " " << rc;
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}




