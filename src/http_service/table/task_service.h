//
// Created by jb030 on 06/05/2024.
//

#ifndef ATODO_SERVICE_TASK_SERVICE_H
#define ATODO_SERVICE_TASK_SERVICE_H

#include <crow.h>

namespace task_service {
    bool init_task_service(crow::SimpleApp &app);
};


#endif //ATODO_SERVICE_TASK_SERVICE_H
