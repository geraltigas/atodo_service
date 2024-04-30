//
// Created by jb030 on 30/04/2024.
//

#include "gtest/gtest.h"
#include "meta/meta.h"

TEST(meta_database_test, manage_meta_database) {
    EXPECT_TRUE(meta::delete_meta_database());
    EXPECT_FALSE(meta::check_meta_database_existence());
    EXPECT_TRUE(meta::create_meta_database());
    EXPECT_TRUE(meta::check_meta_database_existence());
}

TEST(meta_database_test, get_app_database_file_path) {
    EXPECT_TRUE(meta::delete_meta_database());
    EXPECT_TRUE(meta::create_meta_database());
    EXPECT_EQ(meta::get_app_database_file_path(), "./app.db");
}

TEST(meta_database_test, set_app_database_file_path) {
    EXPECT_TRUE(meta::delete_meta_database());
    EXPECT_TRUE(meta::create_meta_database());
    EXPECT_TRUE(meta::set_app_database_file_path("./test.db"));
    EXPECT_EQ(meta::get_app_database_file_path(), "./test.db");
}
