//
// Created by ggssh on 2021/12/2.
//

#ifndef OS_LAB_ATTRIBUTES_H
#define OS_LAB_ATTRIBUTES_H


enum class Access {
    _RXX, // 只读
    _RWX, // 可读写
    _RWE, // 可执行
};

enum class FileType {
    _FILE, // 文件
    _FOLDER, // 文件夹
};



#endif //OS_LAB_ATTRIBUTES_H
