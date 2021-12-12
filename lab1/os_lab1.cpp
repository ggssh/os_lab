#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "pcb.h"

using namespace std;
static const string enum_str[4] = {"READY", "BLOCK", "FINISH", "RUNNING"};

void init();// 队列初始化
void print_result(int i);// 打印结果
vector<PCB> ready_queue;// 就绪队列
vector<PCB> block_queue;// 阻塞队列
vector<PCB> finished_queue;// 已完成队列

bool comp(const PCB p1, const PCB p2) {
    // 优先级高的排到前面
    return p1.priority > p2.priority;
}

bool comp1(const PCB p1, const PCB p2) {
    return p1.id < p2.id;
}

int main() {
    init();
    int count = 1;
    // 直到就绪队列为空,每次循环相当于一个时间片
    while (!ready_queue.empty()) {
        // 对就绪队列进行排序
        sort(ready_queue.begin(), ready_queue.end(), comp);
        ready_queue.front().state = STATE::RUNNING;
        for (int i = 1; i < ready_queue.size(); i++) {
            ready_queue.at(i).state = STATE::READY;
//            ready_queue.at(i).priority++;
        }
        print_result(count++);

        ready_queue.front().priority -= 3;
        ready_queue.front().cpu_time++;
        ready_queue.front().all_time--;

        for (int i = 1; i < ready_queue.size(); i++) {
            ready_queue.at(i).state = STATE::READY;
            ready_queue.at(i).priority++;
        }
//        sort(ready_queue.begin(), ready_queue.end(), comp);
        // 判断是否需要就绪转阻塞,阻塞转就绪
        for (auto i = 0; i < block_queue.size(); ++i) {
            block_queue.at(i).block_time--;
            if (block_queue.at(i).block_time == 0) {
                block_queue.at(i).state = STATE::READY;
                ready_queue.emplace_back(block_queue.at(i));
                block_queue.erase(block_queue.begin() + i);
//                sort(ready_queue.begin(), ready_queue.end(), comp);
            }
        }

//        for (auto i = 0; i < ready_queue.size(); ++i) {
//            if (ready_queue.at(i).start_block > 0) {
//                ready_queue.at(i).start_block--;
//                if (ready_queue.at(i).start_block == 0) {
//                    ready_queue.at(i).state = STATE::BLOCK;
//                    block_queue.emplace_back(ready_queue.at(i));
//                    ready_queue.erase(ready_queue.begin() + i);
//                }
//            }
//        }
//        sort(ready_queue.begin(), ready_queue.end(), comp);

        if (ready_queue.front().start_block > 0) {
            ready_queue.front().start_block--;
            if (ready_queue.front().start_block == 0) {
                ready_queue.front().state = STATE::BLOCK;
                block_queue.emplace_back(ready_queue.front());
                ready_queue.erase(ready_queue.begin() + 0);

            }
        }

        if (!ready_queue.front().all_time) {
            ready_queue.front().state = STATE::FINISHED;
            finished_queue.emplace_back(ready_queue.front());
            ready_queue.erase(ready_queue.begin());
        }
//        sort(ready_queue.begin(), ready_queue.end(), comp);
//        if (!ready_queue.empty()) {
//            ready_queue.front().state = STATE::RUNNING;
//            for (int i = 1; i < ready_queue.size(); i++) {
//                ready_queue.at(i).state = STATE::READY;
//                ready_queue.at(i).priority++;
//            }
//        }
//        print_result(count++);
    }

    print_result(count++);
    cout << "运行完成" << endl;
    return 0;
}

// 初始化
void init() {
    ready_queue.emplace_back(PCB(0, 9, 0, 3, 2, 3, STATE::READY));
    ready_queue.emplace_back(PCB(1, 38, 0, 3, -1, 0, STATE::READY));
    ready_queue.emplace_back(PCB(2, 30, 0, 6, -1, 0, STATE::READY));
    ready_queue.emplace_back(PCB(3, 29, 0, 3, -1, 0, STATE::READY));
    ready_queue.emplace_back(PCB(4, 0, 0, 4, -1, 0, STATE::READY));
}

// 格式化打印
void print_result(int i) {
    cout << "第" << i << "个时间片:" << endl;
    cout << "RUNNING PROG: " << ready_queue.front().id << endl;
    cout << "READY_QUEUE:";
    for (auto item: ready_queue) {
        cout << " -> " << item.id;
    }
    cout << endl;
    cout << "BLOCK_QUEUE:";
    for (auto item: block_queue) {
        cout << " -> " << item.id;
    }
    cout << endl;
    cout << "FINISHED_QUEUE:";
    for (auto item: finished_queue) {
        cout << " -> " << item.id;
    }
    cout << endl;
    cout << " = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
    vector<PCB> temp;
    temp.insert(temp.end(), ready_queue.begin(), ready_queue.end());
    temp.insert(temp.end(), block_queue.begin(), block_queue.end());
    temp.insert(temp.end(), finished_queue.begin(), finished_queue.end());
    std::sort(temp.begin(), temp.end());
    cout << "ID            ";
    for (auto item: temp) {
        cout.width(7);
        cout << item.id << "        ";
    }
    cout << endl;
    cout << "PRIORITY      ";
    for (auto item: temp) {
        cout.width(7);
        cout << item.priority << "        ";
    }
    cout << endl;
    cout << "CPUTIME       ";
    for (auto item: temp) {
        cout.width(7);
        cout << item.cpu_time << "        ";
    }
    cout << endl;
    cout << "ALLTIME       ";
    for (auto item: temp) {
        cout.width(7);
        cout << item.all_time << "        ";
    }
    cout << endl;
    cout << "STARTBLOCK    ";
    for (auto item: temp) {
        cout.width(7);
        cout << item.start_block << "        ";
    }
    cout << endl;
    cout << "BLOCKTIME     ";
    for (auto item: temp) {
        cout.width(7);
        cout << item.block_time << "        ";
    }
    cout << endl;
    cout << "STATE         ";
    for (auto item: temp) {
        cout.width(7);
        cout << enum_str[static_cast<int>(item.state)] << "        ";
    }
    cout << endl;
    cout << endl;
}