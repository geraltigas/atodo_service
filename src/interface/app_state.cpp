//
// Created by jb030 on 29/04/2024.
//

#include "app_state.h"
#include <component/sql_prepare.h>
#include <glog/logging.h>
#include <interface/database.h>

bool app_state::set_root_task(int64_t root_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("set_root_task");
    sqlite3_bind_int64(stmt, 1, root_task);
    CHECK_ERROR(sqlite3_step(stmt))
    sqlite3_reset(stmt);
    return true;
}

int64_t app_state::get_root_task() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_root_task");
    CHECK_ERROR_SELECT(sqlite3_step(stmt));
    int64_t root_task = sqlite3_column_int64(stmt, 0);
    sqlite3_reset(stmt);
    return root_task;
}

bool app_state::set_now_viewing_task(int64_t now_viewing_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("set_now_viewing_task");
    sqlite3_bind_int64(stmt, 1, now_viewing_task);
    CHECK_ERROR(sqlite3_step(stmt))
    sqlite3_reset(stmt);
    return true;
}

int64_t app_state::get_now_viewing_task() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_now_viewing_task");
    CHECK_ERROR_SELECT(sqlite3_step(stmt));
    int64_t now_viewing_task = sqlite3_column_int64(stmt, 0);
    sqlite3_reset(stmt);
    return now_viewing_task;
}

bool app_state::set_now_selected_task(int64_t now_selected_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("set_now_selected_task");
    sqlite3_bind_int64(stmt, 1, now_selected_task);
    CHECK_ERROR(sqlite3_step(stmt));
    sqlite3_reset(stmt);
    return true;
}

int64_t app_state::get_now_selected_task() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_now_selected_task");
    CHECK_ERROR_SELECT(sqlite3_step(stmt));
    int64_t now_selected_task = sqlite3_column_int64(stmt, 0);
    sqlite3_reset(stmt);
    return now_selected_task;
}


