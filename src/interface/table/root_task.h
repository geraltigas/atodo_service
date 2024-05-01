//
// Created by jb030 on 30/04/2024.
//

#ifndef ATODO_SERVICE_ROOT_TASK_H
#define ATODO_SERVICE_ROOT_TASK_H

#include <vector>

namespace root_task {
    bool clear_all_root_tasks();
    std::vector<int64_t> get_all_root_tasks();
    bool insert_root_task(int64_t root_task_id);
    bool delete_root_task(int64_t root_task_id);
};

#endif //ATODO_SERVICE_ROOT_TASK_H
