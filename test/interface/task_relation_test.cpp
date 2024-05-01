//
// Created by jb030 on 01/05/2024.
//

#include <gtest/gtest.h>
#include <interface/task_relation.h>
#include <app.h>

TEST(task_relation_test, add_realtion) {
    app::init(0, nullptr);
    EXPECT_TRUE(task_relation::add_relation(1, 2));
    EXPECT_TRUE(task_relation::add_relation(1, 3));
    EXPECT_TRUE(task_relation::add_relation(1, 4));
    EXPECT_TRUE(task_relation::add_relation(2, 3));
    EXPECT_TRUE(task_relation::add_relation(2, 4));
    EXPECT_TRUE(task_relation::add_relation(3, 4));

    std::vector<int64_t> target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 3);
    EXPECT_EQ(target_tasks[0], 2);
    EXPECT_EQ(target_tasks[1], 3);
    EXPECT_EQ(target_tasks[2], 4);

    std::vector<int64_t> source_tasks = task_relation::get_source_tasks(4);
    EXPECT_EQ(source_tasks.size(), 3);
    EXPECT_EQ(source_tasks[0], 1);
    EXPECT_EQ(source_tasks[1], 2);
    EXPECT_EQ(source_tasks[2], 3);

    EXPECT_TRUE(task_relation::delete_relation(1, 2));
    target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 2);
    EXPECT_EQ(target_tasks[0], 3);
    EXPECT_EQ(target_tasks[1], 4);

    EXPECT_TRUE(task_relation::remove_all_related_relations(1));
    target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 0);

    EXPECT_TRUE(task_relation::clear_all_relations());
    target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 0);
    source_tasks = task_relation::get_source_tasks(4);
    EXPECT_EQ(source_tasks.size(), 0);

    task_relation::clear_all_relations();
}

TEST(task_relation_test, delete_relation) {
    app::init(0, nullptr);
    EXPECT_TRUE(task_relation::add_relation(1, 2));
    EXPECT_TRUE(task_relation::add_relation(1, 3));
    EXPECT_TRUE(task_relation::add_relation(1, 4));
    EXPECT_TRUE(task_relation::add_relation(2, 3));
    EXPECT_TRUE(task_relation::add_relation(2, 4));
    EXPECT_TRUE(task_relation::add_relation(3, 4));

    std::vector<int64_t> target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 3);
    EXPECT_EQ(target_tasks[0], 2);
    EXPECT_EQ(target_tasks[1], 3);
    EXPECT_EQ(target_tasks[2], 4);

    EXPECT_TRUE(task_relation::delete_relation(1, 2));

    target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 2);
    EXPECT_EQ(target_tasks[0], 3);
    EXPECT_EQ(target_tasks[1], 4);

    task_relation::clear_all_relations();
}

TEST(task_relation_test, remove_all_related_relations) {
    app::init(0, nullptr);
    EXPECT_TRUE(task_relation::add_relation(1, 2));
    EXPECT_TRUE(task_relation::add_relation(1, 3));
    EXPECT_TRUE(task_relation::add_relation(1, 4));
    EXPECT_TRUE(task_relation::add_relation(2, 3));
    EXPECT_TRUE(task_relation::add_relation(2, 4));
    EXPECT_TRUE(task_relation::add_relation(3, 4));

    std::vector<int64_t> target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 3);
    EXPECT_EQ(target_tasks[0], 2);
    EXPECT_EQ(target_tasks[1], 3);
    EXPECT_EQ(target_tasks[2], 4);

    EXPECT_TRUE(task_relation::remove_all_related_relations(1));

    target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 0);

    task_relation::clear_all_relations();
}

TEST(task_relation_test, clear_all_relations) {
    app::init(0, nullptr);
    EXPECT_TRUE(task_relation::add_relation(1, 2));
    EXPECT_TRUE(task_relation::add_relation(1, 3));
    EXPECT_TRUE(task_relation::add_relation(1, 4));
    EXPECT_TRUE(task_relation::add_relation(2, 3));
    EXPECT_TRUE(task_relation::add_relation(2, 4));
    EXPECT_TRUE(task_relation::add_relation(3, 4));

    std::vector<int64_t> target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 3);
    EXPECT_EQ(target_tasks[0], 2);
    EXPECT_EQ(target_tasks[1], 3);
    EXPECT_EQ(target_tasks[2], 4);

    EXPECT_TRUE(task_relation::clear_all_relations());

    target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 0);

    task_relation::clear_all_relations();
}

TEST(task_relation_test, get_target_tasks) {
    app::init(0, nullptr);
    EXPECT_TRUE(task_relation::add_relation(1, 2));
    EXPECT_TRUE(task_relation::add_relation(1, 3));
    EXPECT_TRUE(task_relation::add_relation(1, 4));
    EXPECT_TRUE(task_relation::add_relation(2, 3));
    EXPECT_TRUE(task_relation::add_relation(2, 4));
    EXPECT_TRUE(task_relation::add_relation(3, 4));

    std::vector<int64_t> target_tasks = task_relation::get_target_tasks(1);
    EXPECT_EQ(target_tasks.size(), 3);
    EXPECT_EQ(target_tasks[0], 2);
    EXPECT_EQ(target_tasks[1], 3);
    EXPECT_EQ(target_tasks[2], 4);

    task_relation::clear_all_relations();
}

TEST(task_relation_test, get_source_tasks) {
    app::init(0, nullptr);
    EXPECT_TRUE(task_relation::add_relation(1, 2));
    EXPECT_TRUE(task_relation::add_relation(1, 3));
    EXPECT_TRUE(task_relation::add_relation(1, 4));
    EXPECT_TRUE(task_relation::add_relation(2, 3));
    EXPECT_TRUE(task_relation::add_relation(2, 4));
    EXPECT_TRUE(task_relation::add_relation(3, 4));

    std::vector<int64_t> source_tasks = task_relation::get_source_tasks(4);
    EXPECT_EQ(source_tasks.size(), 3);
    EXPECT_EQ(source_tasks[0], 1);
    EXPECT_EQ(source_tasks[1], 2);
    EXPECT_EQ(source_tasks[2], 3);

    task_relation::clear_all_relations();
}
