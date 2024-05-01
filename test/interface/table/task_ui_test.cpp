//
// Created by jb030 on 01/05/2024.
//

#include <gtest/gtest.h>
#include <interface/table/task_ui.h>
#include <component/sql_prepare.h>
#include <app.h>

TEST(task_ui_test, add_or_update_task_ui) {
    app::init(0, nullptr);
    task_ui::clear_all_task_ui();
    EXPECT_TRUE(task_ui::add_or_update_task_ui(1, 0, 0, 0));
    task_ui::task_ui_t task_ui = task_ui::get_task_ui_by_id(1);
    EXPECT_EQ(task_ui.task_id, 1);
    EXPECT_EQ(task_ui.parent_task, 0);
    EXPECT_EQ(task_ui.position_x, 0);
    EXPECT_EQ(task_ui.position_y, 0);
    task_ui::clear_all_task_ui();
}

TEST(task_ui_test, get_task_ui_by_id) {
    app::init(0, nullptr);
    task_ui::clear_all_task_ui();
    EXPECT_TRUE(task_ui::add_or_update_task_ui(1, 0, 0, 0));
    task_ui::task_ui_t task_ui = task_ui::get_task_ui_by_id(1);
    EXPECT_EQ(task_ui.task_id, 1);
    EXPECT_EQ(task_ui.parent_task, 0);
    EXPECT_EQ(task_ui.position_x, 0);
    EXPECT_EQ(task_ui.position_y, 0);
    task_ui::clear_all_task_ui();
}

TEST(task_ui_test, get_task_ui_by_parent_task) {
    app::init(0, nullptr);
    task_ui::clear_all_task_ui();
    EXPECT_TRUE(task_ui::add_or_update_task_ui(1, 0, 0, 0));
    EXPECT_TRUE(task_ui::add_or_update_task_ui(2, 1, 0, 0));
    EXPECT_TRUE(task_ui::add_or_update_task_ui(3, 1, 0, 0));
    std::vector<task_ui::task_ui_t> task_ui_list = task_ui::get_task_ui_by_parent_task(1);
    EXPECT_EQ(task_ui_list.size(), 2);
    EXPECT_EQ(task_ui_list[0].task_id, 2);
    EXPECT_EQ(task_ui_list[1].task_id, 3);
    task_ui::clear_all_task_ui();
}

TEST(task_ui_test, clear_all_task_ui) {
    app::init(0, nullptr);
    task_ui::clear_all_task_ui();
    EXPECT_TRUE(task_ui::add_or_update_task_ui(1, 0, 0, 0));
    EXPECT_TRUE(task_ui::add_or_update_task_ui(2, 1, 0, 0));
    EXPECT_TRUE(task_ui::add_or_update_task_ui(3, 1, 0, 0));
    task_ui::clear_all_task_ui();
    std::vector<task_ui::task_ui_t> task_ui_list = task_ui::get_task_ui_by_parent_task(1);
    EXPECT_EQ(task_ui_list.size(), 0);
}

TEST(task_ui_test, get_task_ui_by_id_not_exist) {
    app::init(0, nullptr);
    task_ui::clear_all_task_ui();
    task_ui::task_ui_t task_ui = task_ui::get_task_ui_by_id(1);
    EXPECT_EQ(task_ui.task_id, -1);
    task_ui::clear_all_task_ui();
}

TEST(task_ui_test, get_task_ui_by_parent_task_not_exist) {
    app::init(0, nullptr);
    task_ui::clear_all_task_ui();
    std::vector<task_ui::task_ui_t> task_ui_list = task_ui::get_task_ui_by_parent_task(1);
    EXPECT_EQ(task_ui_list.size(), 0);
    task_ui::clear_all_task_ui();
}

TEST(task_ui_test, delete_task_ui) {
    app::init(0, nullptr);
    task_ui::clear_all_task_ui();
    EXPECT_TRUE(task_ui::add_or_update_task_ui(1, 0, 0, 0));
    EXPECT_TRUE(task_ui::add_or_update_task_ui(2, 1, 0, 0));
    EXPECT_TRUE(task_ui::add_or_update_task_ui(3, 1, 0, 0));
    EXPECT_TRUE(task_ui::delete_task_ui(1));
    std::vector<task_ui::task_ui_t> task_ui_list = task_ui::get_task_ui_by_parent_task(1);
    EXPECT_EQ(task_ui_list.size(), 2);
    task_ui::clear_all_task_ui();
}
