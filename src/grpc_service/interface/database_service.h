//
// Created by jb030 on 02/05/2024.
//

#ifndef ATODO_SERVICE_DATABASE_SERVICE_H
#define ATODO_SERVICE_DATABASE_SERVICE_H

#include <grpcpp/grpcpp.h>

namespace database_service {
    // input builder
    bool init_database_service(grpc::ServerBuilder &builder);
};


#endif //ATODO_SERVICE_DATABASE_SERVICE_H
