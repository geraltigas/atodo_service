//
// Created by jb030 on 01/05/2024.
//

#include <gtest/gtest.h>
#include <interface/task.h>
#include <app.h>
#include <glog/logging.h>

TEST(task_test, add_task) {
    app::init(0, nullptr);
    task::clear_all_tasks();
    task::task_t task;
    task.root_task = 1;
    task.name = "task1";
    task.goal = "goal1";
    task.deadline = 1;
    task.in_work_time = true;
    task.status = task_status::todo;
    task.parent_task = 0;
    int64_t task_id = task::add_task(task);
    EXPECT_NE(task_id, -1);
    task.task_id = task_id;
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    task::clear_all_tasks();
}

TEST(task_test, delete_task) {
    app::init(0, nullptr);
    task::clear_all_tasks();
    task::task_t task;
    task.root_task = 1;
    task.name = "task1";
    task.goal = "goal1";
    task.deadline = 1;
    task.in_work_time = true;
    task.status = task_status::todo;
    task.parent_task = 0;
    int64_t task_id = task::add_task(task);
    EXPECT_NE(task_id, -1);
    task.task_id = task_id;
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    EXPECT_TRUE(task::delete_task(task_id));
    task::task_t task2 = task::get_task_by_id(task_id);
    EXPECT_EQ(task2.task_id, -1);
    task::clear_all_tasks();
}

TEST(task_test, get_zero_id_task) {
    app::init(0, nullptr);
    task::clear_all_tasks();
    task::task_t task = task::get_task_by_id(0);
    EXPECT_EQ(task.task_id, 0);
    LOG(INFO) << "\n" << task.to_string();
    task::clear_all_tasks();
}

TEST(task_test, get_task_not_exist) {
    app::init(0, nullptr);
    task::clear_all_tasks();
    task::task_t task = task::get_task_by_id(-1);
    EXPECT_EQ(task.task_id, -1);
    LOG(INFO) << "\n" << task.to_string();
    task::clear_all_tasks();
}

TEST(task_test, get_all_tasks) {
    app::init(0, nullptr);
    task::clear_all_tasks();
    task::task_t task;
    task.root_task = 1;
    task.name = "task1";
    task.goal = "goal1";
    task.deadline = 1;
    task.in_work_time = true;
    task.status = task_status::todo;
    task.parent_task = 0;
    int64_t task_id = task::add_task(task);
    EXPECT_NE(task_id, -1);
    task.task_id = task_id;
    std::vector<task::task_t> tasks = task::get_all_tasks();
    ASSERT_EQ(tasks.size(), 2);
    ASSERT_TRUE(tasks[1] == task);
    task::clear_all_tasks();
}

TEST(task_test, get_tasks_by_root_task) {
    app::init(0, nullptr);
    task::clear_all_tasks();
    task::task_t task;
    task.root_task = 0;
    task.name = "task1";
    task.goal = "goal1";
    task.deadline = 1;
    task.in_work_time = true;
    task.status = task_status::todo;
    task.parent_task = 0;
    int64_t task_id = task::add_task(task);
    EXPECT_NE(task_id, -1);
    task.task_id = task_id;
    std::vector<task::task_t> tasks = task::get_tasks_by_root_task(0);
    ASSERT_EQ(tasks.size(), 1);
    ASSERT_TRUE(tasks[0] == task);
    task::clear_all_tasks();
}

TEST(task_test, get_tasks_by_parent_task) {
    app::init(0, nullptr);
    task::clear_all_tasks();
    task::task_t task;
    task.root_task = 0;
    task.name = "task1";
    task.goal = "goal1";
    task.deadline = 1;
    task.in_work_time = true;
    task.status = task_status::todo;
    task.parent_task = 0;
    int64_t task_id = task::add_task(task);
    EXPECT_NE(task_id, -1);
    task.task_id = task_id;
    std::vector<task::task_t> tasks = task::get_tasks_by_parent_task(0);
    ASSERT_EQ(tasks.size(), 1);
    ASSERT_TRUE(tasks[0] == task);
    task::clear_all_tasks();
}
