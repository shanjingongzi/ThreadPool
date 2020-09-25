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
    void AddTask(std::function<void()>);
    template<typename T>
    std::future<T>AddTaskWithRt(std::function<void()>);
    void AddThread(int num=1);
    template<typename ...Ty>
    
    
private:
    std::queue<std::function<void>>TaskQue;

};