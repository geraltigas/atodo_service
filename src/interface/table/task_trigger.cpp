//
// Created by jb030 on 02/05/2024.
//

#include "task_trigger.h"
#include <component/sql_prepare.h>
#include <json/json.h>

bool task_trigger::add_or_update_task_trigger(task_trigger::task_trigger_t task_trigger) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("add_or_update_task_trigger");

    sqlite3_bind_int64(stmt, 1, task_trigger.task_id);
    sqlite3_bind_int(stmt, 2, static_cast<int>(task_trigger.type));
    std::string info;
    switch (task_trigger.type) {
        case task_trigger_type::dependency:
            info = task_trigger.dependency.to_json();
            break;
        case task_trigger_type::event:
            info = task_trigger.event.to_json();
            break;
    }
    sqlite3_bind_text(stmt, 3, info.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task_trigger::delete_task_trigger(int64_t task_id, task_trigger_type type) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_task_trigger");

    sqlite3_bind_int64(stmt, 1, task_id);
    sqlite3_bind_int(stmt, 2, static_cast<int>(type));

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task_trigger::delete_task_triggers_by_id(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_task_triggers_by_id");

    sqlite3_bind_int64(stmt, 1, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

task_trigger::task_trigger_t task_trigger::get_task_trigger(int64_t task_id, task_trigger_type type) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_task_trigger");

    sqlite3_bind_int64(stmt, 1, task_id);
    sqlite3_bind_int(stmt, 2, static_cast<int>(type));

    task_trigger_t task_trigger;
    task_trigger.task_id = task_id;
    task_trigger.type = type;

    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *info = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        switch (type) {
            case task_trigger_type::dependency:
                task_trigger.dependency = dependency_t::from_json(info);
                break;
            case task_trigger_type::event:
                task_trigger.event = event_t::from_json(info);
                break;
        }
    }
    sqlite3_reset(stmt);
    return std::move(task_trigger);
}

std::vector<task_trigger::task_trigger_t> task_trigger::get_task_triggers_by_id(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_task_triggers_by_id");

    sqlite3_bind_int64(stmt, 1, task_id);

    std::vector<task_trigger_t> task_triggers;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        task_trigger_t task_trigger;
        task_trigger.task_id = task_id;
        task_trigger.type = static_cast<task_trigger_type>(sqlite3_column_int(stmt, 1));
        const char *info = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        switch (task_trigger.type) {
            case task_trigger_type::dependency:
                task_trigger.dependency = dependency_t::from_json(info);
                break;
            case task_trigger_type::event:
                task_trigger.event = event_t::from_json(info);
                break;
        }
        task_triggers.push_back(std::move(task_trigger));
    }
    sqlite3_reset(stmt);
    return std::move(task_triggers);
}

std::vector<task_trigger::task_trigger_t> task_trigger::get_task_triggers_by_type(task_trigger_type type) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_task_triggers_by_type");

    sqlite3_bind_int(stmt, 1, static_cast<int>(type));

    std::vector<task_trigger_t> task_triggers;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        task_trigger_t task_trigger;
        task_trigger.task_id = sqlite3_column_int64(stmt, 0);
        task_trigger.type = type;
        const char *info = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        switch (type) {
            case task_trigger_type::dependency:
                task_trigger.dependency = dependency_t::from_json(info);
                break;
            case task_trigger_type::event:
                task_trigger.event = event_t::from_json(info);
                break;
        }
        task_triggers.push_back(std::move(task_trigger));
    }
    sqlite3_reset(stmt);
    return std::move(task_triggers);
}

std::vector<task_trigger::task_trigger_t> task_trigger::get_all_task_triggers() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_all_task_triggers");

    std::vector<task_trigger_t> task_triggers;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        task_trigger_t task_trigger;
        task_trigger.task_id = sqlite3_column_int64(stmt, 0);
        task_trigger.type = static_cast<task_trigger_type>(sqlite3_column_int(stmt, 1));
        const char *info = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        switch (task_trigger.type) {
            case task_trigger_type::dependency:
                task_trigger.dependency = dependency_t::from_json(info);
                break;
            case task_trigger_type::event:
                task_trigger.event = event_t::from_json(info);
                break;
        }
        task_triggers.push_back(std::move(task_trigger));
    }
    sqlite3_reset(stmt);
    return std::move(task_triggers);
}

bool task_trigger::clear_task_triggers() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("clear_all_task_triggers");

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

task_trigger::task_trigger_t::task_trigger_t() {
    type = task_trigger_type::dependency;
    dependency = dependency_t();
}

task_trigger::task_trigger_t::~task_trigger_t() {
    switch (type) {
        case task_trigger_type::dependency:
            dependency.~dependency_t();
            break;
        case task_trigger_type::event:
            event.~event_t();
            break;
    }
}

task_trigger::task_trigger_t::task_trigger_t(task_trigger::task_trigger_t &&trigger) noexcept {
    new(this) task_trigger_t();
    task_id = trigger.task_id;
    type = trigger.type;
    switch (type) {
        case task_trigger_type::dependency:
            dependency = trigger.dependency;
            break;
        case task_trigger_type::event:
            event = std::move(trigger.event);
            break;
    }
}

task_trigger::task_trigger_t::task_trigger_t(const task_trigger::task_trigger_t & trigger) {
    task_id = trigger.task_id;
    type = trigger.type;
    switch (type) {
        case task_trigger_type::dependency:
            dependency = trigger.dependency;
            break;
        case task_trigger_type::event:
            event = trigger.event;
            break;
    }
}

task_trigger::event_t::~event_t() {
    event_name.clear();
    event_description.clear();
}

json task_trigger::dependency_t::to_json() const {
    Json::Value root;
    root["task_id"] = task_id;
    return root.toStyledString();
}

task_trigger::dependency_t task_trigger::dependency_t::from_json(const json &j) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(j, root);

    dependency_t dependency;
    dependency.task_id = root["task_id"].asInt64();
    return dependency;
}

task_trigger::dependency_t::dependency_t(int task_id) {
    this->task_id = task_id;
}

json task_trigger::event_t::to_json() const {
    Json::Value root;
    root["event_name"] = event_name;
    root["event_description"] = event_description;

    return root.toStyledString();
}

task_trigger::event_t &task_trigger::event_t::operator=(task_trigger::event_t &&event) noexcept {
    new(this) event_t(std::move(event.event_name), std::move(event.event_description));
    return *this;
}

task_trigger::event_t::event_t(std::string &&event_name, std::string &&event_description) {
    this->event_name = std::move(event_name);
    this->event_description = std::move(event_description);
}

task_trigger::event_t task_trigger::event_t::from_json(const json &j) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(j, root);

    event_t event;
    event.event_name = root["event_name"].asString();
    event.event_description = root["event_description"].asString();
    return std::move(event);
}

task_trigger::event_t::event_t(task_trigger::event_t &&event) noexcept {
    new(this) event_t(std::move(event.event_name), std::move(event.event_description));
}

task_trigger::event_t &task_trigger::event_t::operator=(const task_trigger::event_t &event) {
    new (this) event_t();
    event_name = event.event_name;
    event_description = event.event_description;
    return *this;
}
