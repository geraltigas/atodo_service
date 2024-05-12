//
// Created by jb030 on 13/05/2024.
//

#ifndef ATODO_SERVICE_SCHEDULER_SERVICE_H
#define ATODO_SERVICE_SCHEDULER_SERVICE_H

#include <crow.h>

namespace scheduler_service {
    bool init_scheduler_service(crow::SimpleApp &app);
}

#endif //ATODO_SERVICE_SCHEDULER_SERVICE_H
