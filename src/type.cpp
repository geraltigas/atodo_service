//
// Created by jb030 on 10/05/2024.
//
#include <type.h>

std::string task_status_to_string(task_status status) {
    switch (status) {
        case task_status::todo:
            return "todo";
        case task_status::in_progress:
            return "in_progress";
        case task_status::paused:
            return "paused";
        case task_status::suspended:
            return "suspended";
        case task_status::done:
            return "done";
        default:
            return "unknown";
    }
}

std::string task_trigger_type_to_string(task_trigger_type type){
    switch (type) {
        case task_trigger_type::dependency:
            return "dependency";
        case task_trigger_type::event:
            return "event";
        default:
            return "unknown";
    }
}

std::string task_after_effect_type_to_string(task_after_effect_type type) {
    switch (type) {
        case task_after_effect_type::periodic:
            return "periodic";
        default:
            return "unknown";
    }
}

std::string suspended_task_type_to_string(suspended_task_type type) {
    switch (type) {
        case suspended_task_type::time:
            return "time";
        case suspended_task_type::email:
            return "email";
        default:
            return "unknown";
    }
}

task_status task_status_from_string(const std::string &status) {
    if (status == "todo") {
        return task_status::todo;
    } else if (status == "in_progress") {
        return task_status::in_progress;
    } else if (status == "paused") {
        return task_status::paused;
    } else if (status == "suspended") {
        return task_status::suspended;
    } else if (status == "done") {
        return task_status::done;
    } else {
        return task_status::todo;
    }
}

