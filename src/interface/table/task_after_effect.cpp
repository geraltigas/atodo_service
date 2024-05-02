//
// Created by jb030 on 02/05/2024.
//

#include "task_after_effect.h"
#include <component/sql_prepare.h>
#include <string>

task_after_effect::periodic_t::periodic_t(int64_t now_at, std::vector<int64_t> intervals) : now_at(now_at), period(intervals.size()), intervals(std::move(intervals)) {}

task_after_effect::periodic_t::periodic_t(task_after_effect::periodic_t && periodic) noexcept : now_at(periodic.now_at), period(periodic.period), intervals(std::move(periodic.intervals)) {}

task_after_effect::periodic_t &task_after_effect::periodic_t::operator=(task_after_effect::periodic_t && periodic) noexcept {
    new (this) periodic_t(std::move(periodic));
    return *this;
}

task_after_effect::periodic_t &task_after_effect::periodic_t::operator=(const task_after_effect::periodic_t & periodic) {
    new (this) periodic_t(periodic);
    return *this;
}

json task_after_effect::periodic_t::to_json() const {
    Json::Value root;
    root["now_at"] = now_at;
    root["period"] = period;
    Json::Value intervals_json;
    for (const auto &interval : intervals) {
        intervals_json.append(interval);
    }
    root["intervals"] = intervals_json;
    return root.toStyledString();
}

task_after_effect::periodic_t::periodic_t() {
    now_at = -1;
    period = -1;
    intervals = {};
}

task_after_effect::periodic_t::~periodic_t() {
    intervals.clear();
}

task_after_effect::periodic_t task_after_effect::periodic_t::from_json(const json &j) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(j, root);


    periodic_t periodic;
    periodic.now_at = root["now_at"].asInt64();
    periodic.period = root["period"].asInt64();
    for (const auto &interval : root["intervals"]) {
        periodic.intervals.push_back(interval.asInt64());
    }
    return std::move(periodic);
}

bool task_after_effect::periodic_t::operator==(const task_after_effect::periodic_t &rhs) const {
    bool intervals_equal = true;
    for (int i = 0; i < period; i++) {
        if (intervals[i] != rhs.intervals[i]) {
            intervals_equal = false;
            break;
        }
    }
    return now_at == rhs.now_at && period == rhs.period && intervals_equal;
}

task_after_effect::periodic_t::periodic_t(const task_after_effect::periodic_t & periodic) = default;


