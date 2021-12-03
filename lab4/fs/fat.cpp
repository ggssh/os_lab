//
// Created by ggssh on 2021/12/2.
//

#include "fat.h"

int FAT::init(int num) {
    for (int i = 0; i < num; i++) {
        freeDiskBlock.push(i);
    }
    return 0;
}
