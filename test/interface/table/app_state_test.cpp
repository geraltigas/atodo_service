//
// Created by jb030 on 30/04/2024.
//

#include "gtest/gtest.h"
#include "interface/table/app_state.h"
#include "app.h"
#include "meta/meta.h"
#include "interface/database.h"

TEST(app_state_test, set_root_task) {
    app::init(0, nullptr);
    app_state::set_root_task(1);
    ASSERT_EQ(app_state::get_root_task(), 1);
}

TEST(app_state_test, set_now_viewing_task) {
    app::init(0, nullptr);
    app_state::set_now_viewing_task(2);
    ASSERT_EQ(app_state::get_now_viewing_task(), 2);
}

TEST(app_state_test, set_now_selected_task) {
    app::init(0, nullptr);
    app_state::set_now_selected_task(3);
    ASSERT_EQ(app_state::get_now_selected_task(), 3);
}
