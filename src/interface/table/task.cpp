//
// Created by jb030 on 30/04/2024.
//

#include "task.h"
#include "component/sql_prepare.h"
#include "glog/logging.h"
#include "interface/database.h"

int64_t task::add_task(task::task_t task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("insert_task");
    sqlite3_bind_int64(stmt, 1, task.root_task);
    sqlite3_bind_text(stmt, 2, task.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, task.goal.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 4, task.deadline);
    sqlite3_bind_int64(stmt, 5, task.in_work_time);
    sqlite3_bind_int64(stmt, 6, static_cast<int>(task.status));
    sqlite3_bind_int64(stmt, 7, task.parent_task);

    int rc = sqlite3_step(stmt);
    // return the id of the task
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "insert_task";
        sqlite3_reset(stmt);
        return -1;
    }
    int64_t task_id = sqlite3_last_insert_rowid((sqlite3 *)database::get_sqlite_db());
    sqlite3_reset(stmt);
    return task_id;
}

bool task::delete_task(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_task");
    sqlite3_bind_int64(stmt, 1, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "delete_task";
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task::clear_all_tasks() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("clear_all_tasks");

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "clear_all_tasks";
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}


bool task::update_task_name(int64_t task_id, std::string name) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("update_task_name");
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "update_task_name";
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task::update_task_goal(int64_t task_id, std::string goal) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("update_task_goal");
    sqlite3_bind_text(stmt, 1, goal.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "update_task_goal";
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task::update_task_deadline(int64_t task_id, int64_t deadline) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("update_task_deadline");
    sqlite3_bind_int64(stmt, 1, deadline);
    sqlite3_bind_int64(stmt, 2, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "update_task_deadline";
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task::update_task_in_work_time(int64_t task_id, bool in_work_time) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("update_task_in_work_time");
    sqlite3_bind_int64(stmt, 1, in_work_time);
    sqlite3_bind_int64(stmt, 2, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "update_task_in_work_time";
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task::update_task_status(int64_t task_id, task_status status) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("update_task_status");
    sqlite3_bind_int64(stmt, 1, static_cast<int>(status));
    sqlite3_bind_int64(stmt, 2, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "update_task_status";
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task::update_task_parent_task(int64_t task_id, int64_t parent_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("update_task_parent_task");
    sqlite3_bind_int64(stmt, 1, parent_task);
    sqlite3_bind_int64(stmt, 2, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg((sqlite3 *)database::get_sqlite_db()) << " " << "update_task_parent_task";
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

std::vector<task::task_t> task::get_all_tasks() {
    std::vector<task::task_t> tasks;
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_all_tasks");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        task::task_t task;
        task.task_id = sqlite3_column_int64(stmt, 0);
        task.root_task = sqlite3_column_int64(stmt, 1);
        task.name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        task.goal = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
        task.deadline = sqlite3_column_int64(stmt, 4);
        task.in_work_time = sqlite3_column_int64(stmt, 5);
        task.status = static_cast<task_status>(sqlite3_column_int(stmt, 6));
        task.parent_task = sqlite3_column_int64(stmt, 7);
        tasks.push_back(task);
    }
    sqlite3_reset(stmt);
    return tasks;
}

task::task_t task::get_task_by_id(int64_t task_id) {
    task::task_t task;
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_task_by_id");
    sqlite3_bind_int64(stmt, 1, task_id);
    if (sqlite3_step(stmt) == SQLITE_ROW) { // if failed to get a row, this branch will not be executed
        task.task_id = sqlite3_column_int64(stmt, 0);
        task.root_task = sqlite3_column_int64(stmt, 1);
        task.name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        task.goal = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
        task.deadline = sqlite3_column_int64(stmt, 4);
        task.in_work_time = sqlite3_column_int64(stmt, 5);
        task.status = static_cast<task_status>(sqlite3_column_int(stmt, 6));
        task.parent_task = sqlite3_column_int64(stmt, 7);
    }
    sqlite3_reset(stmt);
    return task;
}

std::vector<task::task_t> task::get_tasks_by_root_task(int64_t root_task) {
    std::vector<task::task_t> tasks;
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_tasks_by_root_task");
    sqlite3_bind_int64(stmt, 1, root_task);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        task::task_t task;
        task.task_id = sqlite3_column_int64(stmt, 0);
        task.root_task = sqlite3_column_int64(stmt, 1);
        task.name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        task.goal = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
        task.deadline = sqlite3_column_int64(stmt, 4);
        task.in_work_time = sqlite3_column_int64(stmt, 5);
        task.status = static_cast<task_status>(sqlite3_column_int(stmt, 6));
        task.parent_task = sqlite3_column_int64(stmt, 7);
        tasks.push_back(task);
    }
    sqlite3_reset(stmt);
    return tasks;
}

std::vector<task::task_t> task::get_tasks_by_parent_task(int64_t parent_task) {
    std::vector<task::task_t> tasks;
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_tasks_by_parent_task");
    sqlite3_bind_int64(stmt, 1, parent_task);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        task::task_t task;
        task.task_id = sqlite3_column_int64(stmt, 0);
        task.root_task = sqlite3_column_int64(stmt, 1);
        task.name = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        task.goal = std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
        task.deadline = sqlite3_column_int64(stmt, 4);
        task.in_work_time = sqlite3_column_int64(stmt, 5);
        task.status = static_cast<task_status>(sqlite3_column_int(stmt, 6));
        task.parent_task = sqlite3_column_int64(stmt, 7);
        tasks.push_back(task);
    }
    sqlite3_reset(stmt);
    return tasks;
}
