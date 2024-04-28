#include <gtest/gtest.h>
#include "meta/meta.h"
#include <filesystem>

TEST(meta, create_meta_database) {
    EXPECT_TRUE(meta::create_meta_database());
    if (std::filesystem::exists(meta_database_file_path)) {
        std::filesystem::remove(meta_database_file_path);
        ASSERT_TRUE(1);
    }else {
        ASSERT_TRUE(0);
    };
}

TEST(meta, meta_database_recreate) {
    EXPECT_TRUE(meta::create_meta_database());
    EXPECT_TRUE(meta::create_meta_database());
    if (std::filesystem::exists(meta_database_file_path)) {
        std::filesystem::remove(meta_database_file_path);
        ASSERT_TRUE(1);
    }else {
        ASSERT_TRUE(0);
    };
}

TEST(meta, remove_meta_database) {
    EXPECT_TRUE(meta::create_meta_database());
    EXPECT_TRUE(meta::delete_meta_database());
    if (!std::filesystem::exists(meta_database_file_path)) {
        ASSERT_TRUE(1);
    }else {
        ASSERT_TRUE(0);
    };
}

TEST(meta, get_app_database_file_path) {
    EXPECT_TRUE(meta::create_meta_database());
    EXPECT_EQ(meta::get_app_database_file_path(), "./app.db");
    if (std::filesystem::exists(meta_database_file_path)) {
        std::filesystem::remove(meta_database_file_path);
        ASSERT_TRUE(1);
    }else {
        ASSERT_TRUE(0);
    };
}

TEST(meta, set_app_database_file_path) {
    EXPECT_TRUE(meta::create_meta_database());
    EXPECT_TRUE(meta::set_app_database_file_path("./test.db"));
    EXPECT_EQ(meta::get_app_database_file_path(), "./test.db");
    if (std::filesystem::exists(meta_database_file_path)) {
        std::filesystem::remove(meta_database_file_path);
        ASSERT_TRUE(1);
    }else {
        ASSERT_TRUE(0);
    };
}