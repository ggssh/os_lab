//
// Created by ggssh on 2021/11/20.
//

#ifndef OS_LAB_OS_LAB3_H
#define OS_LAB_OS_LAB3_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define INST_NUM 320
#define LOOP while(true)
using namespace std;

class Page;

class Job {
public:
    vector<Page> pages;// 分配给该作业的内存块数(页面数最大为4)
    int replace_times = 0;// 访问页面失败的次数F(即缺页次数)
    Job() {
        pages = vector<Page>(4);
    }
};

class Page {
public:
    int id;
    int stayed_time ;// 在内存中驻留时间
    int latest_visit_time ;// 自上次被访问以来所经历的时间

    Page() {
        id = -1;
        stayed_time=0;
        latest_visit_time=0;
    }

//    Page(unsigned int id) : id(id) {
//        stayed_time = 0;
//        latest_visit_time = 0;
//    }

//    bool operator==(const Page &page) {
//        return (this->id == page.id);
//    }
};

/**
 * 得到指定范围的随机数
 * @param min_value
 * @param max_value
 * @return
 */
int get_random(int min_value, int max_value) {
    int res = (rand() % (max_value - min_value + 1)) + min_value;
    return res;
}


#endif //OS_LAB_OS_LAB3_H
