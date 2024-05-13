//
// Created by jb030 on 12/05/2024.
//

#include "scheduler.h"
#include <interface/table/app_state.h>
#include <interface/table/task.h>
#include <interface/table/task_relation.h>
#include <interface/table/suspended_task.h>
#include <interface/table/task_trigger.h>
#include <set>
#include <type.h>

scheduler::schedule_t scheduler::schedule() {
    std::set<scheduler::task_show_t> tasks;
    std::set<scheduler::suspended_task_show_t> suspended_tasks;
    std::set<scheduler::event_trigger_task_show_t> event_trigger_tasks;

    int64_t now_viewing_task = app_state::get_root_task();
    std::set<int64_t> wait_for_viewing;
    wait_for_viewing.insert(now_viewing_task);
    suspended_task::suspended_task_t suspended_task_info;
    scheduler::suspended_task_show_t suspended_task;
    std::vector<int64_t> source_tasks;
    std::vector<int64_t> sub_tasks;
    std::vector<task_trigger::task_trigger_t> task_triggers;
    while (!wait_for_viewing.empty()) {
        int64_t task_id = *wait_for_viewing.begin();
        task::task_t task1 = task::get_task_by_id(task_id);
        switch (task1.status) {
            case task_status::suspended:
                suspended_task.id = task1.task_id;
                suspended_task.name = task1.name;
                suspended_task.goal = task1.goal;
                suspended_task.deadline = task1.deadline;
                suspended_task.in_work_time = task1.in_work_time;
                suspended_task_info = std::move(suspended_task::get_suspended_task(task1.task_id));
                switch (suspended_task_info.type) {
                    case suspended_task_type::time:
                        suspended_task.type = suspended_task_type::time;
                        suspended_task.time_info = suspended_time_info_t(suspended_task_info.time_info.timestamp);
                        break;
                    case suspended_task_type::email:
                        suspended_task.type = suspended_task_type::email;
                        suspended_task.email_info = suspended_email_info_t(suspended_task_info.email_info.email, suspended_task_info.email_info.keywords);
                        break;
                }
                suspended_tasks.insert(suspended_task);
                wait_for_viewing.erase(task_id);
                continue;
            case task_status::todo:
                source_tasks.clear();
                sub_tasks.clear();
                source_tasks = task_relation::get_source_tasks(task_id);
                if (!source_tasks.empty()) {
                    for (auto &i : source_tasks) {
                        wait_for_viewing.insert(i);
                    }
                    wait_for_viewing.erase(task_id);
                    continue;
                }
                if (task::have_sub_tasks(task_id)) {
                    sub_tasks = task::get_sub_tasks(task_id);
                    for (auto &i : sub_tasks) {
                        wait_for_viewing.insert(i);
                    }
                    wait_for_viewing.erase(task_id);
                    continue;
                }
                task_triggers.clear();
                task_triggers = task_trigger::get_task_triggers_by_id(task_id);
                if (task_triggers.size() == 1) {
                    event_trigger_tasks.insert(scheduler::event_trigger_task_show_t(task1.task_id, task1.name, task1.goal, task1.deadline, task1.in_work_time, task_triggers[0].event.event_name, task_triggers[0].event.event_description));
                }else {
                    tasks.insert(scheduler::task_show_t(task1.task_id, task1.name, task1.goal, task1.deadline, task1.in_work_time));
                }
                wait_for_viewing.erase(task_id);
                continue;
            case task_status::done:
                wait_for_viewing.erase(task_id);
                continue;
        }
    }
    return {std::vector<scheduler::task_show_t>(tasks.begin(), tasks.end()),
            std::vector<scheduler::suspended_task_show_t>(suspended_tasks.begin(), suspended_tasks.end()),
            std::vector<scheduler::event_trigger_task_show_t>(event_trigger_tasks.begin(), event_trigger_tasks.end())};
}

scheduler::task_show_t::task_show_t() {
    id = -1;
    name = "";
    goal = "";
    deadline = 0;
    in_work_time = false;
}

scheduler::task_show_t::task_show_t(const scheduler::task_show_t &other) {
    id = other.id;
    name = other.name;
    goal = other.goal;
    deadline = other.deadline;
    in_work_time = other.in_work_time;
}

scheduler::task_show_t &scheduler::task_show_t::operator=(const scheduler::task_show_t &other) = default;

