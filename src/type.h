//
// Created by jb030 on 30/04/2024.
//

#ifndef ATODO_SERVICE_TYPE_H
#define ATODO_SERVICE_TYPE_H

enum class task_status {
    todo = 0,
    in_progress = 1,
    paused = 2,
    suspended = 3,
    done = 4
};

enum class task_trigger_type {
    dependency = 0,
    event = 1,
    mix = 2
};

enum class task_after_effect_type {
    periodic = 0
};

enum class suspended_task_type {
    time = 0,
    email = 1
};

#endif //ATODO_SERVICE_TYPE_H
