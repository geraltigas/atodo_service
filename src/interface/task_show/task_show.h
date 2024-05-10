//
// Created by jb030 on 04/05/2024.
//

#ifndef ATODO_SERVICE_TASK_SHOW_H
#define ATODO_SERVICE_TASK_SHOW_H

#include <string>
#include <vector>
#include "crow/json.h"

namespace task_show {
    struct show_edge_t;
    struct position_t;
    struct show_node_t;
    struct show_data_t;
    std::vector<std::string> get_show_stack();
    show_data_t get_show_data();
    show_data_t get_show_data_by_id(int64_t id);
    show_data_t set_now_viewing_and_get_show_data(int64_t id);
    enum class edge_type {
        default_e,
    };

    std::string edge_type_to_string(edge_type t);
    struct show_edge_t {
        std::string source;
        std::string target;

        show_edge_t();
        ~show_edge_t();

        // move constructor
        show_edge_t(show_edge_t &&other) noexcept;
        // move assignment
        show_edge_t &operator=(show_edge_t &&other) noexcept;
    };

    struct position_t {
        int64_t x;
        int64_t y;

        position_t();
        ~position_t();
        // copy constructor
        position_t(const position_t &other);
        // copy assignment
        position_t &operator=(const position_t &other);
    };

    enum class node_type {
        start,
        end,
        origin,
        task
    };

    std::string node_type_to_string(node_type t);

    struct show_node_t {
        std::string id;
        std::string name;
        position_t position;

        show_node_t();
        ~show_node_t();
        // move constructor
        show_node_t(show_node_t &&other) noexcept;
        // move assignment
        show_node_t &operator=(show_node_t &&other) noexcept;
        // copy constructor
        show_node_t(const show_node_t &other);
    };

    struct show_data_t {
        std::vector<show_node_t> nodes;
        std::vector<show_edge_t> edges;
        std::vector<std::string> node_connected_to_start;
        std::vector<std::string> node_connected_to_end;

        show_data_t();
        ~show_data_t();
        // move constructor
        show_data_t(show_data_t &&other) noexcept;
        // move assignment
        show_data_t &operator=(show_data_t &&other) noexcept ;

        crow::json::wvalue to_crow_json();
    };

}

#endif //ATODO_SERVICE_TASK_SHOW_H
