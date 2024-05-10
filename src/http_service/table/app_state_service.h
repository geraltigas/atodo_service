//
// Created by jb030 on 09/05/2024.
//

#ifndef ATODO_SERVICE_APP_STATE_SERVICE_H
#define ATODO_SERVICE_APP_STATE_SERVICE_H

#include "crow.h"

namespace app_state_service {
    bool init_app_state_service(crow::SimpleApp &app);
};


#endif //ATODO_SERVICE_APP_STATE_SERVICE_H