scheduler::task_show_t::task_show_t(scheduler::task_show_t &&other) noexcept {
    id = other.id;
    name = std::move(other.name);
    goal = std::move(other.goal);
    deadline = other.deadline;
    in_work_time = other.in_work_time;
}

scheduler::task_show_t &scheduler::task_show_t::operator=(scheduler::task_show_t &&other) noexcept {
    id = other.id;
    name = std::move(other.name);
    goal = std::move(other.goal);
    deadline = other.deadline;
    in_work_time = other.in_work_time;
    return *this;
}

scheduler::task_show_t::~task_show_t() {
    id = -1;
    name = "";
    goal = "";
    deadline = 0;
    in_work_time = false;
}

scheduler::task_show_t::task_show_t(int64_t id, const std::string &name, const std::string &goal, int64_t deadline,
                                    bool in_work_time) {
    this->id = id;
    this->name = name;
    this->goal = goal;
    this->deadline = deadline;
    this->in_work_time = in_work_time;
}

bool scheduler::task_show_t::operator<(const scheduler::task_show_t &rhs) const {
    if (deadline != rhs.deadline) {
        return deadline < rhs.deadline;
    }
    return id < rhs.id;
}

scheduler::suspended_time_info_t::suspended_time_info_t() {
    time = 0;
}

scheduler::suspended_time_info_t::suspended_time_info_t(int64_t time) {
    this->time = time;
}

scheduler::suspended_time_info_t::suspended_time_info_t(const scheduler::suspended_time_info_t &other) {
    time = other.time;
}

scheduler::suspended_time_info_t::~suspended_time_info_t() = default;

scheduler::suspended_time_info_t &
scheduler::suspended_time_info_t::operator=(const scheduler::suspended_time_info_t &other) = default;

scheduler::suspended_email_info_t::suspended_email_info_t() {
    email = "";
    keywords = std::vector<std::string>();
}

scheduler::suspended_email_info_t::suspended_email_info_t(const std::string &email,
                                                          const std::vector<std::string> &keywords) {
    this->email = email;
    this->keywords = keywords;
}

scheduler::suspended_email_info_t::suspended_email_info_t(const scheduler::suspended_email_info_t &other) {
    email = other.email;
    keywords = other.keywords;
}

scheduler::suspended_email_info_t &
scheduler::suspended_email_info_t::operator=(const scheduler::suspended_email_info_t &other) = default;

scheduler::suspended_email_info_t::suspended_email_info_t(scheduler::suspended_email_info_t &&other) noexcept {
    email = std::move(other.email);
    keywords = std::move(other.keywords);
}

scheduler::suspended_email_info_t &
scheduler::suspended_email_info_t::operator=(scheduler::suspended_email_info_t &&other) noexcept {
    email = std::move(other.email);
    keywords = std::move(other.keywords);
    return *this;
}

scheduler::suspended_email_info_t::~suspended_email_info_t() {
    email = "";
    keywords.clear();
}

scheduler::suspended_task_show_t::suspended_task_show_t() {
    id = -1;
    name = "";
    goal = "";
    deadline = 0;
    in_work_time = false;
    type = suspended_task_type::time;
    time_info = suspended_time_info_t();
}

scheduler::suspended_task_show_t &
scheduler::suspended_task_show_t::operator=(const scheduler::suspended_task_show_t &other) {
    id = other.id;
    name = other.name;
    goal = other.goal;
    deadline = other.deadline;
    in_work_time = other.in_work_time;
    type = other.type;
    switch (type) {
        case suspended_task_type::time:
            time_info = other.time_info;
            break;
        case suspended_task_type::email:
            email_info = other.email_info;
            break;
    }
    return *this;
}

scheduler::suspended_task_show_t::suspended_task_show_t(const scheduler::suspended_task_show_t &other) {
    id = other.id;
    name = other.name;
    goal = other.goal;
    deadline = other.deadline;
    in_work_time = other.in_work_time;
    type = other.type;
    switch (type) {
        case suspended_task_type::time:
            time_info = other.time_info;
            break;
        case suspended_task_type::email:
            email_info = other.email_info;
            break;
    }
}

scheduler::suspended_task_show_t::suspended_task_show_t(scheduler::suspended_task_show_t &&other) noexcept {
    id = other.id;
    name = std::move(other.name);
    goal = std::move(other.goal);
    deadline = other.deadline;
    in_work_time = other.in_work_time;
    type = other.type;
    switch (type) {
        case suspended_task_type::time:
            time_info = suspended_time_info_t();
            time_info = other.time_info;
            break;
        case suspended_task_type::email:
            email_info = suspended_email_info_t();
            email_info = std::move(other.email_info);
            break;
    }
}

