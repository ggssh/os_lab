cmake_minimum_required(VERSION 3.16)
project(os_lab)

set(CMAKE_CXX_STANDARD 17)

# 使用动态优先权的进程调度算法模拟
add_executable(os_lab1 lab1/os_lab1.cpp lab1/pcb.h)

# 使用动态分区分配方式的模拟
#add_compile_definitions(os_lab2 PUBLIC _FIRST_FIT)# 首次适应算法debugflag
add_compile_definitions(os_lab2 PUBLIC _BEST_FIT)# 最佳适应算法
add_executable(os_lab2 lab2/os_lab2.cpp lab2/free_area.h)

# 请求调页存储管理方式的模拟、
#add_compile_definitions(os_lab3 PUBLIC _OPT)# 最佳置换算法
add_compile_definitions(os_lab3 PUBLIC _FIFO)# 先进先出算法
#add_compile_definitions(os_lab3 PUBLIC _LRU)# 最近最久未使用算法
add_executable(os_lab3 lab3/os_lab3.cpp lab3/os_lab3.h)

# 简单文件系统的实现
add_executable(os_lab4 lab4/os_lab4.cpp)