//
// Created by jb030 on 01/05/2024.
//

#include "task_ui.h"
#include <component/sql_prepare.h>

bool task_ui::add_or_update_task_ui(int64_t task_id, int64_t parent_task, int64_t position_x, int64_t position_y) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("add_or_update_task_ui");
    sqlite3_bind_int64(stmt, 1, task_id);
    sqlite3_bind_int64(stmt, 2, parent_task);
    sqlite3_bind_int64(stmt, 3, position_x);
    sqlite3_bind_int64(stmt, 4, position_y);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

task_ui::task_ui_t task_ui::get_task_ui_by_id(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_task_ui_by_id");
    sqlite3_bind_int64(stmt, 1, task_id);
    int rc;
    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        task_ui_t task_ui;
        task_ui.task_id = sqlite3_column_int64(stmt, 0);
        task_ui.parent_task = sqlite3_column_int64(stmt, 1);
        task_ui.position_x = sqlite3_column_int64(stmt, 2);
        task_ui.position_y = sqlite3_column_int64(stmt, 3);
        sqlite3_reset(stmt);
        return task_ui;
    }
    sqlite3_reset(stmt);
    return {};
}

std::vector<task_ui::task_ui_t> task_ui::get_task_ui_by_parent_task(int64_t parent_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_task_ui_by_parent_task");
    sqlite3_bind_int64(stmt, 1, parent_task);
    std::vector<task_ui_t> task_ui_list;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        task_ui_t task_ui;
        task_ui.task_id = sqlite3_column_int64(stmt, 0);
        task_ui.parent_task = sqlite3_column_int64(stmt, 1);
        task_ui.position_x = sqlite3_column_int64(stmt, 2);
        task_ui.position_y = sqlite3_column_int64(stmt, 3);
        task_ui_list.push_back(task_ui);
    }
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return {};
    }
    sqlite3_reset(stmt);
    return task_ui_list;
}

bool task_ui::delete_task_ui(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_task_ui");
    sqlite3_bind_int64(stmt, 1, task_id);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task_ui::clear_all_task_ui() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("clear_all_task_ui");
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}
