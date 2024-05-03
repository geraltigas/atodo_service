//
// Created by jb030 on 30/04/2024.
//

#include "suspended_task.h"
#include <component/sql_prepare.h>
#include <json/json.h>
#include <glog/logging.h>

bool suspended_task::add_suspended_task(suspended_task::suspended_task_t suspended_task) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("add_suspended_task");

    sqlite3_bind_int64(stmt, 1, suspended_task.task_id);
    sqlite3_bind_int64(stmt, 2, static_cast<int64_t>(suspended_task.type));
    std::string info;
    switch (suspended_task.type) {
        case suspended_task_type::time:
            info = suspended_task.time_info.to_json();
            break;
        case suspended_task_type::email:
            info = suspended_task.email_info.to_json();
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

bool suspended_task::delete_suspended_task(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_suspended_task");
    sqlite3_bind_int64(stmt, 1, task_id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

suspended_task::suspended_task_t suspended_task::get_suspended_task(int64_t task_id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_suspended_task");
    sqlite3_bind_int64(stmt, 1, task_id);
    int rc;
    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        suspended_task_t suspended_task;
        suspended_task.task_id = sqlite3_column_int64(stmt, 0);
        suspended_task.type = static_cast<suspended_task_type>(sqlite3_column_int(stmt, 1));
        const char *info;
        switch (suspended_task.type) {
            case suspended_task_type::time:
                info = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
                suspended_task.time_info = suspended_task::time_task_info_t::from_json(info);
                break;
            case suspended_task_type::email:
                info = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
                suspended_task.email_info = suspended_task::email_task_info_t::from_json(info);
                break;
        }
        sqlite3_reset(stmt);
        return suspended_task;
    }
    sqlite3_reset(stmt);
    return {};
}

std::vector<suspended_task::suspended_task_t> suspended_task::get_suspended_task_by_type(suspended_task_type type) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_suspended_task_by_type");
    sqlite3_bind_int(stmt, 1, static_cast<int>(type));
    std::vector<suspended_task_t> suspended_tasks;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        suspended_task_t suspended_task;
        suspended_task.task_id = sqlite3_column_int64(stmt, 0);
        suspended_task.type = static_cast<suspended_task_type>(sqlite3_column_int(stmt, 1));
        switch (suspended_task.type) {
            case suspended_task_type::time:
                suspended_task.time_info = suspended_task::time_task_info_t::from_json(
                        std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2))));
                break;
            case suspended_task_type::email:
                suspended_task.email_info = suspended_task::email_task_info_t::from_json(
                        std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2))));
                break;
        }
        suspended_tasks.push_back(suspended_task);
    }
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return {};
    }
    sqlite3_reset(stmt);
    return suspended_tasks;
}

std::vector<suspended_task::suspended_task_t> suspended_task::get_all_suspended_tasks() {
    std::vector<suspended_task::suspended_task_t> suspended_tasks;
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_all_suspended_tasks");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        suspended_task::suspended_task_t suspended_task;
        suspended_task.task_id = sqlite3_column_int64(stmt, 0);
        suspended_task.type = static_cast<suspended_task_type>(sqlite3_column_int(stmt, 1));
        switch (suspended_task.type) {
            case suspended_task_type::time:
                suspended_task.time_info = suspended_task::time_task_info_t::from_json(
                        std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2))));
                break;
            case suspended_task_type::email:
                suspended_task.email_info = suspended_task::email_task_info_t::from_json(
                        std::string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2))));
                break;
        }
        suspended_tasks.push_back(suspended_task);
    }
    sqlite3_reset(stmt);
    return suspended_tasks;
}

bool suspended_task::clear_all_suspended_tasks() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("clear_all_suspended_tasks");
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool suspended_task::time_task_info_t::operator==(const suspended_task::time_task_info_t &rhs) const {
    return timestamp == rhs.timestamp;
}

suspended_task::time_task_info_t::time_task_info_t(int64_t timestamp) : timestamp(timestamp) {}

suspended_task::time_task_info_t &
suspended_task::time_task_info_t::operator=(const suspended_task::time_task_info_t &time_task) {
    if (this == &time_task) {
        return *this;
    }
    timestamp = time_task.timestamp;
    return *this;
}

