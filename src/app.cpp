//
// Created by jb030 on 28/04/2024.
//

#include "app.h"
#include <glog/logging.h>
#include <filesystem>
#include "constant.h"
#include "meta/meta.h"

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

int init_glog(int argc, char *argv[]) {
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
    return 0;
}

bool init_meta_database() {
    if(meta::create_meta_database()) {
        LOG(INFO) << "Meta database created";
        return true;
    } else {
        LOG(ERROR) << "Meta database creation failed";
        throw std::runtime_error("Meta database creation failed");
    }
}

void app::init(int argc, char *argv[]) {
    init_glog(argc, argv);
    init_meta_database();
    LOG(INFO) << "App initialized";
}
