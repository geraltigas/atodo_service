//
// Created by jb030 on 30/04/2024.
//

#ifndef ATODO_SERVICE_TASK_H
#define ATODO_SERVICE_TASK_H

#include <cstdint>
#include <string>
#include "type.h"
#include <crow.h>
#include <vector>

namespace task {
    struct task_t;

    struct task_detail_t {
        int64_t task_id;
        std::string name;
        std::string goal;
        std::string deadline;
        bool in_work_time;
        std::string status;
        std::vector<std::string> trigger_type;
        std::vector<std::string> after_effect_type;
        std::vector<std::string> suspended_task_type;
        std::string resume_time;
        std::string email;
        std::vector<std::string> keywords;
        std::string event_name;
        std::string event_description;
        int64_t now_at;
        int64_t period;
        std::vector<int64_t> intervals;

        task_detail_t();

        [[nodiscard]] crow::json::wvalue to_json() const;

        bool operator==(const task_detail_t &rhs) const;

        void from_json(const crow::json::rvalue& rvalue1);
    };

    task_detail_t get_detailed_task(int64_t task_id);
    bool set_detailed_task(const task_detail_t &task);
    int64_t add_task(const task_t& task);
    int64_t add_task_default(std::string name, std::string goal, int64_t deadline, bool in_work_time);
    bool delete_task(int64_t task_id);
    bool eliminate_task(int64_t task_id);
    bool clear_all_tasks();
    bool update_task_name(int64_t task_id, std::string name);
    bool update_task_goal(int64_t task_id, std::string goal);
    bool update_task_deadline(int64_t task_id, int64_t deadline);
    bool update_task_in_work_time(int64_t task_id, bool in_work_time);
    bool update_task_status(int64_t task_id, task_status status);
    bool update_task_parent_task(int64_t task_id, int64_t parent_task);
    bool complete_task(int64_t task_id);
    std::vector<task_t> get_all_tasks();
    task_t get_task_by_id(int64_t task_id);
    std::vector<task_t> get_tasks_by_root_task(int64_t root_task);
    std::vector<task_t> get_tasks_by_parent_task(int64_t parent_task);
    std::vector<int64_t> get_sub_tasks(int64_t task_id);
    bool have_sub_tasks(int64_t task_id);

    struct task_t {
        int64_t task_id = -1;
        int64_t root_task;
        std::string name;
        std::string goal;
        int64_t deadline;
        bool in_work_time;
        task_status status;
        int64_t parent_task;

        bool operator==(const task_t &rhs) const;

        [[nodiscard]] bool equal_without_id(const task_t &rhs) const;

        [[nodiscard]] std::string to_string() const;
    };
}


#endif //ATODO_SERVICE_TASK_H
