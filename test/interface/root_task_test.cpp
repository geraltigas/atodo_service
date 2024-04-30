//
// Created by jb030 on 30/04/2024.
//

#include <gtest/gtest.h>
#include <interface/root_task.h>
#include <app.h>

TEST(root_task_test, get_all_root_tasks) {
    app::init(0, nullptr);
    root_task::clear_all_root_tasks();
    std::vector<int64_t> root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 0);
    root_task::insert_root_task(1);
    root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 1);
    EXPECT_EQ(root_tasks[0], 1);
    root_task::insert_root_task(2);
    root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 2);
    EXPECT_EQ(root_tasks[0], 1);
    EXPECT_EQ(root_tasks[1], 2);
    root_task::delete_root_task(1);
    root_task::delete_root_task(2);
    root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 0);
}

TEST(root_task_test, insert_root_task) {
    app::init(0, nullptr);
    root_task::clear_all_root_tasks();
    root_task::insert_root_task(1);
    std::vector<int64_t> root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 1);
    EXPECT_EQ(root_tasks[0], 1);
    root_task::insert_root_task(2);
    root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 2);
    EXPECT_EQ(root_tasks[0], 1);
    EXPECT_EQ(root_tasks[1], 2);
    root_task::delete_root_task(1);
    root_task::delete_root_task(2);
    root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 0);
}

TEST(root_task_test, delete_root_task) {
    app::init(0, nullptr);
    root_task::clear_all_root_tasks();
    root_task::insert_root_task(1);
    root_task::insert_root_task(2);
    std::vector<int64_t> root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 2);
    EXPECT_EQ(root_tasks[0], 1);
    EXPECT_EQ(root_tasks[1], 2);
    root_task::delete_root_task(1);
    root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 1);
    EXPECT_EQ(root_tasks[0], 2);
    root_task::delete_root_task(2);
    root_tasks = root_task::get_all_root_tasks();
    EXPECT_EQ(root_tasks.size(), 0);
}