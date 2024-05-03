//
// Created by jb030 on 02/05/2024.
//

#include "service.h"
#include <grpcpp/grpcpp.h>
#include <grpc_service/interface/database_service.h>
#include <glog/logging.h>

std::unique_ptr<grpc::Server> server;

bool service::init_service(const char *grpc_url) {
    grpc::ServerBuilder builder;
    builder.AddListeningPort(grpc_url, grpc::InsecureServerCredentials());
    bool rt = database_service::init_database_service(builder);

    server = builder.BuildAndStart();
    LOG(INFO) << "Server will listen on " << grpc_url;
    return rt;
}

bool service::run_service() {
    if (server) {
        server->Wait();
        return true;
    }
    LOG(ERROR) << "Server is not initialized";
    return false;
}
