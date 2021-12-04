//
// Created by ggssh on 2021/11/14 0014.
//
#include <iostream>
#include "config.h"
#include "file_system.h"

using namespace std;

int main(int argc, char *argv[]) {
//    // 解析命令行参数
//    parse_arg(argc, argv);
    FileSystem fileSystem;
    //
//    fileSystem.create("file1");
//    fileSystem.mkdir("folder1");
//    fileSystem.ls();
//    cout<<endl;
//
//    fileSystem.cd("folder1");
//    fileSystem.create("file1");
//    fileSystem.ls();
//    cout<<endl;

    fileSystem.start();

//    fileSystem.cd("..");
//    fileSystem.ls();
//    cout<<endl;
//
//    fileSystem.rm("file1");
//    fileSystem.ls();
//    cout<<endl;
//
//    fileSystem.rmdir("folder1");
//    fileSystem.ls();
//    cout<<endl;


    return 0;
}