//
// Created by jb030 on 28/04/2024.
//

#ifndef ATODO_SERVICE_APP_H
#define ATODO_SERVICE_APP_H

namespace app {
    namespace _init {
        bool glog(int argc, char* argv[]);
        bool meta_database();
        bool app_database();
    }
    void init(int argc, char* argv[]);
    void run();
    void exit();
}

#endif //ATODO_SERVICE_APP_H
