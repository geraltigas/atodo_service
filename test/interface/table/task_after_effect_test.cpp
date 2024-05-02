//
// Created by jb030 on 02/05/2024.
//

#include <gtest/gtest.h>
#include <app.h>
#include <interface/table/task_after_effect.h>

TEST(task_after_effect_test, add_or_update_after_effect) {
    app::init(0, nullptr);
    task_after_effect::clear_all_after_effects();
    task_after_effect::after_effect_t after_effect;
    after_effect.id = 1;
    after_effect.type = task_after_effect_type::periodic;
    after_effect.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect));
    task_after_effect::after_effect_t after_effect1;
    after_effect1.id = 2;
    after_effect1.type = task_after_effect_type::periodic;
    after_effect1.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect1));
    std::vector<task_after_effect::after_effect_t> after_effects = task_after_effect::get_all_after_effects();
    EXPECT_EQ(after_effects.size(), 2);
    EXPECT_TRUE(after_effects[0] == after_effect);
    EXPECT_TRUE(after_effects[1] == after_effect1);
    task_after_effect::clear_all_after_effects();
}

TEST(task_after_effect_test, get_after_effect) {
    app::init(0, nullptr);
    task_after_effect::clear_all_after_effects();
    task_after_effect::after_effect_t after_effect;
    after_effect.id = 1;
    after_effect.type = task_after_effect_type::periodic;
    after_effect.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect));
    task_after_effect::after_effect_t after_effect1;
    after_effect1.id = 2;
    after_effect1.type = task_after_effect_type::periodic;
    after_effect1.periodic = task_after_effect::periodic_t(0, {1, 2, 3});

    auto after_effect2 = task_after_effect::get_after_effect(1, task_after_effect_type::periodic);
    EXPECT_TRUE(after_effect2 == after_effect);
    task_after_effect::clear_all_after_effects();
}

TEST(task_after_effect_test, get_after_effects_by_id) {
        app::init(0, nullptr);
    task_after_effect::clear_all_after_effects();
    task_after_effect::after_effect_t after_effect;
    after_effect.id = 1;
    after_effect.type = task_after_effect_type::periodic;
    after_effect.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect));
    task_after_effect::after_effect_t after_effect1;
    after_effect1.id = 2;
    after_effect1.type = task_after_effect_type::periodic;
    after_effect1.periodic = task_after_effect::periodic_t(0, {1, 2, 3});

    auto after_effect2 = task_after_effect::get_after_effects_by_id(1);
    EXPECT_EQ(after_effect2.size(), 1);
    EXPECT_TRUE(after_effect2[0] == after_effect);
    task_after_effect::clear_all_after_effects();
}

TEST(task_after_effect_test, delete_after_effect) {
    app::init(0, nullptr);
    task_after_effect::clear_all_after_effects();
    task_after_effect::after_effect_t after_effect;
    after_effect.id = 1;
    after_effect.type = task_after_effect_type::periodic;
    after_effect.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect));
    task_after_effect::after_effect_t after_effect1;
    after_effect1.id = 2;
    after_effect1.type = task_after_effect_type::periodic;
    after_effect1.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect1));
    EXPECT_TRUE(task_after_effect::delete_after_effect(1, task_after_effect_type::periodic));
    std::vector<task_after_effect::after_effect_t> after_effects = task_after_effect::get_all_after_effects();
    EXPECT_EQ(after_effects.size(), 1);
    EXPECT_TRUE(after_effects[0] == after_effect1);
    task_after_effect::clear_all_after_effects();
}

TEST(task_after_effect_test, delete_after_effect_by_id) {
    app::init(0, nullptr);
    task_after_effect::clear_all_after_effects();
    task_after_effect::after_effect_t after_effect;
    after_effect.id = 1;
    after_effect.type = task_after_effect_type::periodic;
    after_effect.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect));
    task_after_effect::after_effect_t after_effect1;
    after_effect1.id = 2;
    after_effect1.type = task_after_effect_type::periodic;
    after_effect1.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect1));
    EXPECT_TRUE(task_after_effect::delete_after_effect_by_id(1));
    std::vector<task_after_effect::after_effect_t> after_effects = task_after_effect::get_all_after_effects();
    EXPECT_EQ(after_effects.size(), 1);
    EXPECT_TRUE(after_effects[0] == after_effect1);
    task_after_effect::clear_all_after_effects();
}

TEST(task_after_effect_test, get_after_effects_by_type) {
    app::init(0, nullptr);
    task_after_effect::clear_all_after_effects();
    task_after_effect::after_effect_t after_effect;
    after_effect.id = 1;
    after_effect.type = task_after_effect_type::periodic;
    after_effect.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect));
    task_after_effect::after_effect_t after_effect1;
    after_effect1.id = 2;
    after_effect1.type = task_after_effect_type::periodic;
    after_effect1.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect1));
    auto after_effects = task_after_effect::get_after_effects_by_type(task_after_effect_type::periodic);
    EXPECT_EQ(after_effects.size(), 2);
    EXPECT_TRUE(after_effects[0] == after_effect);
    EXPECT_TRUE(after_effects[1] == after_effect1);
    task_after_effect::clear_all_after_effects();
}

TEST(task_after_effect_test, clear_all_after_effects) {
    app::init(0, nullptr);
    task_after_effect::clear_all_after_effects();
    task_after_effect::after_effect_t after_effect;
    after_effect.id = 1;
    after_effect.type = task_after_effect_type::periodic;
    after_effect.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect));
    task_after_effect::after_effect_t after_effect1;
    after_effect1.id = 2;
    after_effect1.type = task_after_effect_type::periodic;
    after_effect1.periodic = task_after_effect::periodic_t(0, {1, 2, 3});
    EXPECT_TRUE(task_after_effect::add_or_update_after_effect(after_effect1));
    EXPECT_TRUE(task_after_effect::clear_all_after_effects());
    std::vector<task_after_effect::after_effect_t> after_effects = task_after_effect::get_all_after_effects();
    EXPECT_EQ(after_effects.size(), 0);
    task_after_effect::clear_all_after_effects();
}
