//
// Created by ggssh on 2021/11/5 0005.
//
#include <iostream>
#include <list>
#include <deque>
#include "free_area.h"

#define MEMORY_SIZE 640
#define OK 0
#define ERROR -1
using namespace std;

list<FreeArea> area_list;
static const string enum_str[4] = {"FREE", "BUSY", "申请", "释放"};
// 作业操作
enum Option {
    _ALLOC = 0,
    _FREE
};
struct job {
    int id;// 作业号
    Option option;// 操作类型 alloc/free
    int size;// 申请或释放的大小
};
deque<job> work_queue;// 作业队列

void init();

void display();

int FF(int id);

int BF(int id);

int Recycle(int id);

int main() {
    init();
    while (!work_queue.empty()) {
        if (work_queue.front().option == _ALLOC) {
#ifdef FIRST_FIT
            FF(work_queue.front().id);
//            if (FF() != OK) cerr << "Memory allocation failed." << endl;
#else
            BF(work_queue.front().id);
#endif
        } else {
            Recycle(work_queue.front().id);
        }
        display();
        cout << endl;
        work_queue.pop_front();
    }
    return 0;
}

void init() {
    FreeArea freeArea(0, MEMORY_SIZE, 1, FREE);
    area_list.emplace_back(freeArea);
    // 初始化作业队列
    work_queue.emplace_back(job{1, _ALLOC, 130});
    work_queue.emplace_back(job{2, _ALLOC, 60});
    work_queue.emplace_back(job{3, _ALLOC, 100});
    work_queue.emplace_back(job{2, _FREE, 60});
    work_queue.emplace_back(job{4, _ALLOC, 200});
    work_queue.emplace_back(job{3, _FREE, 100});
    work_queue.emplace_back(job{1, _FREE, 130});
    work_queue.emplace_back(job{5, _ALLOC, 140});
    work_queue.emplace_back(job{6, _ALLOC, 60});
    work_queue.emplace_back(job{7, _ALLOC, 50});
    work_queue.emplace_back(job{6, _FREE, 60});
}

void display() {
    cout << "作业" << work_queue.front().id << enum_str[static_cast<int >(work_queue.front().option) + 2]
         << work_queue.front().size << "KB" << endl;
    for (auto item: area_list) {
        cout << item.id << " " << item.start_address << " " << item.start_address + item.size - 1 << " "
             << enum_str[static_cast<int>(item.state)] << endl;
    }
}

int FF(int id) {
    job j = work_queue.front();
    for (auto it = area_list.begin(); it != area_list.end(); it++) {
        if (it->size > j.size && it->state == FREE) {// 空闲分区大小大于申请的
            FreeArea freeArea(id, j.size, it->start_address, BUSY);
            // 在当前位置的前面插入
            area_list.insert(it, freeArea);
            it->start_address = freeArea.size + freeArea.start_address;
            it->size -= freeArea.size;
        } else if (it->size == j.size && it->state == FREE) {// 空闲分区大小等于作业申请的
            it->state = BUSY;
        }
    }
    return OK;
}

int BF(int id) {
    job j = work_queue.front();
    list<FreeArea>::iterator iter = area_list.end();
    int min_size = MEMORY_SIZE;
    for (auto it = area_list.begin(); it != area_list.end(); it++) {
        if ((it->size > j.size || it->size == j.size) && it->state == FREE) {
            if (it->size - j.size < min_size) {
                iter = it;
                min_size = it->size - j.size;
            }
        }
    }
    if (iter == area_list.end()) {
        return ERROR;
    } else {
        if (min_size == 0) {
            iter->state = BUSY;
        } else {
            FreeArea freeArea(id, j.size, iter->start_address, BUSY);
            area_list.insert(iter, freeArea);
            iter->size -= freeArea.size;
            iter->start_address = freeArea.size + freeArea.start_address;
        }
    }
    return OK;
}

int Recycle(int id) {
    job j = work_queue.front();
    cout<<"free"<<j.id<<endl;
    return OK;
}