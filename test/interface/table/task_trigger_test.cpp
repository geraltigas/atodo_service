//
// Created by jb030 on 02/05/2024.
//

#include <gtest/gtest.h>
#include <interface/table/task_trigger.h>
#include <app.h>

TEST(task_trigger_test, add_or_update_task_trigger) {
    app::init(0, nullptr);
    task_trigger::clear_task_triggers();
    task_trigger::task_trigger_t task_trigger2;
    task_trigger2.task_id = 1;
    task_trigger2.type = task_trigger_type::event;
    task_trigger2.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger2));
    std::vector<task_trigger::task_trigger_t> task_triggers = task_trigger::get_all_task_triggers();
    EXPECT_EQ(task_triggers.size(), 1);
    task_trigger::clear_task_triggers();
}

TEST(task_trigger_test, delete_task_trigger) {
    app::init(0, nullptr);
    task_trigger::clear_task_triggers();
    task_trigger::task_trigger_t task_trigger;
    task_trigger.task_id = 1;
    task_trigger.type = task_trigger_type::event;
    task_trigger.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger));
    EXPECT_TRUE(task_trigger::delete_task_trigger(1, task_trigger_type::event));
    std::vector<task_trigger::task_trigger_t> task_triggers = task_trigger::get_all_task_triggers();
    EXPECT_EQ(task_triggers.size(), 0);
    task_trigger::clear_task_triggers();
}

TEST(task_trigger_test, delete_task_triggers_by_id) {
    app::init(0, nullptr);
    task_trigger::clear_task_triggers();
    task_trigger::task_trigger_t task_trigger;
    task_trigger.task_id = 1;
    task_trigger.type = task_trigger_type::event;
    task_trigger.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger));
    task_trigger::task_trigger_t task_trigger2;
    task_trigger2.task_id = 2;
    task_trigger2.type = task_trigger_type::event;
    task_trigger2.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger2));
    EXPECT_TRUE(task_trigger::delete_task_triggers_by_id(1));
    std::vector<task_trigger::task_trigger_t> task_triggers = task_trigger::get_all_task_triggers();
    EXPECT_EQ(task_triggers.size(), 1);
    task_trigger::clear_task_triggers();
}

TEST(task_trigger_test, get_task_trigger) {
    app::init(0, nullptr);
    task_trigger::clear_task_triggers();
    task_trigger::task_trigger_t task_trigger;
    task_trigger.task_id = 1;
    task_trigger.type = task_trigger_type::event;
    task_trigger.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger));
    task_trigger::task_trigger_t task_trigger2;
    task_trigger2.task_id = 2;
    task_trigger2.type = task_trigger_type::event;
    task_trigger2.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger2));
//    task_trigger::task_trigger_t task_trigger3 = task_trigger::get_task_trigger(1, task_trigger_type::dependency);
//    EXPECT_EQ(task_trigger3.task_id, 1);
//    EXPECT_EQ(task_trigger3.type, task_trigger_type::dependency);
//    EXPECT_EQ(task_trigger3.dependency.task_id, 2);
    task_trigger::clear_task_triggers();
}

TEST(task_trigger_test, get_task_triggers_by_id) {
    app::init(0, nullptr);
    task_trigger::clear_task_triggers();
    task_trigger::task_trigger_t task_trigger2;
    task_trigger2.task_id = 1;
    task_trigger2.type = task_trigger_type::event;
    task_trigger2.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger2));
    task_trigger::task_trigger_t task_trigger3;
    task_trigger3.task_id = 2;
    task_trigger3.type = task_trigger_type::event;
    task_trigger3.event = task_trigger::event_t("event_name", "event_description");
    std::vector<task_trigger::task_trigger_t> task_triggers = task_trigger::get_task_triggers_by_id(1);
    EXPECT_EQ(task_triggers.size(), 1);
    task_trigger::clear_task_triggers();
}

TEST(task_trigger_test, get_task_triggers_by_type) {
    app::init(0, nullptr);
    task_trigger::clear_task_triggers();
    task_trigger::task_trigger_t task_trigger;
    task_trigger.task_id = 1;
    task_trigger.type = task_trigger_type::event;
    task_trigger.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger));
    task_trigger::task_trigger_t task_trigger2;
    task_trigger2.task_id = 2;
    task_trigger2.type = task_trigger_type::event;
    task_trigger2.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger2));
    std::vector<task_trigger::task_trigger_t> task_triggers = task_trigger::get_task_triggers_by_type(task_trigger_type::event);
    EXPECT_EQ(task_triggers.size(), 2);
    task_trigger::clear_task_triggers();
}

TEST(task_trigger_test, get_all_task_triggers) {
    app::init(0, nullptr);
    task_trigger::clear_task_triggers();
    task_trigger::task_trigger_t task_trigger;
    task_trigger.task_id = 1;
    task_trigger.type = task_trigger_type::event;
    task_trigger.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger));
    task_trigger::task_trigger_t task_trigger2;
    task_trigger2.task_id = 2;
    task_trigger2.type = task_trigger_type::event;
    task_trigger2.event = task_trigger::event_t("event_name", "event_description");
    EXPECT_TRUE(task_trigger::add_or_update_task_trigger(task_trigger2));
    std::vector<task_trigger::task_trigger_t> task_triggers = task_trigger::get_all_task_triggers();
    EXPECT_EQ(task_triggers.size(), 2);
    task_trigger::clear_task_triggers();
}
