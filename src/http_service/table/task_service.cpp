//
// Created by jb030 on 06/05/2024.
//

#include "task_service.h"
#include <interface/table/task.h>

std::tuple<bool, std::string> task_detail_input_check(const task::task_detail_t &task_detail) {
    static const std::vector<std::string> status_list = {"todo", "in_progress", "paused", "suspended", "done"};
    static const std::vector<std::string> trigger_type_list = {"event"};
    static const std::vector<std::string> after_effect_type_list = {"periodic"};
    static const std::vector<std::string> suspended_task_type_list = {"time", "email"};
    bool task_check = task_detail.task_id >= 0;
    bool name_check = !task_detail.name.empty();
    bool goal_check = !task_detail.goal.empty();
    bool deadline_check = !task_detail.deadline.empty();
    bool status_check = std::find(status_list.begin(), status_list.end(), task_detail.status) != status_list.end();
    bool trigger_type_check = std::all_of(task_detail.trigger_type.begin(), task_detail.trigger_type.end(), [](const std::string &trigger_type) {
        return std::find(trigger_type_list.begin(), trigger_type_list.end(), trigger_type) != trigger_type_list.end();
    });
    bool after_effect_type_check = std::all_of(task_detail.after_effect_type.begin(), task_detail.after_effect_type.end(), [](const std::string &after_effect_type) {
        return std::find(after_effect_type_list.begin(), after_effect_type_list.end(), after_effect_type) != after_effect_type_list.end();
    });
    bool suspended_task_type_check = std::all_of(task_detail.suspended_task_type.begin(), task_detail.suspended_task_type.end(), [](const std::string &suspended_task_type) {
        return std::find(suspended_task_type_list.begin(), suspended_task_type_list.end(), suspended_task_type) != suspended_task_type_list.end();
    });
    // no redundant
    bool trigger_type_no_redundant = std::all_of(task_detail.trigger_type.begin(), task_detail.trigger_type.end(), [&task_detail](const std::string &trigger_type) {
        return std::count(task_detail.trigger_type.begin(), task_detail.trigger_type.end(), trigger_type) == 1;
    });
    bool after_effect_type_no_redundant = std::all_of(task_detail.after_effect_type.begin(), task_detail.after_effect_type.end(), [&task_detail](const std::string &after_effect_type) {
        return std::count(task_detail.after_effect_type.begin(), task_detail.after_effect_type.end(), after_effect_type) == 1;
    });
    bool suspended_task_type_no_redundant = std::all_of(task_detail.suspended_task_type.begin(), task_detail.suspended_task_type.end(), [&task_detail](const std::string &suspended_task_type) {
        return std::count(task_detail.suspended_task_type.begin(), task_detail.suspended_task_type.end(), suspended_task_type) == 1;
    });
    // if "time“ in suspended_task_type, resume_time should not be empty
    bool resume_time_check = std::all_of(task_detail.suspended_task_type.begin(), task_detail.suspended_task_type.end(), [&task_detail](const std::string &suspended_task_type) {
        return suspended_task_type != "time" || !task_detail.resume_time.empty();
    });
    // if "email" in suspended_task_type, email and keywords should not be empty
    bool email_check = std::all_of(task_detail.suspended_task_type.begin(), task_detail.suspended_task_type.end(), [&task_detail](const std::string &suspended_task_type) {
        return suspended_task_type != "email" || (!task_detail.email.empty() && !task_detail.keywords.empty());
    });
    // if "event" in trigger_type, event_name and event_description should not be empty
    bool event_check = std::all_of(task_detail.trigger_type.begin(), task_detail.trigger_type.end(), [&task_detail](const std::string &trigger_type) {
        return trigger_type != "event" || (!task_detail.event_name.empty() && !task_detail.event_description.empty());
    });
    // if "periodic" in after_effect_type, now_at, period and intervals should not be empty
    bool periodic_check = std::all_of(task_detail.after_effect_type.begin(), task_detail.after_effect_type.end(), [&task_detail](const std::string &after_effect_type) {
        return after_effect_type != "periodic" || (task_detail.now_at >= 0 && task_detail.period >= 0 && !task_detail.intervals.empty());
    });

    if (!task_check) {
        return { false, "task_id should be non-negative" };
    }

    if (!name_check) {
        return { false, "name should not be empty" };
    }

    if (!goal_check) {
        return { false, "goal should not be empty" };
    }

    if (!deadline_check) {
        return { false, "deadline should not be empty" };
    }

    if (!status_check) {
        return { false, "status should be one of todo, in_progress, paused, suspended, done" };
    }

    if (!trigger_type_check) {
        return { false, "trigger_type should be one of event" };
    }

    if (!after_effect_type_check) {
        return { false, "after_effect_type should be one of periodic" };
    }

    if (!suspended_task_type_check) {
        return { false, "suspended_task_type should be one of time, email" };
    }

    if (!trigger_type_no_redundant) {
        return { false, "trigger_type should not be redundant" };
    }

    if (!after_effect_type_no_redundant) {
        return { false, "after_effect_type should not be redundant" };
    }

    if (!suspended_task_type_no_redundant) {
        return { false, "suspended_task_type should not be redundant" };
    }

    if (!resume_time_check) {
        return { false, "resume_time should not be empty if suspended_task_type contains time" };
    }

    if (!email_check) {
        return { false, "email and keywords should not be empty if suspended_task_type contains email" };
    }

    if (!event_check) {
        return { false, "event_name and event_description should not be empty if trigger_type contains event" };
    }

    if (!periodic_check) {
        return { false, "now_at, period and intervals should not be empty if after_effect_type contains periodic" };
    }

    return { true, "" };
}

bool task_service::init_task_service(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/task/add_task_default").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        response["status"] = task::add_task_default(request["name"].s(), request["goal"].s(), request["deadline"].i(), request["in_work_time"].b());
        return response;
    });

    CROW_ROUTE(app, "/task/eliminate_task").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        response["status"] = task::eliminate_task(request["id"].i());
        return response;
    });

    CROW_ROUTE(app, "/task/get_detailed_task").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        response = task::get_detailed_task(request["id"].i()).to_json();
        return response;
    });

    CROW_ROUTE(app, "/task/set_detailed_task").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        task::task_detail_t task_detail;
        task_detail.from_json(request);
        auto [check, msg] = task_detail_input_check(task_detail);
        crow::json::wvalue response;
        if (!check) {
            // return error code
            response["status"] = false;
            response["msg"] = msg;
            return response;
        }
        response["status"] = task::set_detailed_task(task_detail);
        return response;
    });

    return true;
}
