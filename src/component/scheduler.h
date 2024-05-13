//
// Created by jb030 on 12/05/2024.
//

#ifndef ATODO_SERVICE_SCHEDULER_H
#define ATODO_SERVICE_SCHEDULER_H

#include <cstdint>
#include <string>
#include <type.h>
#include <vector>
#include <crow.h>

namespace scheduler {
    struct schedule_t;
    struct task_show_t;
    struct suspended_task_show_t;
    struct suspended_time_info_t;
    struct suspended_email_info_t;
    struct event_trigger_task_show_t;

    schedule_t
    schedule();

    struct schedule_t {
        std::vector<task_show_t> tasks;
        std::vector<suspended_task_show_t> suspended_tasks;
        std::vector<event_trigger_task_show_t> event_trigger_tasks;

        schedule_t();
        schedule_t(const std::vector<task_show_t> &tasks, const std::vector<suspended_task_show_t> &suspended_tasks,
                   const std::vector<event_trigger_task_show_t> &event_trigger_tasks);
        ~schedule_t();

        // copy constructor
        schedule_t(const schedule_t &other);
        // copy assignment
        schedule_t &operator=(const schedule_t &other);

        // move constructor
        schedule_t(schedule_t &&other) noexcept;
        // move assignment
        schedule_t &operator=(schedule_t &&other) noexcept;

        crow::json::wvalue to_json() const;
    };

    struct task_show_t {
        int64_t id;
        std::string name;
        std::string goal;
        int64_t deadline;
        bool in_work_time;

        task_show_t();
        ~task_show_t();
        task_show_t(int64_t id, const std::string &name, const std::string &goal, int64_t deadline, bool in_work_time);

        // copy constructor
        task_show_t(const task_show_t &other);
        // copy assignment
        task_show_t &operator=(const task_show_t &other);

        // move constructor
        task_show_t(task_show_t &&other) noexcept;
        // move assignment
        task_show_t &operator=(task_show_t &&other) noexcept;

        // operator for std::set
        bool operator<(const task_show_t &rhs) const;
    };

    struct suspended_time_info_t {
        int64_t time;

        suspended_time_info_t();
        explicit suspended_time_info_t(int64_t time);
        ~suspended_time_info_t();

        // copy constructor
        suspended_time_info_t(const suspended_time_info_t &other);
        // copy assignment
        suspended_time_info_t &operator=(const suspended_time_info_t &other);
    };

    struct suspended_email_info_t {
        std::string email;
        std::vector<std::string> keywords;

        suspended_email_info_t();
        suspended_email_info_t(const std::string &email, const std::vector<std::string> &keywords);
        ~suspended_email_info_t();

        // copy constructor
        suspended_email_info_t(const suspended_email_info_t &other);
        // copy assignment
        suspended_email_info_t &operator=(const suspended_email_info_t &other);

        // move constructor
        suspended_email_info_t(suspended_email_info_t &&other) noexcept;
        // move assignment
        suspended_email_info_t &operator=(suspended_email_info_t &&other) noexcept;
    };

    struct suspended_task_show_t {
        int64_t id;
        std::string name;
        std::string goal;
        int64_t deadline;
        bool in_work_time;
        suspended_task_type type;
        union {
            suspended_time_info_t time_info;
            suspended_email_info_t email_info;
        };

        suspended_task_show_t();
        ~suspended_task_show_t();

        // copy constructor
        suspended_task_show_t(const suspended_task_show_t &other);
        // copy assignment
        suspended_task_show_t &operator=(const suspended_task_show_t &other);

        // move constructor
        suspended_task_show_t(suspended_task_show_t &&other) noexcept;
        // move assignment
        suspended_task_show_t &operator=(suspended_task_show_t &&other) noexcept;

        // operator for std::set
        bool operator<(const suspended_task_show_t &rhs) const;
    };

    struct event_trigger_task_show_t {
        int64_t id;
        std::string name;
        std::string goal;
        int64_t deadline;
        bool in_work_time;
        std::string event_name;
        std::string event_description;

        event_trigger_task_show_t();
        event_trigger_task_show_t(int64_t id, const std::string &name, const std::string &goal, int64_t deadline,
                                  bool in_work_time, const std::string &event_name, const std::string &event_description);
        ~event_trigger_task_show_t();

        // copy constructor
        event_trigger_task_show_t(const event_trigger_task_show_t &other);
        // copy assignment
        event_trigger_task_show_t &operator=(const event_trigger_task_show_t &other);

        // move constructor
        event_trigger_task_show_t(event_trigger_task_show_t &&other) noexcept;
        // move assignment
        event_trigger_task_show_t &operator=(event_trigger_task_show_t &&other) noexcept;

        // operator for std::set
        bool operator<(const event_trigger_task_show_t &rhs) const;
    };

}

#endif //ATODO_SERVICE_SCHEDULER_H
