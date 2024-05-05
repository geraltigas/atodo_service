//
// Created by jb030 on 04/05/2024.
//

#include "task_show_service.h"
#include <interface/task_show/task_show.h>

bool task_show_service::init_task_show_service(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/task_show/get_show_stack").methods("POST"_method)([](const crow::request &req) {
        std::vector<std::string> show_stack = task_show::get_show_stack();
        crow::json::wvalue response;
        response["show_stack"] = show_stack;
        return response;
    });

    CROW_ROUTE(app, "/task_show/get_show_data").methods("POST"_method)([](const crow::request &req) {
        task_show::show_data_t show_data = task_show::get_show_data();
        crow::json::wvalue response;
        crow::json::wvalue show_data_json = std::move(show_data.to_crow_json());
        response["nodes"] = std::move(show_data_json["nodes"]);
        response["edges"] = std::move(show_data_json["edges"]);
        response["node_connected_to_start"] = std::move(show_data_json["node_connected_to_start"]);
        response["node_connected_to_end"] = std::move(show_data_json["node_connected_to_end"]);
        return response;
    });

    return true;
}