scheduler::suspended_task_show_t &
scheduler::suspended_task_show_t::operator=(scheduler::suspended_task_show_t &&other) noexcept {
    id = other.id;
    name = std::move(other.name);
    goal = std::move(other.goal);
    deadline = other.deadline;
    in_work_time = other.in_work_time;
    type = other.type;
    switch (type) {
        case suspended_task_type::time:
            time_info = suspended_time_info_t();
            time_info = other.time_info;
            break;
        case suspended_task_type::email:
            email_info = suspended_email_info_t();
            email_info = std::move(other.email_info);
            break;
    }
    return *this;
}

scheduler::suspended_task_show_t::~suspended_task_show_t() {
    id = -1;
    name = "";
    goal = "";
    deadline = 0;
    in_work_time = false;
    type = suspended_task_type::time;
    switch (type) {
        case suspended_task_type::time:
            time_info.~suspended_time_info_t();
            break;
        case suspended_task_type::email:
            email_info.~suspended_email_info_t();
            break;
    }
}

bool scheduler::suspended_task_show_t::operator<(const scheduler::suspended_task_show_t &rhs) const {
    if (type != rhs.type) {
        return type < rhs.type;
    }

    switch (type) {
        case suspended_task_type::time:
            return time_info.time < rhs.time_info.time;
        case suspended_task_type::email:
            if (email_info.email != rhs.email_info.email) {
                return email_info.email < rhs.email_info.email;
            }
            return email_info.keywords < rhs.email_info.keywords;
    }

    return id < rhs.id;
}

scheduler::event_trigger_task_show_t::event_trigger_task_show_t() {
    id = -1;
    name = "";
    goal = "";
    deadline = 0;
    in_work_time = false;
    event_name = "";
    event_description = "";
}

scheduler::event_trigger_task_show_t::~event_trigger_task_show_t() {
    id = -1;
    name = "";
    goal = "";
    deadline = 0;
    in_work_time = false;
    event_name = "";
    event_description = "";
}

scheduler::event_trigger_task_show_t::event_trigger_task_show_t(const scheduler::event_trigger_task_show_t &other) {
    id = other.id;
    name = other.name;
    goal = other.goal;
    deadline = other.deadline;
    in_work_time = other.in_work_time;
    event_name = other.event_name;
    event_description = other.event_description;
}

scheduler::event_trigger_task_show_t &
scheduler::event_trigger_task_show_t::operator=(const scheduler::event_trigger_task_show_t &other) = default;

scheduler::event_trigger_task_show_t::event_trigger_task_show_t(scheduler::event_trigger_task_show_t &&other) noexcept {
    id = other.id;
    name = std::move(other.name);
    goal = std::move(other.goal);
    deadline = other.deadline;
    in_work_time = other.in_work_time;
    event_name = std::move(other.event_name);
    event_description = std::move(other.event_description);
}

scheduler::event_trigger_task_show_t &
scheduler::event_trigger_task_show_t::operator=(scheduler::event_trigger_task_show_t &&other) noexcept {
    id = other.id;
    name = std::move(other.name);
    goal = std::move(other.goal);
    deadline = other.deadline;
    in_work_time = other.in_work_time;
    event_name = std::move(other.event_name);
    event_description = std::move(other.event_description);
    return *this;
}

bool scheduler::event_trigger_task_show_t::operator<(const scheduler::event_trigger_task_show_t &rhs) const {
    if (deadline != rhs.deadline) {
        return deadline < rhs.deadline;
    }
    return id < rhs.id;
}

scheduler::event_trigger_task_show_t::event_trigger_task_show_t(int64_t id, const std::string &name,
                                                                const std::string &goal, int64_t deadline,
                                                                bool in_work_time, const std::string &event_name,
                                                                const std::string &event_description) {
    this->id = id;
    this->name = name;
    this->goal = goal;
    this->deadline = deadline;
    this->in_work_time = in_work_time;
    this->event_name = event_name;
    this->event_description = event_description;
}

scheduler::schedule_t::schedule_t() {
    tasks = std::vector<scheduler::task_show_t>();
    suspended_tasks = std::vector<scheduler::suspended_task_show_t>();
    event_trigger_tasks = std::vector<scheduler::event_trigger_task_show_t>();
}

