//
// Created by ggssh on 2021/12/3.
//

#ifndef OS_LAB_FILE_SYSTEM_H
#define OS_LAB_FILE_SYSTEM_H

#include <iostream>
#include "fs/file.h"
#include "fs/folder.h"

using namespace std;

class FileSystem {
private:
    string current_path = "/yyz";
    Folder *current_folder;
    Folder *root;
public:
    FileSystem();

    void format();

    /**
     * 显示目录
     */
    void ls();

    /**
     * 创建文件
     * @param filename
     */
    void create(const string filename);

    /**
     * 创建目录
     * @param folder_name
     */
    void mkdir(const string folder_name);

    /**
     * 更改当前目录
     * @param folder_name
     */
    void cd(const string folder_name);

    /**
     * 删除文件
     * @param file_name
     */
    void rm(const string file_name);

    /**
     * 删除目录
     * @param folder_name
     */
    void rmdir(const string folder_name);

    /**
     * 打开文件
     * @param file_name
     */
    void open(const string file_name);

    /**
     * 关闭文件
     * @param file_name
     */
    void close(const string file_name);

    /**
     * 写文件
     * @param file_name
     * @param content
     */
    void write(const string file_name,const string content);

    void read(const string file_name);
};


#endif //OS_LAB_FILE_SYSTEM_H
