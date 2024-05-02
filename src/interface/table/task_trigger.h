//
// Created by jb030 on 02/05/2024.
//

#ifndef ATODO_SERVICE_TASK_TRIGGER_H
#define ATODO_SERVICE_TASK_TRIGGER_H

#include <cstdint>
#include <string>
#include <vector>
#include <type.h>

namespace task_trigger {
    struct dependency_t {
        dependency_t(int task_id);

        int64_t task_id = -1;

        dependency_t() = default;
        ~dependency_t() = default;

        // copy assignment operator
        dependency_t& operator=(const dependency_t&) = default;

        // copy constructor
        dependency_t(const dependency_t&) = default;

        json to_json() const;
        static dependency_t from_json(const json& j);
    };

    struct event_t {
        std::string event_name;
        std::string event_description;

        event_t() = default;
        ~event_t();

        // move constructor, event_name, event_description
        event_t(std::string&& event_name, std::string&& event_description);

        // move constructor
        event_t(event_t&&) noexcept ;

        // move assignment operator
        event_t& operator=(event_t&&) noexcept;

        // copy assignment operator
        event_t& operator=(const event_t& event);

        json to_json() const;
        static event_t from_json(const json& j);
    };

    struct task_trigger_t {
        int64_t task_id = -1;
        task_trigger_type type;
        union {
            dependency_t dependency;
            event_t event;
        };

        task_trigger_t();
        ~task_trigger_t();

        // move constructor
        task_trigger_t(task_trigger_t&& trigger) noexcept;

        // copy constructor
        task_trigger_t(const task_trigger_t& trigger);
    };

    bool add_or_update_task_trigger(task_trigger_t task_trigger);
    bool delete_task_trigger(int64_t task_id, task_trigger_type type);
    bool delete_task_triggers_by_id(int64_t task_id);
    task_trigger_t get_task_trigger(int64_t task_id, task_trigger_type type);
    std::vector<task_trigger_t> get_task_triggers_by_id(int64_t task_id);
    std::vector<task_trigger_t> get_task_triggers_by_type(task_trigger_type type);
    std::vector<task_trigger_t> get_all_task_triggers();
    bool clear_task_triggers();

};


#endif //ATODO_SERVICE_TASK_TRIGGER_H