suspended_task::time_task_info_t::time_task_info_t() {
    timestamp = -1;
}

json suspended_task::time_task_info_t::to_json() const {
    Json::Value root;
    root["timestamp"] = timestamp;
    return root.toStyledString();
}

suspended_task::time_task_info_t suspended_task::time_task_info_t::from_json(const json &json_str) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(json_str, root);
    time_task_info_t time_task;
    time_task.timestamp = root["timestamp"].asInt64();
    return time_task;
}

suspended_task::email_task_info_t::email_task_info_t(suspended_task::email_task_info_t &&email_task) noexcept {
    email = std::move(email_task.email);
    keywords = std::move(email_task.keywords);
}

suspended_task::email_task_info_t::email_task_info_t(const suspended_task::email_task_info_t &email_task) {
    email = email_task.email;
    keywords = email_task.keywords;
}

suspended_task::email_task_info_t &
suspended_task::email_task_info_t::operator=(const suspended_task::email_task_info_t &email_task) {
    if (this == &email_task) {
        return *this;
    }
    new(this) email_task_info_t(email_task.email, email_task.keywords);
    return *this;
}

suspended_task::email_task_info_t &
suspended_task::email_task_info_t::operator=(suspended_task::email_task_info_t &&email_task) noexcept {
    if (this == &email_task) {
        return *this;
    }
    new(this) email_task_info_t(std::move(email_task.email), std::move(email_task.keywords));
    return *this;
}

suspended_task::email_task_info_t::email_task_info_t(const std::string &email,
                                                     const std::vector<std::string> &keywords) : email(email),
                                                                                                 keywords(keywords) {}

suspended_task::email_task_info_t::email_task_info_t(std::string &&email, std::vector<std::string> &&keywords) : email(
        std::move(email)), keywords(std::move(keywords)) {}

suspended_task::email_task_info_t::email_task_info_t(const char *email, std::initializer_list<const char *> keywords)
        : email(email) {
    for (const auto &keyword: keywords) {
        this->keywords.emplace_back(keyword);
    }
}

bool suspended_task::email_task_info_t::operator==(const suspended_task::email_task_info_t &rhs) const {
    return email == rhs.email &&
           keywords == rhs.keywords;
}

json suspended_task::email_task_info_t::to_json() const {
    Json::Value root;
    root["email"] = email;
    Json::Value keywords_json;
    for (const auto &keyword: keywords) {
        keywords_json.append(keyword);
    }
    root["keywords"] = keywords_json;
    Json::StreamWriterBuilder builder;
    return Json::writeString(builder, root);
}

suspended_task::email_task_info_t suspended_task::email_task_info_t::from_json(const json &json_str) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(json_str, root);
    email_task_info_t email_task;
    email_task.email = root["email"].asString();
    for (const auto &keyword: root["keywords"]) {
        email_task.keywords.push_back(keyword.asString());
    }
    return email_task;
}

suspended_task::email_task_info_t::~email_task_info_t() {
    email.clear();
    keywords.clear();
}

bool suspended_task::suspended_task_t::operator==(const suspended_task::suspended_task_t &rhs) const {
    switch (type) {
        case suspended_task_type::time:
            return task_id == rhs.task_id && type == rhs.type && time_info == rhs.time_info;
        case suspended_task_type::email:
            return task_id == rhs.task_id && type == rhs.type && email_info == rhs.email_info;
    }
}

suspended_task::suspended_task_t::suspended_task_t() {
    task_id = -1;
    type = suspended_task_type::time;
    time_info = time_task_info_t();
}

suspended_task::suspended_task_t::suspended_task_t(const suspended_task::suspended_task_t &suspended_task) {
    task_id = suspended_task.task_id;
    type = suspended_task.type;
    switch (type) {
        case suspended_task_type::time:
            time_info = suspended_task.time_info;
            break;
        case suspended_task_type::email:
            email_info = suspended_task.email_info;
            break;
    }
}

suspended_task::suspended_task_t::~suspended_task_t() {
    switch (type) {
        case suspended_task_type::time:
            time_info.~time_task_info_t();
            break;
        case suspended_task_type::email:
            email_info.~email_task_info_t();
            break;
    }
}
