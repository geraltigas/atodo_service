//
// Created by jb030 on 28/04/2024.
//

#include "app.h"
#include <glog/logging.h>
#include <filesystem>
#include "constant.h"
#include "meta/meta.h"
#include "interface/database.h"
#include "component/sql_prepare.h"
#include "http_service/service.h"

void SignalHandle(const char *data, size_t size) {
    std::string str = std::string(data, size);
    LOG(ERROR) << str;
    if (str.find("Check failed") != std::string::npos) {
        exit(1);
    }
}

int manage_log_dir() {
    // check log dir use stdlib
    if (!std::filesystem::exists(LOG_DIR)) {
        std::filesystem::create_directory(LOG_DIR);
    }
    // check log files, if there are more than 10 files, delete the old files
    std::filesystem::directory_iterator end_iter;
    int count = 0;
    for (std::filesystem::directory_iterator iter(LOG_DIR); iter != end_iter; iter++) {
        if (std::filesystem::is_regular_file(iter->status())) {
            count++;
        }
    }
    if (count > LOG_FILE_MAX_NUM) {
        for (std::filesystem::directory_iterator iter(LOG_DIR); iter != end_iter; iter++) {
            if (std::filesystem::is_regular_file(iter->status())) {
                std::filesystem::remove(iter->path());
                count--;
                if (count <= LOG_FILE_MAX_NUM) {
                    break;
                }
            }
        }
    }
    return 0;
}

bool app::_init::glog(int argc, char *argv[]) {
    // check whether glog is initialized
    if (google::IsGoogleLoggingInitialized()) {
        return true;
    }
    FLAGS_log_dir = LOG_DIR;
    manage_log_dir();
    if (argc == 0) {
        google::InitGoogleLogging("app");
    } else {
        google::InitGoogleLogging(argv[0]);
    }
    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(&SignalHandle);
    // set log level
    FLAGS_stderrthreshold = google::GLOG_INFO;
    return true;
}

bool app::_init::meta_database() {
    if(meta::create_if_not_exist()) {
        LOG(INFO) << "Meta database created";
        return true;
    } else {
        LOG(ERROR) << "Meta database creation failed";
        throw std::runtime_error("Meta database creation failed");
    }
}

bool app::_init::app_database() {
    database::create_if_not_exist();
    sql_prepare::set_db(database::get_sqlite_db());
    sql_prepare::sql_finalize();
    if (sql_prepare::sql_precompile()) {
        LOG(INFO) << "App database initialized";
        sqlite3_close(database::get_sqlite_db());
        return true;
    } else {
        LOG(ERROR) << "App database initialization failed";
        throw std::runtime_error("App database initialization failed");
    }
}

void app::init(int argc, char *argv[]) {
    _init::glog(argc, argv);
    _init::meta_database();
    _init::app_database();
    LOG(INFO) << "App initialized";
}

void app::run() {
    service::init_service();
    service::run_service(API_PORT);
}
