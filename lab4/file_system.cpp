//
// Created by ggssh on 2021/12/3.
//

#include "file_system.h"

FileSystem::FileSystem() {
    root = new Folder("/");
    current_folder = root;
}

void FileSystem::ls() {
    cout << current_path << endl;
    current_folder->list();
    cout << endl;
}

void FileSystem::create(const string file_name) {
    current_folder->add_child(new File(file_name));
}

void FileSystem::mkdir(const string folder_name) {
    auto folder = new Folder(folder_name);
    folder->father = this->current_folder;
    current_folder->add_child(folder);
}

void FileSystem::cd(const string folder_name) {
    // 返回上级目录
    if (folder_name == "..") {
        if (current_folder->father != nullptr) {
//            auto l1 = current_path.length();
//            auto l2 = current_folder->name.length();
            // 要把最后的/给去掉
            current_path = current_path.substr(0, current_path.length() - current_folder->name.length() - 1);
            current_folder = static_cast<Folder *>(current_folder->father);
            return;
        }
    }
    auto children = current_folder->child;
    for (int i = 0; i < children.size(); i++) {
        // 如果在当前目录下找到和指定目录名一样的folder,更改current_folder
        if (children[i]->name == folder_name && children[i]->type == FileType::_FOLDER) {
            current_folder = static_cast<Folder *>(current_folder->child[i]);
            current_path = current_path + "/" + current_folder->name;
            return;
        }
    }
}

void FileSystem::rm(const string file_name) {
    auto children = current_folder->child;
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->name == file_name && children[i]->type == FileType::_FILE) {
            // 删除指定位置的文件
            current_folder->child.erase(current_folder->child.begin() + i);
        }
    }
}

void FileSystem::rmdir(const string folder_name) {
    // 递归删除(先不考虑,能过再说,顶多是内存泄露而已)
    // 从里到外删
    auto children = current_folder->child;
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->name == folder_name && children[i]->type == FileType::_FOLDER) {
            current_folder->child.erase(current_folder->child.begin() + i);
        }
    }
}

void FileSystem::start() {
    cout << "Welcome to yyz's shell" << endl;
    string cmd;
//    cin 输入字符串 遇到空格,TAB,回车都结束
    while (cin >> cmd) {
        if (cmd == "ls") ls();
        else if (cmd == "cd") {
            string name;
            cin >> name;
            cd(name);
            ls();
        } else if (cmd == "mkdir") {
            string name;
            cin >> name;
            mkdir(name);
            ls();
        } else if (cmd == "create") {
            string name;
            cin >> name;
            create(name);
            ls();
        } else if (cmd == "rm") {
            string name;
            cin >> name;
            rm(name);
            ls();
        } else if (cmd == "rmdir") {
            string name;
            cin >> name;
            rmdir(name);
            ls();
        } else if (cmd == "quit") {
            cout << "Exit yyz's shell successfully!" << endl;
            cout << "Have a nice day!";
            exit(0);
        }
    }
}