scheduler::schedule_t::~schedule_t() {
    tasks.clear();
    suspended_tasks.clear();
    event_trigger_tasks.clear();
}

scheduler::schedule_t::schedule_t(const scheduler::schedule_t &other) {
    tasks = other.tasks;
    suspended_tasks = other.suspended_tasks;
    event_trigger_tasks = other.event_trigger_tasks;
}

scheduler::schedule_t &scheduler::schedule_t::operator=(const scheduler::schedule_t &other) {
    tasks = other.tasks;
    suspended_tasks = other.suspended_tasks;
    event_trigger_tasks = other.event_trigger_tasks;
    return *this;
}

scheduler::schedule_t::schedule_t(scheduler::schedule_t &&other) noexcept {
    tasks = std::move(other.tasks);
    suspended_tasks = std::move(other.suspended_tasks);
    event_trigger_tasks = std::move(other.event_trigger_tasks);
}

scheduler::schedule_t &scheduler::schedule_t::operator=(scheduler::schedule_t &&other) noexcept {
    tasks = std::move(other.tasks);
    suspended_tasks = std::move(other.suspended_tasks);
    event_trigger_tasks = std::move(other.event_trigger_tasks);
    return *this;
}

scheduler::schedule_t::schedule_t(const std::vector<task_show_t> &tasks,
                                  const std::vector<suspended_task_show_t> &suspended_tasks,
                                  const std::vector<event_trigger_task_show_t> &event_trigger_tasks) {
    // move
    this->tasks = std::move(tasks);
    this->suspended_tasks = std::move(suspended_tasks);
    this->event_trigger_tasks = std::move(event_trigger_tasks);
}

crow::json::wvalue scheduler::schedule_t::to_json() const {
    std::vector<crow::json::wvalue> tasks_json;
    for (auto &task : tasks) {
        crow::json::wvalue task_json;
        task_json["id"] = task.id;
        task_json["name"] = task.name;
        task_json["goal"] = task.goal;
        task_json["deadline"] = task.deadline;
        task_json["in_work_time"] = task.in_work_time;
        tasks_json.push_back(std::move(task_json));
    }

    std::vector<crow::json::wvalue> suspended_tasks_json;
    for (auto &suspended_task : suspended_tasks) {
        crow::json::wvalue suspended_task_json;
        suspended_task_json["id"] = suspended_task.id;
        suspended_task_json["name"] = suspended_task.name;
        suspended_task_json["goal"] = suspended_task.goal;
        suspended_task_json["deadline"] = suspended_task.deadline;
        suspended_task_json["in_work_time"] = suspended_task.in_work_time;
        switch (suspended_task.type) {
            case suspended_task_type::time:
                suspended_task_json["type"] = "time";
                suspended_task_json["time_info"]["time"] = suspended_task.time_info.time;
                break;
            case suspended_task_type::email:
                suspended_task_json["type"] = "email";
                suspended_task_json["email_info"]["email"] = suspended_task.email_info.email;
                std::vector<crow::json::wvalue> keywords_json;
                for (auto &keyword : suspended_task.email_info.keywords) {
                    crow::json::wvalue keyword_json;
                    keyword_json = keyword;
                    keywords_json.push_back(std::move(keyword_json));
                }
                suspended_task_json["email_info"]["keywords"] = std::move(keywords_json);
                break;
        }
        suspended_tasks_json.push_back(std::move(suspended_task_json));
    }

    std::vector<crow::json::wvalue> event_trigger_tasks_json;
    for (auto &event_trigger_task : event_trigger_tasks) {
        crow::json::wvalue event_trigger_task_json;
        event_trigger_task_json["id"] = event_trigger_task.id;
        event_trigger_task_json["name"] = event_trigger_task.name;
        event_trigger_task_json["goal"] = event_trigger_task.goal;
        event_trigger_task_json["deadline"] = event_trigger_task.deadline;
        event_trigger_task_json["in_work_time"] = event_trigger_task.in_work_time;
        event_trigger_task_json["event_name"] = event_trigger_task.event_name;
        event_trigger_task_json["event_description"] = event_trigger_task.event_description;
        event_trigger_tasks_json.push_back(std::move(event_trigger_task_json));
    }

    crow::json::wvalue json;
    json["tasks"] = std::move(tasks_json);
    json["suspended_tasks"] = std::move(suspended_tasks_json);
    json["event_trigger_tasks"] = std::move(event_trigger_tasks_json);
    return json;
}
