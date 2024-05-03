//
// Created by jb030 on 03/05/2024.
//

#ifndef ATODO_SERVICE_DATABASE_SERVICE_H
#define ATODO_SERVICE_DATABASE_SERVICE_H

#include <crow.h>

namespace database_service {
    bool init_database_service(crow::SimpleApp &app);
};


#endif //ATODO_SERVICE_DATABASE_SERVICE_H
