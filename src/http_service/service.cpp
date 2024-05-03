//
// Created by jb030 on 03/05/2024.
//

#include "service.h"
#include "constant.h"
#include <crow.h>
#include <http_service/database_service.h>

crow::SimpleApp app;

bool service::init_service() {
    return database_service::init_database_service(app);
}

bool service::run_service(int64_t port) {
    app.port(port).run();
    return true;
}
