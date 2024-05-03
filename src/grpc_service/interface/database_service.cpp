//
// Created by jb030 on 02/05/2024.
//

#include "database_service.h"
#include <grpc/database.grpc.pb.h>
#include <interface/database.h>

class database_service_impl final : public database::Database::Service {
public:
    ::grpc::Status CheckDatabaseExistence(::grpc::ServerContext* context, const ::database::Empty* request, ::database::CallStatus* response) override {
        response->set_success(database::check_database_existence());
        return ::grpc::Status::OK;
    }
    ::grpc::Status GetDatabasePath(::grpc::ServerContext* context, const ::database::Empty* request, ::database::DatabasePath* response) override {
        response->set_path(database::get_database_file_path());
        return ::grpc::Status::OK;
    }
    ::grpc::Status SetDatabasePath(::grpc::ServerContext* context, const ::database::DatabasePath* request, ::database::CallStatus* response) override {
        response->set_success(database::set_database_file_path(request->path()));
        return ::grpc::Status::OK;
    }
    ::grpc::Status CreateIfNotExists(::grpc::ServerContext* context, const ::database::Empty* request, ::database::CallStatus* response) override {
        response->set_success(database::create_database());
        return ::grpc::Status::OK;
    }
    ::grpc::Status DeleteDatabase(::grpc::ServerContext* context, const ::database::Empty* request, ::database::CallStatus* response) override {
        response->set_success(database::delete_database());
        return ::grpc::Status::OK;
    }
};

bool database_service::init_database_service(grpc::ServerBuilder &builder) {
    database_service_impl service;
    builder.RegisterService(&service);
    return true;
}
