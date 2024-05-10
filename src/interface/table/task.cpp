//
// Created by jb030 on 30/04/2024.
//

#include "task.h"
#include "component/sql_prepare.h"
#include "glog/logging.h"
#include "interface/database.h"
#include "task_relation.h"
#include "task_trigger.h"
#include "task_after_effect.h"
#include <interface/table/app_state.h>
#include <interface/table/suspended_task.h>
#include <interface/table/task_ui.h>

#include <utility>

int64_t task::add_task(const task::task_t &task) {
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
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " " << "insert_task";
        sqlite3_reset(stmt);
        return -1;
    }
    int64_t task_id = sqlite3_last_insert_rowid(database::get_sqlite_db());
    sqlite3_reset(stmt);
    return task_id;
}

bool task::delete_task(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_task");
    sqlite3_bind_int64(stmt, 1, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " " << "delete_task";
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
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " " << "clear_all_tasks";
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
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " " << "update_task_name";
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
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " " << "update_task_goal";
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
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " "
                   << "update_task_deadline";
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
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " "
                   << "update_task_in_work_time";
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
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " "
                   << "update_task_status";
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
        LOG(ERROR) << "sqlite3_step failed: " << sqlite3_errmsg(database::get_sqlite_db()) << " "
                   << "update_task_parent_task";
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

int64_t task::add_task_default(std::string name, std::string goal, int64_t deadline, bool in_work_time) {
    task::task_t task;
    task.root_task = app_state::get_root_task();
    task.name = std::move(name);
    task.goal = std::move(goal);
    task.deadline = deadline;
    task.in_work_time = in_work_time;
    task.status = task_status::todo;
    task.parent_task = app_state::get_now_viewing_task();
    int64_t task_id = add_task(task);
    task_ui::add_or_update_task_ui(task_id, task.parent_task, 0, 0);
    return task_id;
}

bool task::eliminate_task(int64_t task_id) {
    task::task_t task = get_task_by_id(task_id);
    if (task.task_id == -1) {
        return false;
    }
    std::vector<task::task_t> tasks = get_tasks_by_parent_task(task_id);
    for (auto &i : tasks) {
        eliminate_task(i.task_id);
    }
    task_ui::delete_task_ui(task_id);
    task_relation::remove_all_related_relations(task_id);
    return delete_task(task_id);
}

task::task_detail_t task::get_detailed_task(int64_t task_id) {
    task::task_t task = get_task_by_id(task_id);
    task_detail_t task_detail;
    task_detail.task_id = task_id;
    task_detail.name = task.name;
    task_detail.goal = task.goal;
    task_detail.deadline = std::to_string(task.deadline);
    task_detail.in_work_time = task.in_work_time;
    task_detail.status = task_status_to_string(task.status);
    std::vector<task_trigger::task_trigger_t> task_triggers = task_trigger::get_task_triggers_by_id(task_id);
    for (auto &i : task_triggers) {
        if (i.type == task_trigger_type::dependency) {
            task_detail.trigger_type.push_back(task_trigger_type_to_string(i.type));
        } else {
            task_detail.trigger_type.push_back(task_trigger_type_to_string(i.type));
            task_detail.event_name = i.event.event_name;
            task_detail.event_description = i.event.event_description;
        }
    }

    std::vector<task_after_effect::after_effect_t> after_effects = task_after_effect::get_after_effects_by_id(task_id);
    for (auto &i : after_effects) {
        task_detail.after_effect_type.push_back(task_after_effect_type_to_string(i.type));
        task_detail.now_at = i.periodic.now_at;
        task_detail.period = i.periodic.period;
        task_detail.intervals = i.periodic.intervals;
    }

    if(task.status == task_status::suspended) {
        suspended_task::suspended_task_t suspended_task = suspended_task::get_suspended_task(task_id);
        if (suspended_task.task_id != -1) {
            if (suspended_task.type == suspended_task_type::time) {
                task_detail.suspended_task_type.push_back(suspended_task_type_to_string(suspended_task.type));
                task_detail.resume_time = std::to_string(suspended_task.time_info.timestamp);
            } else {
                task_detail.suspended_task_type.push_back(suspended_task_type_to_string(suspended_task.type));
                task_detail.email = suspended_task.email_info.email;
                task_detail.keywords = suspended_task.email_info.keywords;
            }
        }
    }

    return task_detail;
}

bool task::set_detailed_task(const task_detail_t &task) {
    task::task_t task_ = get_task_by_id(task.task_id);
    task_.name = task.name;
    task_.goal = task.goal;
    task_.deadline = std::stoll(task.deadline);
    task_.in_work_time = task.in_work_time;
    task_.status = task_status_from_string(task.status);
    task_.parent_task = app_state::get_now_viewing_task();
    update_task_name(task_.task_id, task_.name);
    update_task_goal(task_.task_id, task_.goal);
    update_task_deadline(task_.task_id, task_.deadline);
    update_task_in_work_time(task_.task_id, task_.in_work_time);
    update_task_status(task_.task_id, task_.status);
    update_task_parent_task(task_.task_id, task_.parent_task);
    task_trigger::delete_task_triggers_by_id(task_.task_id);
    for (auto &i : task.trigger_type) {
        if (i == "dependency") {
            LOG(ERROR) << "task_trigger_type::dependency is not supported";
        } else {
            task_trigger::task_trigger_t task_trigger;
            task_trigger.task_id = task_.task_id;
            task_trigger.type = task_trigger_type::event;
            task_trigger.event = task_trigger::event_t();
            task_trigger.event.event_name = task.event_name;
            task_trigger.event.event_description = task.event_description;
            task_trigger::add_or_update_task_trigger(task_trigger);
        }
    }

    task_after_effect::delete_after_effect_by_id(task_.task_id);
    for (auto &i : task.after_effect_type) {
        if (i == "periodic") {
            task_after_effect::after_effect_t after_effect;
            after_effect.id = task_.task_id;
            after_effect.type = task_after_effect_type::periodic;
            after_effect.periodic = task_after_effect::periodic_t();
            after_effect.periodic.now_at = task.now_at;
            after_effect.periodic.period = task.period;
            after_effect.periodic.intervals = task.intervals;
            task_after_effect::add_or_update_after_effect(after_effect);
        }
    }

    suspended_task::delete_suspended_task(task_.task_id);
    if (task.status == "suspended") {
        if (!task.suspended_task_type.empty()) {
            if (task.suspended_task_type[0] == "time") {
                suspended_task::suspended_task_t suspended_task;
                suspended_task.task_id = task_.task_id;
                suspended_task.type = suspended_task_type::time;
                suspended_task.time_info = suspended_task::time_task_info_t();
                suspended_task.time_info.timestamp = std::stoll(task.resume_time);
                suspended_task::add_suspended_task(suspended_task);
            } else {
                suspended_task::suspended_task_t suspended_task;
                suspended_task.task_id = task_.task_id;
                suspended_task.type = suspended_task_type::email;
                suspended_task.email_info = suspended_task::email_task_info_t();
                suspended_task.email_info.email = task.email;
                suspended_task.email_info.keywords = task.keywords;
                suspended_task::add_or_update_suspended_task(suspended_task);
            }
        }
    }

    return true;
}

bool task::task_t::operator==(const task::task_t &rhs) const {
    return task_id == rhs.task_id &&
           root_task == rhs.root_task &&
           name == rhs.name &&
           goal == rhs.goal &&
           deadline == rhs.deadline &&
           in_work_time == rhs.in_work_time &&
           status == rhs.status &&
           parent_task == rhs.parent_task;
}

bool task::task_t::equal_without_id(const task::task_t &rhs) const {
    return root_task == rhs.root_task &&
           name == rhs.name &&
           goal == rhs.goal &&
           deadline == rhs.deadline &&
           in_work_time == rhs.in_work_time &&
           status == rhs.status &&
           parent_task == rhs.parent_task;
}

std::string task::task_t::to_string() const {
    return "task_id: " + std::to_string(task_id) + "\n" +
           "root_task: " + std::to_string(root_task) + "\n" +
           "name: " + name + "\n" +
           "goal: " + goal + "\n" +
           "deadline: " + std::to_string(deadline) + "\n" +
           "in_work_time: " + std::to_string(in_work_time) + "\n" +
           "status: " + std::to_string(static_cast<int>(status)) + "\n" +
           "parent_task: " + std::to_string(parent_task) + "\n";
}

crow::json::wvalue task::task_detail_t::to_json() const {
    crow::json::wvalue json;
    json["task"]["task_id"] = task_id;
    json["task"]["name"] = name;
    json["task"]["goal"] = goal;
    json["task"]["deadline"] = deadline;
    json["task"]["in_work_time"] = in_work_time;
    json["task"]["status"] = status;
    std::vector<std::string> trigger_type_;
    trigger_type_.reserve(trigger_type.size());
    for (auto &i : trigger_type) {
        trigger_type_.push_back(i);
    }
    json["trigger_type"] = trigger_type_;
    std::vector<std::string> after_effect_;
    after_effect_.reserve(after_effect_type.size());
    for (auto &i : after_effect_type) {
        after_effect_.push_back(i);
    }
    json["after_effect_type"] = after_effect_;
    std::vector<std::string> suspended_task_type_;
    suspended_task_type_.reserve(suspended_task_type.size());
    for (auto &i : suspended_task_type) {
        suspended_task_type_.push_back(i);
    }
    json["suspended_task_type"] = suspended_task_type_;
    json["suspended_task"]["resume_time"] = resume_time;
    json["suspended_task"]["email"] = email;
    std::vector<std::string> keywords_;
    keywords_.reserve(keywords.size());
    for (auto &i : keywords) {
        keywords_.push_back(i);
    }
    json["suspended_task"]["keywords"] = keywords_;
    json["trigger"]["event_name"] = event_name;
    json["trigger"]["event_description"] = event_description;
    if (after_effect_type.empty()) {
        json["after_effect"]["now_at"] = -1;
        json["after_effect"]["period"] = -1;
        json["after_effect"]["intervals"] = std::vector<int64_t>();
    }else {
        json["after_effect"]["now_at"] = now_at;
        json["after_effect"]["period"] = period;
        std::vector<int64_t> intervals_;
        intervals_.reserve(intervals.size());
        for (auto &i : intervals) {
            intervals_.push_back(i);
        }
        json["after_effect"]["intervals"] = intervals_;
    }

    return json;
}

bool task::task_detail_t::operator==(const task::task_detail_t &rhs) const {
    bool trigger_type_equal = true;
    for (int i = 0; i < trigger_type.size(); i++) {
        if (trigger_type[i] != rhs.trigger_type[i]) {
            trigger_type_equal = false;
            break;
        }
    }

    bool after_effect_equal = true;
    for (int i = 0; i < after_effect_type.size(); i++) {
        if (after_effect_type[i] != rhs.after_effect_type[i]) {
            after_effect_equal = false;
            break;
        }
    }

    bool suspended_task_type_equal = true;
    for (int i = 0; i < suspended_task_type.size(); i++) {
        if (suspended_task_type[i] != rhs.suspended_task_type[i]) {
            suspended_task_type_equal = false;
            break;
        }
    }

    bool intervals_equal = true;
    for (int i = 0; i < intervals.size(); i++) {
        if (intervals[i] != rhs.intervals[i]) {
            intervals_equal = false;
            break;
        }
    }

    bool keywords_equal = true;
    for (int i = 0; i < keywords.size(); i++) {
        if (keywords[i] != rhs.keywords[i]) {
            keywords_equal = false;
            break;
        }
    }



    return name == rhs.name &&
           goal == rhs.goal &&
           deadline == rhs.deadline &&
           in_work_time == rhs.in_work_time &&
           status == rhs.status &&
           resume_time == rhs.resume_time &&
           email == rhs.email &&
           event_name == rhs.event_name &&
           event_description == rhs.event_description &&
           now_at == rhs.now_at &&
           period == rhs.period &&
           trigger_type_equal &&
           after_effect_equal &&
           suspended_task_type_equal &&
           intervals_equal &&
           keywords_equal;
}

void task::task_detail_t::from_json(const crow::json::rvalue& rvalue) {
    task_id = rvalue["task"]["task_id"].i();
    name = rvalue["task"]["name"].s();
    goal = rvalue["task"]["goal"].s();
    deadline = rvalue["task"]["deadline"].s();
    in_work_time = rvalue["task"]["in_work_time"].b();
    status = rvalue["task"]["status"].s();
    auto &trigger_type_ = rvalue["trigger_type"];
    for (auto &i : trigger_type_) {
        trigger_type.push_back(i.s());
    }
    auto &after_effect_ = rvalue["after_effect_type"];
    for (auto &i : after_effect_) {
        after_effect_type.push_back(i.s());
    }
    auto &suspended_task_type_ = rvalue["suspended_task_type"];
    for (auto &i : suspended_task_type_) {
        suspended_task_type.push_back(i.s());
    }
    event_name = rvalue["trigger"]["event_name"].s();
    event_description = rvalue["trigger"]["event_description"].s();
    now_at = rvalue["after_effect"]["now_at"].i();
    period = rvalue["after_effect"]["period"].i();
    auto &intervals_ = rvalue["after_effect"]["intervals"];
    for (auto &i : intervals_) {
        intervals.push_back(i.i());
    }
    resume_time = rvalue["suspended_task"]["resume_time"].s();
    email = rvalue["suspended_task"]["email"].s();
    auto &keywords_ = rvalue["suspended_task"]["keywords"];
    for (auto &i : keywords_) {
        keywords.push_back(i.s());
    }
}
