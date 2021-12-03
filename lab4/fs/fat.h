//
// Created by ggssh on 2021/12/2.
//

#ifndef OS_LAB_FAT_H
#define OS_LAB_FAT_H

#include <iostream>
#include <stack>
#include <vector>

#define BLOCK_SIZE = 4096

using namespace std;

class FAT{
public:
    stack<int> freeDiskBlock; // 空磁盘块栈
    stack<int> fullDiskBlock; // 已占用磁盘块

    int init(int num);

    int get_block();


};

#endif //OS_LAB_FAT_H
