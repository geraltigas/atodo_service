//
// Created by jb030 on 09/05/2024.
//

#include "task_relation_service.h"
#include <interface/table/task_relation.h>

bool task_relation_service::init_task_relation_service(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/task_relation/add_relation_default").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        const crow::json::rvalue& task_relations_json = request["task_relation"];
        response["status"] = task_relation::add_relation_default(task_relations_json["source"].i(), task_relations_json["target"].i());
        return response;
    });

    CROW_ROUTE(app, "/task_relation/delete_relation").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        const auto& task_relations_json = request["task_relation"];
        response["status"] = task_relation::delete_relation(task_relations_json["source"].i(), task_relations_json["target"].i());
        return response;
    });

    return true;
}
