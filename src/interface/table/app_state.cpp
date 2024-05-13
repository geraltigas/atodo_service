//
// Created by jb030 on 29/04/2024.
//

#include "app_state.h"
#include "component/sql_prepare.h"
#include "glog/logging.h"
#include "interface/database.h"
#include "task.h"

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

bool app_state::back_to_parent_task() {
    int64_t now_viewing_task = get_now_viewing_task();
    if (now_viewing_task == -1) {
        return false;
    }
    task::task_t task1 = task::get_task_by_id(now_viewing_task);
    if (task1.parent_task == -1) {
        return false;
    }
    set_now_viewing_task(task1.parent_task);
    return true;
}

bool app_state::set_work_time(int64_t work_time) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("set_work_time");
    sqlite3_bind_int64(stmt, 1, work_time);
    CHECK_ERROR(sqlite3_step(stmt));
    sqlite3_reset(stmt);
    return true;
}

int64_t app_state::get_work_time() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_work_time");
    CHECK_ERROR_SELECT(sqlite3_step(stmt));
    int64_t work_time = sqlite3_column_int64(stmt, 0);
    sqlite3_reset(stmt);
    return work_time;
}

bool app_state::set_today_work_start(bool today_work_start) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("set_today_work_start");
    sqlite3_bind_int(stmt, 1, today_work_start);
    CHECK_ERROR(sqlite3_step(stmt));
    sqlite3_reset(stmt);
    return true;
}

bool app_state::get_today_work_start() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_today_work_start");
    CHECK_ERROR_SELECT(sqlite3_step(stmt));
    bool today_work_start = sqlite3_column_int(stmt, 0);
    sqlite3_reset(stmt);
    return today_work_start;
}

bool app_state::set_now_doing_task(int64_t now_doing_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("set_now_doing_task");
    sqlite3_bind_int64(stmt, 1, now_doing_task);
    CHECK_ERROR(sqlite3_step(stmt));
    sqlite3_reset(stmt);
    return true;
}

int64_t app_state::get_now_doing_task() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_now_doing_task");
    CHECK_ERROR_SELECT(sqlite3_step(stmt));
    int64_t now_doing_task = sqlite3_column_int64(stmt, 0);
    sqlite3_reset(stmt);
    return now_doing_task;
}

bool app_state::set_now_is_work_time(bool now_is_work_time) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("set_now_is_work_time");
    sqlite3_bind_int(stmt, 1, now_is_work_time);
    CHECK_ERROR(sqlite3_step(stmt));
    sqlite3_reset(stmt);
    return true;
}

bool app_state::get_now_is_work_time() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_now_is_work_time");
    CHECK_ERROR_SELECT(sqlite3_step(stmt));
    bool now_is_working_time = sqlite3_column_int(stmt, 0);
    sqlite3_reset(stmt);
    return now_is_working_time;
}


