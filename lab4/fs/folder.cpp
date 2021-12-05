//
// Created by ggssh on 2021/12/2.
//

#include "folder.h"

void Folder::add_child(FCB *fcb) {
    this->child.emplace_back(fcb);
    fcb->father = this;
}

Folder::Folder(string name) {
    this->name = name;
    this->child.clear();
    this->update_time = "2021/12/02 00:00:00";
    this->size = 0;
    this->type = FileType::_FOLDER;
    this->access = Access::_CLOSED; //默认为关闭
    this->father = nullptr;
}

void Folder::list() {
    if (child.empty()) {
//        cout << "当前文件夹为空" << endl;
        return;
    }
    cout << "name        access        size        update_time            type" << endl;
    for (int i = 0; i < child.size(); i++) {
        cout << child[i]->name << "        " << EnumToStringA(child[i]->access) << "        " << child[i]->size
             << "        " << child[i]->update_time << "        "
             << EnumToStringF(child[i]->type) << endl;
    }
}