bool task_after_effect::add_or_update_after_effect(const task_after_effect::after_effect_t &after_effect) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("add_or_update_after_effect");

    sqlite3_bind_int64(stmt, 1, after_effect.id);
    sqlite3_bind_int(stmt, 2, static_cast<int>(after_effect.type));
    std::string info;
    switch (after_effect.type) {
        case task_after_effect_type::periodic:
            info = after_effect.periodic.to_json();
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

bool task_after_effect::delete_after_effect(int64_t id, task_after_effect_type type) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_after_effect");

    sqlite3_bind_int64(stmt, 1, id);
    sqlite3_bind_int(stmt, 2, static_cast<int>(type));

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

bool task_after_effect::delete_after_effect_by_id(int64_t id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_after_effect_by_id");

    sqlite3_bind_int64(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

task_after_effect::after_effect_t task_after_effect::get_after_effect(int64_t id, task_after_effect_type type) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_after_effect");

    sqlite3_bind_int64(stmt, 1, id);
    sqlite3_bind_int(stmt, 2, static_cast<int>(type));

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_reset(stmt);
        return {};
    }

    after_effect_t after_effect;
    after_effect.id = sqlite3_column_int64(stmt, 0);
    after_effect.type = static_cast<task_after_effect_type>(sqlite3_column_int(stmt, 1));
    std::string info(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
    switch (after_effect.type) {
        case task_after_effect_type::periodic:
            after_effect.periodic = std::move(task_after_effect::periodic_t::from_json(info));
            break;
    }
    sqlite3_reset(stmt);
    return std::move(after_effect);
}

std::vector<task_after_effect::after_effect_t> task_after_effect::get_after_effects_by_id(int64_t id) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_after_effects_by_id");

    sqlite3_bind_int64(stmt, 1, id);

    std::vector<after_effect_t> after_effects;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        after_effect_t after_effect;
        after_effect.id = sqlite3_column_int64(stmt, 0);
        after_effect.type = static_cast<task_after_effect_type>(sqlite3_column_int(stmt, 1));
        std::string info(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        switch (after_effect.type) {
            case task_after_effect_type::periodic:
                after_effect.periodic = std::move(task_after_effect::periodic_t::from_json(info));
                break;
        }
        after_effects.push_back(after_effect);
    }
    sqlite3_reset(stmt);
    return std::move(after_effects);
}

std::vector<task_after_effect::after_effect_t> task_after_effect::get_after_effects_by_type(task_after_effect_type type) {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_after_effects_by_type");

    sqlite3_bind_int(stmt, 1, static_cast<int>(type));

    std::vector<after_effect_t> after_effects;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        after_effect_t after_effect;
        after_effect.id = sqlite3_column_int64(stmt, 0);
        after_effect.type = static_cast<task_after_effect_type>(sqlite3_column_int(stmt, 1));
        std::string info(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        switch (after_effect.type) {
            case task_after_effect_type::periodic:
                after_effect.periodic = std::move(task_after_effect::periodic_t::from_json(info));
                break;
        }
        after_effects.push_back(after_effect);
    }
    sqlite3_reset(stmt);
    return std::move(after_effects);
}

std::vector<task_after_effect::after_effect_t> task_after_effect::get_all_after_effects() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("get_all_after_effects");

    std::vector<after_effect_t> after_effects;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        after_effect_t after_effect;
        after_effect.id = sqlite3_column_int64(stmt, 0);
        after_effect.type = static_cast<task_after_effect_type>(sqlite3_column_int(stmt, 1));
        std::string info(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
        switch (after_effect.type) {
            case task_after_effect_type::periodic:
                after_effect.periodic = std::move(task_after_effect::periodic_t::from_json(info));
                break;
        }
        after_effects.push_back(after_effect);
    }
    sqlite3_reset(stmt);
    return std::move(after_effects);
}

bool task_after_effect::clear_all_after_effects() {
    sqlite3_stmt *stmt = sql_prepare::get_stmt("delete_all_after_effects");

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(stmt);
        return false;
    }
    sqlite3_reset(stmt);
    return true;
}

task_after_effect::after_effect_t::after_effect_t() {
    id = -1;
    type = task_after_effect_type::periodic;
    periodic = periodic_t();
}

task_after_effect::after_effect_t::~after_effect_t() {
    switch (type) {
        case task_after_effect_type::periodic:
            periodic.~periodic_t();
            break;
    }
}

task_after_effect::after_effect_t::after_effect_t(const task_after_effect::after_effect_t & after_effect) {
    id = after_effect.id;
    type = after_effect.type;
    switch (type) {
        case task_after_effect_type::periodic:
            new (&periodic) periodic_t(after_effect.periodic);
            break;
    }
}

task_after_effect::after_effect_t::after_effect_t(task_after_effect::after_effect_t && after_effect) noexcept {
    id = after_effect.id;
    type = after_effect.type;
    switch (type) {
        case task_after_effect_type::periodic:
            new (&periodic) periodic_t(std::move(after_effect.periodic));
            break;
    }
}

task_after_effect::after_effect_t &
task_after_effect::after_effect_t::operator=(const task_after_effect::after_effect_t & after_effect) {
    id = after_effect.id;
    type = after_effect.type;
    switch (type) {
        case task_after_effect_type::periodic:
            new (&periodic) periodic_t(after_effect.periodic);
            break;
    }
    return *this;
}

task_after_effect::after_effect_t &
task_after_effect::after_effect_t::operator=(task_after_effect::after_effect_t && after_effect) noexcept {
    id = after_effect.id;
    type = after_effect.type;
    switch (type) {
        case task_after_effect_type::periodic:
            new (&periodic) periodic_t(std::move(after_effect.periodic));
            break;
    }
    return *this;
}

bool task_after_effect::after_effect_t::operator==(const task_after_effect::after_effect_t &rhs) const {
    switch (type) {
        case task_after_effect_type::periodic:
            return id == rhs.id && type == rhs.type && periodic == rhs.periodic;
    }
}
