//
// Created by jb030 on 30/04/2024.
//

#ifndef ATODO_SERVICE_TYPE_H
#define ATODO_SERVICE_TYPE_H

#include <string>

enum class task_status : int {
    todo = 0,
//    in_progress = 1,
//    paused = 2,
    suspended = 3,
    done = 4
};

std::string task_status_to_string(task_status status);
task_status task_status_from_string(const std::string &status);

enum class task_trigger_type : int{
//    dependency = 0,
    event = 1
};

std::string task_trigger_type_to_string(task_trigger_type type);

enum class task_after_effect_type : int{
    periodic = 0
};

std::string task_after_effect_type_to_string(task_after_effect_type type);

enum class suspended_task_type : int{
    time = 0,
    email = 1
};

std::string suspended_task_type_to_string(suspended_task_type type);

using json = std::string;

#endif //ATODO_SERVICE_TYPE_H
