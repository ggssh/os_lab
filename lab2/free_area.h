//
// Created by ggssh on 2021/11/16 0016.
//

#ifndef OS_LAB_FREE_AREA_H
#define OS_LAB_FREE_AREA_H

enum Status {
    FREE = 0,
    BUSY
};

class FreeArea {
public:
    int id;// 分区号
    int size;// 分区大小
    int start_address;// 当前分区首地址
    Status state;

    FreeArea(int id, int size, int startAddress, Status state) : id(id), size(size), start_address(startAddress),
                                                                 state(state) {}

//    bool operator==(const FreeArea &rhs) const {
//        return (id == rhs.id);
//    }
};

#endif //OS_LAB_FREE_AREA_H
