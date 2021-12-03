//
// Created by ggssh on 2021/11/29.
//

#include "config.h"

void parse_arg(int argc, char **argv) {
    if (argc == 0) {
        std::cerr << "There is no argv !" << std::endl;
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i] == std::string("-h")) {
                std::cout << "docs" << std::endl;
            } else if (argv[i] == std::string("-l")) {
                std::cout << "print the fs' structure" << std::endl;
            }
        }
    }
}

