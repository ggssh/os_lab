//
// Created by ggssh on 2021/11/5 0005.
//

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "os_lab3.h"

using namespace std;

static vector<int> instructions(INST_NUM);// 需要执行的指令
int pos = 0;

// 函数声明
int inst_init();

int OPT(Job &job, int pid);

int FIFO(Job &job, int pid);

int LRU(Job &job, int pid);

int page_exchange(Job &job, int pid);

bool is_exist(Job job, int pid);

void display(Job job);

int get_next_position(int pos, int pid);

// 主函数
int main() {
//    vector<Page> pages;
    Job job;// 初始化作业

    inst_init();
//    std::sort(instructions.begin(), instructions.end());
    for (auto i = 0; i < instructions.size(); i++, pos = i) {
        int pid = instructions[i] / 10;// 当前执行的指令所在的页面
        display(job);
        cout << "当前执行的指令序号为:" << instructions[i] << " 指令所在的页面号为:" << pid;
        if (!is_exist(job, pid)) {
            cout << " 发生缺页";
            // 如果不存在需要的页面(一个页面都没有/四个页面都不是需要的),则执行页面置换算法
            page_exchange(job, pid);
            job.replace_times++;// 缺页次数+1
        }
        cout << endl << endl;
        for (auto &page: job.pages) {
            if (page.id != -1) {
                // 修改自上次访问以来所经历的时间
                if (page.id == pid) page.latest_visit_time = 0;
                else page.latest_visit_time++;
                // 修改在内存中驻留的时间
                page.stayed_time++;
            }
        }
    }
    cout << "缺页次数:" << job.replace_times << endl;
    cout << "缺页率:" << job.replace_times / 320.0 << endl;
    return 0;
}

int page_exchange(Job &job, int pid) {
    for (auto &page: job.pages) {
        // 如果有空的页面,则直接装入
        if (page.id == -1) {
            page.id = pid;
            page.latest_visit_time = 0;
            page.stayed_time = 0;
            return 0;
        }
    }
    // 在分配给作业的4个内存块中找不到,需要进行页面置换操作
#ifdef _OPT
    OPT(job, pid);
#else
#ifdef _FIFO
    FIFO(job, pid);
#else
    LRU(job, pid);
#endif
#endif
    return 0;
}

/**
 * 初始化指令集合
 * @return
 */
int inst_init() {
    int count = 0;
    int m;
    m = get_random(0, INST_NUM - 1);
    instructions[count++] = m;
    instructions[count++] = m + 1;
    int m1 = 0, m2 = 0;
    LOOP {
        // 前地址部分
        m1 = get_random(0, m - 1);
        instructions[count++] = m1;
        if (count == INST_NUM) break;
        // 顺序执行
        instructions[count++] = m1 + 1;
        if (count == INST_NUM) break;

        // 后地址部分
        m2 = get_random(m1 + 2, 319);
        instructions[count++] = m2;
        if (count == INST_NUM) break;
        // 顺序执行
        instructions[count++] = m2 + 1;
        if (count == INST_NUM) break;
    };
    return 0;
}

/**
 * 最佳置换算法无法实现的根本原因是计算机没有办法确定将来要执行哪些指令,
 * 在本实验中,由于已给定具体的实施办法
 * 所以指令的执行顺序是可以确定的,能够实现最佳置换算法
 */
int OPT(Job &job, int pid) {
    int max_id = -1;
    int max_next_position = INT_MIN;
    for (auto page: job.pages) {
        if (get_next_position(pos, page.id) == -1) {
            max_id = page.id;
            break;
        }
        if (get_next_position(pos, page.id) > max_next_position) {
            max_next_position = get_next_position(pos, page.id);
            max_id = page.id;
        }
    }

    for (auto &page: job.pages) {
        if (page.id == max_id) {
            page.id = pid;
            page.stayed_time = 0;
            page.latest_visit_time = 0;
        }
    }
    return 0;
}

/**
 * 先进先出算法
 */
int FIFO(Job &job, int pid) {
    int max_id = -1;
    int max_stayed_time = INT_MIN;
    for (auto page: job.pages) {
        if (max_stayed_time < page.stayed_time) {
            max_stayed_time = page.stayed_time;
            max_id = page.id;
        }
//        max_stayed_time = max(max_stayed_time, page.stayed_time);
//        max_id = page.id;
    }
    for (auto &page: job.pages) {
        if (page.id == max_id) {
            page.id = pid;
            page.stayed_time = 0;
            page.latest_visit_time = 0;
        }
    }
    return 0;
}

/**
 * 最近最久未使用算法
 */
int LRU(Job &job, int pid) {
    int max_id = -1;
    int max_latest_visit = INT_MIN;
    for (auto page: job.pages) {
        if (max_latest_visit < page.latest_visit_time) {
            max_latest_visit = page.latest_visit_time;
            max_id = page.id;
        }
    }
    for (auto &page: job.pages) {
        if (page.id == max_id) {
            page.id = pid;
            page.stayed_time = 0;
            page.latest_visit_time = 0;
        }
    }
    return 0;
}

/**
 * 在给当前页面分配的页面中查找有没有指令所在的页面
 * @param job
 * @param pid
 * @return
 */
bool is_exist(Job job, int pid) {
    for (auto item: job.pages) {
        if (item.id == pid) return true;
    }
    return false;
}

void display(Job job) {
    // 页面号为-1表示这个块还没有装入页面
    cout << "作业内的页面: ";
    for (auto item: job.pages) {
        cout << item.id << " ";
    }
    cout << endl;
    cout << "stayed_time: ";
    for (auto item: job.pages) {
        cout << item.stayed_time << " ";
    }
    cout << "latest_visit_time: ";
    for (auto item: job.pages) {
        cout << item.latest_visit_time << " ";
    }
    cout << endl;
}

int get_next_position(int pos, int pid) {
    for (int i = pos + 1; i < instructions.size(); i++) {
        // 找到未来再次使用距离现在的时间,求出时间间隔
        if (pid == instructions[i] / 10) return i - pos;
    }
    return -1;
}

