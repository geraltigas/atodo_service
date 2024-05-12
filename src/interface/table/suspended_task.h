//
// Created by jb030 on 30/04/2024.
//

#ifndef ATODO_SERVICE_SUSPENDED_TASK_H
#define ATODO_SERVICE_SUSPENDED_TASK_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <type.h>
#include <json/json.h>
#include <glog/logging.h>

namespace suspended_task {
    struct time_task_info_t;

    struct email_task_info_t;

    struct suspended_task_t;

    bool add_suspended_task(suspended_task_t suspended_task);

    bool add_or_update_suspended_task(suspended_task_t suspended_task);

    bool delete_suspended_task(int64_t task_id);

    suspended_task_t get_suspended_task(int64_t task_id);

    std::vector<suspended_task_t> get_suspended_task_by_type(suspended_task_type type);

    std::vector<suspended_task_t> get_all_suspended_tasks();

    bool clear_all_suspended_tasks();

    struct time_task_info_t  {
        int64_t timestamp{};

        bool operator==(const time_task_info_t &rhs) const;

        // constructor
        explicit time_task_info_t(int64_t timestamp);

        // assignment operator
        time_task_info_t &operator=(const time_task_info_t &time_task);

        time_task_info_t();

        [[nodiscard]] json to_json() const;

        static time_task_info_t from_json(const json &json_str);
    };

    struct email_task_info_t  {
        std::string email;
        std::vector<std::string> keywords;

        // move constructor
        email_task_info_t(email_task_info_t &&email_task) noexcept;

        // copy constructor
        email_task_info_t(const email_task_info_t &email_task);

        // copy assignment
        email_task_info_t &operator=(const email_task_info_t &email_task);

        // move assignment
        email_task_info_t &operator=(email_task_info_t &&email_task) noexcept;

        email_task_info_t() = default;

        // copy constructor with initializer list
        email_task_info_t(const std::string &email, const std::vector<std::string> &keywords);

        // move constructor with initializer list
        email_task_info_t(std::string &&email, std::vector<std::string> &&keywords);

        email_task_info_t(const char *email, std::initializer_list<const char *> keywords);

        bool operator==(const email_task_info_t &rhs) const;

        json to_json() const;

        static email_task_info_t from_json(const json &json_str);

        ~email_task_info_t();
    };

    struct suspended_task_t  {
        int64_t task_id = -1;
        suspended_task_type type;
        union {
            time_task_info_t time_info;
            email_task_info_t email_info;
        };

        bool operator==(const suspended_task_t &rhs) const;

        suspended_task_t();

        // copy constructor
        suspended_task_t(const suspended_task_t &suspended_task);

        // move assignment
        suspended_task_t &operator=(suspended_task_t &&suspended_task) noexcept;
        ~suspended_task_t();
    };
};


#endif //ATODO_SERVICE_SUSPENDED_TASK_H
