//
// Created by ggssh on 2021/12/2.
//

#ifndef OS_LAB_FOLDER_H
#define OS_LAB_FOLDER_H

#include "fcb.h"

class Folder : public FCB {
public:
    // folder里面可以有file和folder
    vector<FCB *> child;

    void add_child(FCB *fcb);

    Folder(string name);

    void list();

    const char *EnumToStringF(FileType fileType) {
        switch (fileType) {
            case FileType::_FILE:
                return "FILE";
            case FileType::_FOLDER:
                return "FOLDER";
            default:
                return "Untitled";
        }
    }

    const char *EnumToStringA(Access access) {
        switch (access) {
            case Access::_RXX:
                return "r__";
            case Access::_RWX:
                return "rw_";
            case Access::_RWE:
                return "rwx";
            default:
                return "xxx";
        }
    }
};


#endif //OS_LAB_FOLDER_H
