//
// Created by jb030 on 01/05/2024.
//

#include "gtest/gtest.h"
#include "interface/table/task.h"
#include "app.h"
#include "glog/logging.h"
#include "interface/table/task_trigger.h"
#include "interface/table/task_after_effect.h"
#include "interface/table/suspended_task.h"

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

TEST(task_test, get_set_default_task) {
    app::init(0, nullptr);
    task::clear_all_tasks();
    task_trigger::clear_task_triggers();
    task_after_effect::clear_all_after_effects();
    suspended_task::clear_all_suspended_tasks();
    int64_t id = task::add_task_default("taskt", "taskt", 1, true);
    task::task_detail_t task_detail = task::get_detailed_task(id);
    EXPECT_EQ(task_detail.task_id, id);
    EXPECT_EQ(task_detail.name, "taskt");
    EXPECT_EQ(task_detail.goal, "taskt");
    EXPECT_EQ(task_detail.deadline, "1");
    EXPECT_EQ(task_detail.in_work_time, true);
    EXPECT_EQ(task_detail.status, "todo");
    EXPECT_EQ(task_detail.trigger_type.size(), 0);
    EXPECT_EQ(task_detail.after_effect_type.size(), 0);
    EXPECT_EQ(task_detail.suspended_task_type.size(), 0);
    EXPECT_EQ(task_detail.resume_time, "");
    EXPECT_EQ(task_detail.email, "");
    EXPECT_EQ(task_detail.keywords.size(), 0);
    EXPECT_EQ(task_detail.event_name, "");
    EXPECT_EQ(task_detail.event_description, "");
    EXPECT_EQ(task_detail.intervals.size(), 0);
    task::task_detail_t task_detail1;
    task_detail1.task_id = id;
    task_detail1.name = "taskt1";
    task_detail1.goal = "taskt1";
    task_detail1.deadline = "2";
    task_detail1.in_work_time = false;
    task_detail1.status = "suspended";
    task_detail1.trigger_type = {"event"};
    task_detail1.after_effect_type = {"periodic"};
    task_detail1.suspended_task_type = {"time"};
    task_detail1.resume_time = "3";
    task_detail1.event_name = "event";
    task_detail1.event_description = "event";
    task_detail1.now_at = 1;
    task_detail1.period = 1;
    task_detail1.intervals = {1};
    EXPECT_TRUE(task::set_detailed_task(task_detail1));
    task::task_detail_t task_detail2 = task::get_detailed_task(id);
    EXPECT_TRUE(task_detail1 == task_detail2);
    task_detail1.name = "taskt2";
    task::set_detailed_task(task_detail1);
    task::task_detail_t task_detail3 = task::get_detailed_task(id);
    EXPECT_TRUE(task_detail1 == task_detail3);
    task_detail1.goal = "taskt3";
    task::set_detailed_task(task_detail1);
    task::task_detail_t task_detail4 = task::get_detailed_task(id);
    EXPECT_TRUE(task_detail1 == task_detail4);
    task_detail1.deadline = "4";
    task::set_detailed_task(task_detail1);
    task::task_detail_t task_detail5 = task::get_detailed_task(id);
    EXPECT_TRUE(task_detail1 == task_detail5);
    task_detail1.in_work_time = true;
    task::set_detailed_task(task_detail1);
    task::task_detail_t task_detail6 = task::get_detailed_task(id);
    EXPECT_TRUE(task_detail1 == task_detail6);
    task_detail1.status = "todo";
    task::set_detailed_task(task_detail1);
    task::task_detail_t task_detail7 = task::get_detailed_task(id);
    task_detail1.suspended_task_type.clear();
    task_detail1.resume_time = "";
    EXPECT_TRUE(task_detail1 == task_detail7);
    task_detail1.trigger_type.clear();
    task::set_detailed_task(task_detail1);
    task::task_detail_t task_detail8 = task::get_detailed_task(id);
    task_detail1.event_name = "";
    task_detail1.event_description = "";
    EXPECT_TRUE(task_detail1 == task_detail8);
    task_detail1.after_effect_type.clear();
    task::set_detailed_task(task_detail1);
    task::task_detail_t task_detail9 = task::get_detailed_task(id);
    task_detail1.now_at = -1;
    task_detail1.period = -1;
    task_detail1.intervals.clear();
    EXPECT_TRUE(task_detail1 == task_detail9);
    task::clear_all_tasks();
    task_trigger::clear_task_triggers();
    task_after_effect::clear_all_after_effects();
    suspended_task::clear_all_suspended_tasks();
}


