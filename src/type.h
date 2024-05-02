//
// Created by jb030 on 30/04/2024.
//

#ifndef ATODO_SERVICE_TYPE_H
#define ATODO_SERVICE_TYPE_H

enum class task_status : int {
    todo = 0,
    in_progress = 1,
    paused = 2,
    suspended = 3,
    done = 4
};

enum class task_trigger_type : int{
    dependency = 0,
    event = 1
};

enum class task_after_effect_type : int{
    periodic = 0
};

enum class suspended_task_type : int{
    time = 0,
    email = 1
};

using json = std::string;

#endif //ATODO_SERVICE_TYPE_H
