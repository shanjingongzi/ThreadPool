#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include<iostream>
#include<queue>
#include<thread>
#include<functional>
#include<future>

namespace {
    enum Leavel{ONE,TWO,THREE};
    struct Task
   {
        std::function<void()>task;
        Leavel leavel; 
   };
}
class ThreadPool
{
public:
    ThreadPool();
    ThreadPool(size_t size);
    void AddTask(std::function<void()>);
    template<typename T>
    std::future<T>AddTaskWithRt(std::function<void()>);
    void AddThread(int num=1);
    template<typename ...Ty>
    std::function<void()>MakeFunction(Ty...args);
    void DeleteThread(size_t num=1);

private:
    std::queue<std::function<void>>TaskQue;
    bool start;
    bool stop;
    bool pause;
};

#endif