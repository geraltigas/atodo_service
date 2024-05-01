//
// Created by jb030 on 01/05/2024.
//

#include <gtest/gtest.h>
#include <interface/table/suspended_task.h>
#include <app.h>
#include <type.h>

TEST(suspended_task_test, add_suspended_task) {
    app::init(0, nullptr);
    suspended_task::clear_all_suspended_tasks();
    suspended_task::suspended_task_t suspended_task;
    suspended_task.task_id = 1;
    suspended_task.type = suspended_task_type::time;
    suspended_task.time_info = ::suspended_task::time_task_info_t(1);
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task));
    suspended_task::suspended_task_t suspended_task1 = suspended_task::get_suspended_task(1);
    ASSERT_TRUE(suspended_task1 == suspended_task);
    suspended_task::clear_all_suspended_tasks();
}

TEST(suspended_task_test, delete_suspended_task) {
    app::init(0, nullptr);
    suspended_task::clear_all_suspended_tasks();
    suspended_task::suspended_task_t suspended_task;
    suspended_task.task_id = 1;
    suspended_task.type = suspended_task_type::time;
    suspended_task.time_info = ::suspended_task::time_task_info_t(1);
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task));
    suspended_task::suspended_task_t suspended_task1 = suspended_task::get_suspended_task(1);
    ASSERT_TRUE(suspended_task1 == suspended_task);
    EXPECT_TRUE(suspended_task::delete_suspended_task(1));
    suspended_task::suspended_task_t suspended_task2 = suspended_task::get_suspended_task(1);
    EXPECT_EQ(suspended_task2.task_id, -1);
    suspended_task::clear_all_suspended_tasks();
}

TEST(suspended_task_test, get_suspended_task) {
    app::init(0, nullptr);
    suspended_task::clear_all_suspended_tasks();
    suspended_task::suspended_task_t suspended_task;
    suspended_task.task_id = 1;
    suspended_task.type = suspended_task_type::time;
    suspended_task.time_info = ::suspended_task::time_task_info_t(1);
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task));
    suspended_task::suspended_task_t suspended_task1 = suspended_task::get_suspended_task(1);
    ASSERT_TRUE(suspended_task1 == suspended_task);
    suspended_task::clear_all_suspended_tasks();
}

TEST(suspended_task_test, get_suspended_task_by_type) {
    app::init(0, nullptr);
    suspended_task::clear_all_suspended_tasks();
    suspended_task::suspended_task_t suspended_task;
    suspended_task.task_id = 1;
    suspended_task.type = suspended_task_type::time;
    suspended_task.time_info = ::suspended_task::time_task_info_t(1);
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task));
    suspended_task::suspended_task_t suspended_task1;
    suspended_task1.task_id = 2;
    suspended_task1.type = suspended_task_type::email;
    // copy assignment
    suspended_task1.email_info = ::suspended_task::email_task_info_t("email", {"content"});
    std::vector<suspended_task::suspended_task_t> suspended_tasks = suspended_task::get_suspended_task_by_type(suspended_task_type::time);
    ASSERT_EQ(suspended_tasks.size(), 1);
    ASSERT_TRUE(suspended_tasks[0] == suspended_task);
    suspended_tasks = suspended_task::get_suspended_task_by_type(suspended_task_type::email);
    ASSERT_EQ(suspended_tasks.size(), 0);
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task1));
    suspended_tasks = suspended_task::get_suspended_task_by_type(suspended_task_type::email);
    ASSERT_EQ(suspended_tasks.size(), 1);
    ASSERT_TRUE(suspended_tasks[0] == suspended_task1);
    suspended_task::clear_all_suspended_tasks();
}

TEST(suspended_task_test, get_all_suspended_tasks) {
    app::init(0, nullptr);
    suspended_task::clear_all_suspended_tasks();
    suspended_task::suspended_task_t suspended_task;
    suspended_task.task_id = 1;
    suspended_task.type = suspended_task_type::time;
    suspended_task.time_info = ::suspended_task::time_task_info_t(1);
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task));
    suspended_task::suspended_task_t suspended_task1;
    suspended_task1.task_id = 2;
    suspended_task1.type = suspended_task_type::email;
    suspended_task1.email_info = ::suspended_task::email_task_info_t("email", {"content"});
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task1));
    std::vector<suspended_task::suspended_task_t> suspended_tasks = suspended_task::get_all_suspended_tasks();
    ASSERT_EQ(suspended_tasks.size(), 2);
    ASSERT_TRUE(suspended_tasks[0] == suspended_task);
    ASSERT_TRUE(suspended_tasks[1] == suspended_task1);
    suspended_task::clear_all_suspended_tasks();
}

TEST(suspended_task_test, clear_all_suspended_tasks) {
    app::init(0, nullptr);
    suspended_task::clear_all_suspended_tasks();
    suspended_task::suspended_task_t suspended_task;
    suspended_task.task_id = 1;
    suspended_task.type = suspended_task_type::time;
    suspended_task.time_info = ::suspended_task::time_task_info_t(1);
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task));
    suspended_task::suspended_task_t suspended_task1;
    suspended_task1.task_id = 2;
    suspended_task1.type = suspended_task_type::email;
    suspended_task1.email_info = ::suspended_task::email_task_info_t("email", {"content"});
    EXPECT_TRUE(suspended_task::add_suspended_task(suspended_task1));
    std::vector<suspended_task::suspended_task_t> suspended_tasks = suspended_task::get_all_suspended_tasks();
    ASSERT_EQ(suspended_tasks.size(), 2);
    EXPECT_TRUE(suspended_task::clear_all_suspended_tasks());
    suspended_tasks = suspended_task::get_all_suspended_tasks();
    ASSERT_EQ(suspended_tasks.size(), 0);
    suspended_task::clear_all_suspended_tasks();
}
