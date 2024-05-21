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
        {"set_work_time", "update app_state set work_time = ? where id = 0;"},
        {"get_work_time", "select work_time from app_state where id = 0;"},
        {"set_now_doing_task", "update app_state set now_doing_task = ? where id = 0;"},
        {"get_now_doing_task", "select now_doing_task from app_state where id = 0;"},
        {"set_now_is_work_time", "update app_state set now_is_work_time = ? where id = 0;"},
        {"get_now_is_work_time", "select now_is_work_time from app_state where id = 0;"},
        {"get_all_root_tasks", "select id from root_task;"},
        {"insert_root_task", "insert into root_task (id) values (?);"},
        {"delete_root_task", "delete from root_task where id = ?;"},
        {"insert_task", "insert into task (root_task, name, goal, deadline, in_work_time, status, parent_task) values (?,?,?,?,?,?,?);"},
        {"delete_task", "delete from task where id = ?;"},
        {"clear_all_tasks", "delete from task where id != 0;"},
        {"count_sub_task_done", "select count(*) from task where parent_task = ? and status != 4;"},
        {"update_task_name", "update task set name = ? where id = ?;"},
        {"update_task_goal", "update task set goal = ? where id = ?;"},
        {"update_task_deadline", "update task set deadline = ? where id = ?;"},
        {"update_task_in_work_time", "update task set in_work_time = ? where id = ?;"},
        {"update_task_status", "update task set status = ? where id = ?;"},
        {"update_task_parent_task", "update task set parent_task = ? where id = ?;"},
        {"get_all_tasks", "select * from task;"},
        {"get_task_by_id", "select * from task where id = ?;"},
        {"get_tasks_by_root_task", "select * from task where root_task = ?;"},
        {"get_tasks_by_parent_task", "select * from task where parent_task = ?;"},
        {"have_sub_tasks", "select count(*) from task where parent_task = ?;"},
        {"get_sub_tasks", "select * from task where parent_task = ?;"},
        {"add_relation", "insert into task_relation (parent_task, source, target) values (?,?,?);"},
        {"delete_relation", "delete from task_relation where source = ? and target = ?;"},
        {"remove_all_related_relations", "delete from task_relation where source = ? or target = ?;"},
        {"clear_all_relations", "delete from task_relation;"},
        {"have_source_task", "select count(*) from task_relation where target = ?;"},
        {"get_target_tasks", "select target from task_relation where source = ?;"},
        {"get_source_tasks", "select source from task_relation where target = ?;"},
        {"get_relations_by_parent_task", "select * from task_relation where parent_task = ?;"},
        {"add_or_update_task_ui", "insert or replace into task_ui (id, parent_task, position_x, position_y) values (?,?,?,?);"},
        {"get_task_ui_by_parent_task", "select * from task_ui where parent_task = ?;"},
        {"get_task_ui_by_id", "select * from task_ui where id = ?;"},
        {"delete_task_ui", "delete from task_ui where id = ?;"},
        {"clear_all_task_ui", "delete from task_ui;"},
        {"add_suspended_task", "insert into suspended_task (id, type, info) values (?,?,?);"},
        {"add_or_update_suspended_task", "insert or replace into suspended_task (id, type, info) values (?,?,?);"},
        {"delete_suspended_task", "delete from suspended_task where id = ?;"},
        {"get_suspended_task", "select * from suspended_task where id = ?;"},
        {"get_suspended_task_by_type", "select * from suspended_task where type = ?;"},
        {"get_all_suspended_tasks", "select * from suspended_task;"},
        {"clear_all_suspended_tasks", "delete from suspended_task;"},
        {"add_or_update_task_trigger", "insert or replace into task_trigger (id, type, info) values (?,?,?);"},
        {"delete_task_triggers_by_id", "delete from task_trigger where id = ?;"},
        {"delete_task_trigger", "delete from task_trigger where id = ? and type = ?;"},
        {"get_task_trigger", "select * from task_trigger where id = ? and type = ?;"},
        {"get_task_triggers_by_id", "select * from task_trigger where id = ?;"},
        {"get_task_triggers_by_type", "select * from task_trigger where type = ?;"},
        {"get_all_task_triggers", "select * from task_trigger;"},
        {"clear_all_task_triggers", "delete from task_trigger;"},
        {"add_or_update_after_effect", "insert or replace into task_after_effect (id, type, info) values (?,?,?);"},
        {"delete_after_effect", "delete from task_after_effect where id = ? and type = ?;"},
        {"delete_after_effect_by_id", "delete from task_after_effect where id = ?;"},
        {"get_after_effect", "select * from task_after_effect where id = ? and type = ?;"},
        {"get_after_effects_by_id", "select * from task_after_effect where id = ?;"},
        {"get_after_effects_by_type", "select * from task_after_effect where type = ?;"},
        {"get_all_after_effects", "select * from task_after_effect;"},
        {"delete_all_after_effects", "delete from task_after_effect;"},
        {"set_task_constraint", "insert or replace into task_constraint (id, dependency_constraint, subtask_constraint) values (?,?,?);"},
        {"get_task_constraint", "select * from task_constraint where id = ?;"},
        {"delete_task_constraint", "delete from task_constraint where id = ?;"}
};

std::map<std::string, sqlite3_stmt *> sql_stmt_map;

bool sql_prepare::set_db(sqlite3 *db) {
    if (db == nullptr) {
        LOG(ERROR) << "db is nullptr";
        return false;
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
            return false;
        }
        sql_stmt_map[i[0]] = stmt;
    }
    return true;
}

sqlite3_stmt *sql_prepare::get_stmt(const char *key) {
    if (sql_stmt_map.find(key) != sql_stmt_map.end()) {
        return sql_stmt_map[key];
    }
    LOG(ERROR) << "key not found: " << key;
    if (sql_stmt_map.empty()) {
        LOG(ERROR) << "sql_stmt_map is empty, run app init first";
    }
    return nullptr;
}

bool sql_prepare::sql_finalize() {
    for (auto &i : sql_stmt_map) {
        int rc = sqlite3_finalize(i.second);
        if (rc != SQLITE_OK) {
            LOG(ERROR) << "sqlite3_finalize failed: " << sqlite3_errmsg(_db);
            return false;
        }
    }
    sql_stmt_map.clear();
    return true;
}


