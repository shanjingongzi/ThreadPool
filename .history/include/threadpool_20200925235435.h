#include<iostream>
#include<queue>
#include<thread>
#include<functional>
#include<future>
class ThreadPool
{
public:
    ThreadPool();
    ThreadPool(size_t size);
    void AddTask();
    template<typename T>
    std::future<T>AddTaskWi();
    void AddThread(int num=1);
    
private:
    std::queue<std::function<void>>TaskQue;

};