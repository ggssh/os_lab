//
// Created by ggssh on 2021/12/2.
//

#include "file.h"

void File::display() {
    cout << "The content in file :" << endl;
    cout << this->content << endl;
}

File::File(string name) {
    this->name = name;
    this->content = "";
    this->update_time = "2021/12/02 00:00:00";
    this->type = FileType::_FILE;
    this->access = Access::_RWE; // 默认为可执行
    this->father = nullptr;
    this->size = 0;
}


