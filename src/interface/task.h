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

        bool operator==(const task_t &rhs) const {
            return task_id == rhs.task_id &&
                   root_task == rhs.root_task &&
                   name == rhs.name &&
                   goal == rhs.goal &&
                   deadline == rhs.deadline &&
                   in_work_time == rhs.in_work_time &&
                   status == rhs.status &&
                   parent_task == rhs.parent_task;
        }

        bool equal_without_id(const task_t &rhs) const {
            return root_task == rhs.root_task &&
                   name == rhs.name &&
                   goal == rhs.goal &&
                   deadline == rhs.deadline &&
                   in_work_time == rhs.in_work_time &&
                   status == rhs.status &&
                   parent_task == rhs.parent_task;
        }

        std::string to_string() const {
            return "task_id: " + std::to_string(task_id) + "\n" +
                   "root_task: " + std::to_string(root_task) + "\n" +
                   "name: " + name + "\n" +
                   "goal: " + goal + "\n" +
                   "deadline: " + std::to_string(deadline) + "\n" +
                   "in_work_time: " + std::to_string(in_work_time) + "\n" +
                   "status: " + std::to_string(static_cast<int>(status)) + "\n" +
                   "parent_task: " + std::to_string(parent_task) + "\n";
        }
    };

    int64_t add_task(task_t task);
    bool delete_task(int64_t task_id);
    bool clear_all_tasks();
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
