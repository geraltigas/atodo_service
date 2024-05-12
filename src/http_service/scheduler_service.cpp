//
// Created by jb030 on 13/05/2024.
//

#include "scheduler_service.h"
#include <component/scheduler.h>

bool scheduler_service::init_scheduler_service(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/schedule").methods("POST"_method)([](const crow::request &req) {
        crow::json::wvalue response = scheduler::schedule().to_json();
        return response;
    });

    return true;
}
