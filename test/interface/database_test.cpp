//
// Created by jb030 on 30/04/2024.
//
#include <gtest/gtest.h>
#include <meta/meta.h>
#include <interface/database.h>

TEST(app_database_test, manage_app_database) {
    EXPECT_TRUE(meta::delete_meta_database());
    EXPECT_TRUE(meta::create_meta_database());
    EXPECT_TRUE(database::create_database());
    EXPECT_TRUE(database::check_database_existence());
    EXPECT_TRUE(database::create_database());
    EXPECT_TRUE(database::check_database_existence());
}