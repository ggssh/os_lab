//
// Created by ggssh on 2021/11/5 0005.
//
#include <iostream>
#include <iomanip>
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

int FF();

int BF();

int Recycle();

int main() {
    init();
#ifdef _FIRST_FIT
    cout << "采用首次适应算法" << endl;
#else
    cout << "采用最佳适应算法" << endl;
#endif
    while (!work_queue.empty()) {
        if (work_queue.front().option == _ALLOC) {
#ifdef _FIRST_FIT
            FF();
#else
            BF();
#endif
        } else {
            Recycle();
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
    cout << "起始地址" << "    " << "结束地址" << "      " << "大小" << "       " << "状态" << "   " << "任务id" << endl;
    for (auto item: area_list) {
        string s = "";
        if (item.id > 0) s = to_string(item.id);
        else s = "无";
        cout << setw(6) << item.start_address << "    ";
        cout << setw(6) << item.start_address + item.size - 1 << "   ";
        cout << setw(6)
             << item.size << "KB";
        cout << setw(6) << "    "
             << enum_str[static_cast<int>(item.state)] << "    ";
        cout << s << endl;
    }
}

int FF() {
    job j = work_queue.front();
    for (auto it = area_list.begin(); it != area_list.end(); it++) {
        if (it->size > j.size && it->state == FREE) {// 空闲分区大小大于申请的
            FreeArea freeArea(j.id, j.size, it->start_address, BUSY);
            // 在当前位置的前面插入
            area_list.insert(it, freeArea);
            it->start_address = freeArea.size + freeArea.start_address;
            it->size -= freeArea.size;
            break;
        } else if (it->size == j.size && it->state == FREE) {// 空闲分区大小等于作业申请的
            it->state = BUSY;
            break;
        }
    }
    return OK;
}

int BF() {
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
            FreeArea freeArea(j.id, j.size, iter->start_address, BUSY);
            area_list.insert(iter, freeArea);
            iter->size -= freeArea.size;
            iter->start_address = freeArea.size + freeArea.start_address;
        }
    }
    return OK;
}

int Recycle() {
    job j = work_queue.front();
    for (auto it = area_list.begin(); it != area_list.end(); it++) {
        if (it->id == j.id && it->state == BUSY) {
            list<FreeArea>::iterator it_prev = it;
            list<FreeArea>::iterator it_next = it;
            it_prev--;// 当前结点的前驱结点
            it_next++;// 当前结点的后继结点
            if (it == area_list.begin()) {
                if (it_next->state == FREE) {
                    it->id = 0;
                    it->size += it_next->size;
                    it->state = FREE;
                    area_list.erase(it_next);
                    break;
                }
                it->id = 0;
                it->state = FREE;
                break;
            }
            if (it_prev->state == FREE && it_next->state == BUSY) {
                it_prev->size += it->size;
                it_prev->id = 0;
                area_list.erase(it);
                break;
            }
            if (it_prev->state == BUSY && it_next->state == FREE) {
                it->size += it_next->size;
                it->id = 0;
                it->state = FREE;
                area_list.erase(it_next);
                break;
            }
            if (it_prev->state == FREE && it_next->state == FREE) {
                it_prev->size += (it->size + it_next->size);
                it_prev->id = 0;
                area_list.erase(it);
                area_list.erase(it_next);
                break;
            }
            if (it_prev->state == BUSY && it_next->state == BUSY) {
                it->id = 0;
                it->state = FREE;
                break;
            }
        }
    }
    return OK;
}