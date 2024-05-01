//
// Created by jb030 on 01/05/2024.
//

#include "task_relation.h"
#include <component/sql_prepare.h>
#include <glog/logging.h>
#include <interface/database.h>

bool task_relation::add_relation(int64_t source_task, int64_t target_task) {
    if (source_task == target_task) {
        LOG(ERROR) << "source_task and target_task cannot be the same";
        return false;
    }
    sqlite3_stmt *stmt = sql_prepare::get_stmt("add_relation");
    sqlite3_bind_int64(stmt, 1, source_task);
    sqlite3_bind_int64(stmt, 2, target_task);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db());
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task_relation::delete_relation(int64_t source_task, int64_t target_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_relation");
    sqlite3_bind_int64(stmt, 1, source_task);
    sqlite3_bind_int64(stmt, 2, target_task);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db());
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task_relation::remove_all_related_relations(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("remove_all_related_relations");
    sqlite3_bind_int64(stmt, 1, task_id);
    sqlite3_bind_int64(stmt, 2, task_id);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db());
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task_relation::clear_all_relations() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("clear_all_relations");
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db());
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

std::vector<int64_t> task_relation::get_target_tasks(int64_t source_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_target_tasks");
    sqlite3_bind_int64(stmt, 1, source_task);
    std::vector<int64_t> target_tasks;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        target_tasks.push_back(sqlite3_column_int64(stmt, 0));
    }
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db());
        throw std::runtime_error("sqlite3_step failed");
    }
    sqlite3_reset(stmt);
    return target_tasks;
}

std::vector<int64_t> task_relation::get_source_tasks(int64_t target_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_source_tasks");
    sqlite3_bind_int64(stmt, 1, target_task);
    std::vector<int64_t> source_tasks;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        source_tasks.push_back(sqlite3_column_int64(stmt, 0));
    }
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db());
        throw std::runtime_error("sqlite3_step failed");
    }
    sqlite3_reset(stmt);
    return source_tasks;
}



