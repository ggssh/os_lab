//
// Created by ggssh on 2021/11/4 0004.
//

#ifndef OS_LAB_PCB_H
#define OS_LAB_PCB_H

enum class STATE {
    READY = 0,// 就绪
    BLOCK,// 阻塞
    FINISHED,//
    RUNNING
};

class PCB {
public:
    unsigned int id;// 进程标识数
    int priority;// 进程优先数(越大优先级越高)
    int cpu_time;// 进程已占用的CPU时间
    int all_time;// 进程还需占用的CPU时间
    int start_block;// 进程再运行start_block个时间片后进入阻塞状态
    int block_time;// 已阻塞的进程再等待block_time个时间片后转换成就绪状态
    STATE state;// 进程状态

    bool operator<(const PCB &pcb) const {
        return priority < pcb.priority;//优先级高的先出列
    }

    PCB(unsigned int id, int priority, int cpuTime, int allTime, int startBlock, int blockTime, STATE state) :
            id(id),

            priority(
                    priority),
            cpu_time(
                    cpuTime),
            all_time(
                    allTime),
            start_block(
                    startBlock),
            block_time(
                    blockTime),
            state(state) {}
};

#endif //OS_LAB_PCB_H
