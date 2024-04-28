//
// Created by jb030 on 28/04/2024.
//

#ifndef ATODO_SERVICE_DATABASE_H
#define ATODO_SERVICE_DATABASE_H

#include <string>

namespace database {
    bool check_database_existence();
    std::string get_database_file_path();
    void set_database_file_path(std::string file_path);
    bool create_database();
    bool delete_database();
}

#endif //ATODO_SERVICE_DATABASE_H
