//
// Created by jb030 on 09/05/2024.
//

#include "app_state_service.h"
#include <interface/table/app_state.h>

bool app_state_service::init_app_state_service(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/app_state/set_now_viewing_task").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        response["status"] = app_state::set_now_viewing_task(request["now_viewing_task"].i());
        return response;
    });

    CROW_ROUTE(app, "/app_state/back_to_parent_task").methods("POST"_method)([](const crow::request &req) {
        crow::json::wvalue response;
        response["status"] = app_state::back_to_parent_task();
        return response;
    });

    return true;
}
