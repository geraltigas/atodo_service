//
// Created by jb030 on 03/05/2024.
//
#include <crow.h>
#include "service.h"
#include "constant.h"
#include "http_service/table/task_ui_service.h"
#include <http_service/table/task_service.h>
#include <http_service/table/task_relation_service.h>
#include <http_service/task_show/task_show_service.h>
#include <http_service/table/app_state_service.h>
#include <http_service/database_service.h>

crow::SimpleApp app;

bool service::init_service() {
    return
    database_service::init_database_service(app) &&
    task_show_service::init_task_show_service(app) &&
    task_service::init_task_service(app) &&
    task_ui_service::init_task_ui_service(app) &&
    task_relation_service::init_task_relation_service(app) &&
    app_state_service::init_app_state_service(app);
}

bool service::run_service(int64_t port) {
    app.port(port).run();
    return true;
}
