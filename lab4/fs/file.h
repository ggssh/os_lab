//
// Created by ggssh on 2021/12/2.
//

#ifndef OS_LAB_FILE_H
#define OS_LAB_FILE_H

#include "fcb.h"

class File : public FCB {
public:
    string content; // 文件内容

    File(string name);

    void display();
};

#endif //OS_LAB_FILE_H
