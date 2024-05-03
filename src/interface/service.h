//
// Created by jb030 on 03/05/2024.
//

#ifndef ATODO_SERVICE_SERVICE_H
#define ATODO_SERVICE_SERVICE_H

namespace service {
    namespace _init {
        bool glog(int argc, char* argv[]);
        bool meta_database();
        bool app_database();
    }
    void init(int argc, char* argv[]);
};


#endif //ATODO_SERVICE_SERVICE_H
