//
// Created by ggssh on 2021/12/2.
//

#ifndef OS_LAB_FCB_H
#define OS_LAB_FCB_H

#include <iostream>
#include <vector>
#include "attributes.h"

using namespace std;

class FCB {
public:
    string name = "untitled"; //文件名+扩展名
    FileType type;
    Access access;
    string path;
    int size;
    string update_time; // 最近更新时间

    // 文件和文件夹都要有父节点
    FCB *father; // 父节点
};

#endif //OS_LAB_FCB_H
