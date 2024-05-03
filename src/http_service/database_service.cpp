//
// Created by jb030 on 03/05/2024.
//

#include "database_service.h"
#include "interface/database.h"

bool database_service::init_database_service(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/database/check_database_existence").methods("POST"_method)([](const crow::request &req) {
        crow::json::wvalue response;
        response["status"] = database::check_database_existence();
        return response;
    });

    CROW_ROUTE(app, "/database/get_database_file_path").methods("POST"_method)([](const crow::request &req) {
        crow::json::wvalue response;
        response["path"] = database::get_database_file_path();
        return response;
    });

    CROW_ROUTE(app, "/database/set_database_file_path").methods("POST"_method)([](const crow::request &req) {
        crow::json::rvalue request = crow::json::load(req.body);
        crow::json::wvalue response;
        response["status"] = database::set_database_file_path(request["path"].s());
        return response;
    });

    CROW_ROUTE(app, "/database/create_database").methods("POST"_method)([](const crow::request &req) {
        crow::json::wvalue response;
        response["status"] = database::create_database();
        return response;
    });

    CROW_ROUTE(app, "/database/create_if_not_exist").methods("POST"_method)([](const crow::request &req) {
        crow::json::wvalue response;
        response["status"] = database::create_if_not_exist();
        return response;
    });

    CROW_ROUTE(app, "/database/delete_database").methods("POST"_method)([](const crow::request &req) {
        crow::json::wvalue response;
        response["status"] = database::delete_database();
        return response;
    });

    return true;
}
