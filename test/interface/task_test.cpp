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

TEST(task_test, update_task_name) {
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
    task.name = "task2";
    EXPECT_TRUE(task::update_task_name(task_id, "task2"));
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    task::clear_all_tasks();
}

TEST(task_test, update_task_goal) {
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
    task.goal = "goal2";
    EXPECT_TRUE(task::update_task_goal(task_id, "goal2"));
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    task::clear_all_tasks();
}

TEST(task_test, update_task_deadline) {
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
    task.deadline = 2;
    EXPECT_TRUE(task::update_task_deadline(task_id, 2));
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    task::clear_all_tasks();
}

TEST(task_test, update_task_in_work_time) {
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
    task.in_work_time = false;
    EXPECT_TRUE(task::update_task_in_work_time(task_id, false));
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    task::clear_all_tasks();
}

TEST(task_test, update_task_status) {
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
    task.status = task_status::done;
    EXPECT_TRUE(task::update_task_status(task_id, task_status::done));
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    task::clear_all_tasks();
}

TEST(task_test, update_task_parent_task) {
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
    task.parent_task = 1;
    EXPECT_TRUE(task::update_task_parent_task(task_id, 1));
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    task::clear_all_tasks();
}

TEST(task_test, clear_all_tasks) {
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
    task::task_t task1 = task::get_task_by_id(task_id);
    ASSERT_TRUE(task1 == task);
    EXPECT_TRUE(task::clear_all_tasks());
    task::task_t task2 = task::get_task_by_id(task_id);
    EXPECT_EQ(task2.task_id, -1);
    task::clear_all_tasks();
}
