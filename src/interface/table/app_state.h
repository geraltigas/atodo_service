//
// Created by jb030 on 29/04/2024.
//

#ifndef ATODO_SERVICE_APP_STATE_H
#define ATODO_SERVICE_APP_STATE_H

#include <cstdint>

namespace app_state {
    bool set_root_task(int64_t root_task);
    int64_t get_root_task();
    bool set_now_viewing_task(int64_t now_viewing_task);
    int64_t get_now_viewing_task();
    bool set_now_selected_task(int64_t now_selected_task);
    int64_t get_now_selected_task();
}


#endif //ATODO_SERVICE_APP_STATE_H
