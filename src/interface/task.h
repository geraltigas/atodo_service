//
// Created by jb030 on 30/04/2024.
//

#ifndef ATODO_SERVICE_TASK_H
#define ATODO_SERVICE_TASK_H


#include <cstdint>
#include <string>
#include <type.h>
#include <vector>

namespace task {
    struct task_t {
        int64_t task_id = -1;
        int64_t root_task;
        std::string name;
        std::string goal;
        int64_t deadline;
        bool in_work_time;
        task_status status;
        int64_t parent_task;
    };

    bool add_task(task_t task);
    bool delete_task(int64_t task_id);
    bool update_task_name(int64_t task_id, std::string name);
    bool update_task_goal(int64_t task_id, std::string goal);
    bool update_task_deadline(int64_t task_id, int64_t deadline);
    bool update_task_in_work_time(int64_t task_id, bool in_work_time);
    bool update_task_status(int64_t task_id, task_status status);
    bool update_task_parent_task(int64_t task_id, int64_t parent_task);
    std::vector<task_t> get_all_tasks();
    task_t get_task_by_id(int64_t task_id);
    std::vector<task_t> get_tasks_by_root_task(int64_t root_task);
    std::vector<task_t> get_tasks_by_parent_task(int64_t parent_task);
};


#endif //ATODO_SERVICE_TASK_H
