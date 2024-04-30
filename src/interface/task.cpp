//
// Created by jb030 on 30/04/2024.
//

#include "task.h"
#include <component/sql_prepare.h>

bool task::add_task(task::task_t task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("insert_task");
    sqlite3_bind_int64(stmt, 1, task.root_task);
    sqlite3_bind_text(stmt, 2, task.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, task.goal.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 4, task.deadline);
    return false;
}

bool task::update_task_name(int64_t task_id, std::string name) {

        return false;
}


