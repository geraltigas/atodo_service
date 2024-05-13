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
    bool back_to_parent_task();
    bool set_now_selected_task(int64_t now_selected_task);
    int64_t get_now_selected_task();
    bool set_work_time(int64_t work_time);
    int64_t get_work_time();
    bool set_today_work_start(bool today_work_start);
    bool get_today_work_start();
    bool set_now_is_work_time(bool now_is_work_time);
    bool get_now_is_work_time();
    bool set_now_doing_task(int64_t now_doing_task);
    int64_t get_now_doing_task();
}


#endif //ATODO_SERVICE_APP_STATE_H
