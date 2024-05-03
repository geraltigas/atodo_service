//
// Created by jb030 on 02/05/2024.
//

#ifndef ATODO_SERVICE_TASK_AFTER_EFFECT_H
#define ATODO_SERVICE_TASK_AFTER_EFFECT_H

#include <string>
#include <type.h>
#include <cstdint>
#include <vector>

namespace task_after_effect {
    struct periodic_t {
        int64_t now_at = 0;
        int64_t period = 0;
        std::vector<int64_t> intervals;

        periodic_t();
        ~periodic_t();

        periodic_t(int64_t now_at, std::vector<int64_t> intervals);

        // move constructor
        periodic_t(periodic_t &&) noexcept;

        // move assignment operator
        periodic_t &operator=(periodic_t &&) noexcept;

        // copy constructor
        periodic_t(const periodic_t &);

        // copy assignment operator
        periodic_t &operator=(const periodic_t &);

        json to_json() const;
        static periodic_t from_json(const json &j);

        bool operator==(const periodic_t &rhs) const;
    };

    struct after_effect_t {
        int64_t id;
        task_after_effect_type type;
        union {
            periodic_t periodic;
        };

        after_effect_t();
        ~after_effect_t();

        // copy constructor
        after_effect_t(const after_effect_t &);
        // move constructor
        after_effect_t(after_effect_t &&) noexcept;

        // copy assignment operator
        after_effect_t &operator=(const after_effect_t &);
        // move assignment operator
        after_effect_t &operator=(after_effect_t &&) noexcept;

        bool operator==(const after_effect_t &rhs) const;

    };

    bool add_or_update_after_effect(const after_effect_t &after_effect);
    bool delete_after_effect(int64_t id, task_after_effect_type type);
    bool delete_after_effect_by_id(int64_t id);
    after_effect_t get_after_effect(int64_t id, task_after_effect_type type);
    std::vector<after_effect_t> get_after_effects_by_id(int64_t id);
    std::vector<after_effect_t> get_after_effects_by_type(task_after_effect_type type);
    std::vector<after_effect_t> get_all_after_effects();
    bool clear_all_after_effects();
};


#endif //ATODO_SERVICE_TASK_AFTER_EFFECT_H
