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
    std::future<T>AddTaskWith();
    void AddThread(int num=1);
    
private:
    std::queue<std::function<void>>TaskQue;

};