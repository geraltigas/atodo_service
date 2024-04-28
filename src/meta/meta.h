//
// Created by jb030 on 28/04/2024.
//

#ifndef ATODO_SERVICE_META_H
#define ATODO_SERVICE_META_H

#include <string>

extern const std::string meta_database_file_path;

namespace meta {
    bool create_meta_database();
    bool delete_meta_database();
    std::string get_app_database_file_path();
    bool set_app_database_file_path(std::string file_path);
}

#endif //ATODO_SERVICE_META_H
