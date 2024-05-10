//
// Created by jb030 on 01/05/2024.
//

#ifndef ATODO_SERVICE_TASK_UI_H
#define ATODO_SERVICE_TASK_UI_H

#include <cstdint>
#include <string>
#include <vector>

namespace task_ui {
    struct task_ui_t {
        int64_t task_id = -1;
        int64_t parent_task = -1;
        int64_t position_x{};
        int64_t position_y{};

        bool operator==(const task_ui_t &rhs) const {
            return task_id == rhs.task_id &&
                   position_x == rhs.position_x &&
                   position_y == rhs.position_y;
        }

        std::string to_string() const {
            return "task_id: " + std::to_string(task_id) + "\n" +
                   "position_x: " + std::to_string(position_x) + "\n" +
                   "position_y: " + std::to_string(position_y) + "\n";
        }
    };

    bool add_or_update_task_uis(const std::vector<task_ui::task_ui_t>& task_ui_list);
    bool add_or_update_task_ui(int64_t task_id, int64_t parent_task, int64_t position_x, int64_t position_y);
    task_ui_t get_task_ui_by_id(int64_t task_id);
    std::vector<task_ui_t> get_task_ui_by_parent_task(int64_t parent_task);
    bool delete_task_ui(int64_t task_id);
    bool clear_all_task_ui();
};


#endif //ATODO_SERVICE_TASK_UI_H
