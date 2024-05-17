//
// Created by jb030 on 17/05/2024.
//

#ifndef ATODO_SERVICE_TASK_CONSTRAINT_H
#define ATODO_SERVICE_TASK_CONSTRAINT_H

#include <cstdint>
#include <string>

namespace task_constraint {
    struct task_constraint_t {
        int64_t id;
        std::string dependency_constraint;
        std::string subtask_constraint;
    };
    bool set_task_constraint(const task_constraint_t &task_constraint);
    task_constraint_t get_task_constraint(int64_t id);
    bool delete_task_constraint(int64_t id);
};

#endif //ATODO_SERVICE_TASK_CONSTRAINT_H
