//
// Created by jb030 on 06/05/2024.
//

#include "task_service.h"
#include <interface/table/task.h>

bool task_service::init_task_service(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/task/add_task_default").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        response["status"] = task::add_task_default(request["name"].s(), request["goal"].s(), request["deadline"].i(), request["in_work_time"].b());
        return response;
    });

    CROW_ROUTE(app, "/task/eliminate_task").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        response["status"] = task::eliminate_task(request["id"].i());
        return response;
    });

    CROW_ROUTE(app, "/task/get_detailed_task").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        response = task::get_detailed_task(request["id"].i()).to_json();
        return response;
    });

    CROW_ROUTE(app, "/task/set_detailed_task").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        task::task_detail_t task_detail;
        task_detail.from_json(request);
        crow::json::wvalue response;
        response["status"] = task::set_detailed_task(task_detail);
        return response;
    });

    return true;
}
