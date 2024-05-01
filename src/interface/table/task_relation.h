//
// Created by jb030 on 01/05/2024.
//

#ifndef ATODO_SERVICE_TASK_RELATION_H
#define ATODO_SERVICE_TASK_RELATION_H

#include <cstdint>
#include <vector>
#include <string>

namespace task_relation {
    bool add_relation(int64_t source_task, int64_t target_task);
    bool delete_relation(int64_t source_task, int64_t target_task);
    bool remove_all_related_relations(int64_t task_id);
    bool clear_all_relations();
    std::vector<int64_t> get_target_tasks(int64_t source_task);
    std::vector<int64_t> get_source_tasks(int64_t target_task);
};

#endif //ATODO_SERVICE_TASK_RELATION_H
