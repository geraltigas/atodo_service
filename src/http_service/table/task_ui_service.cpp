//
// Created by jb030 on 09/05/2024.
//

#include "task_ui_service.h"
#include <interface/table/task_ui.h>

bool task_ui_service::init_task_ui_service(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/task_ui/add_task_uis").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        crow::json::rvalue task_uis_json = request["task_uis"];
        std::vector<task_ui::task_ui_t> task_uis;
        for (auto &task_ui_json : task_uis_json) {
            task_ui::task_ui_t task_ui;
            task_ui.task_id = task_ui_json["id"].i();
            task_ui.position_x = task_ui_json["position"]["x"].i();
            task_ui.position_y = task_ui_json["position"]["y"].i();
            task_uis.push_back(task_ui);
        }
        response["status"] = task_ui::add_or_update_task_uis(task_uis);
        return response;
    });

    return true;
}
