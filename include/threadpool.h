#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include<iostream>
#include<queue>
#include<thread>
#include<functional>
#include<future>
#include<mutex>

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
    template<typename Func,typename ...Args>
    void AddTask(Func func,Args...arg);
    template<typename Func,typename...Args>
    auto AddTaskWithRt(Func func,Args...args)->std::future<decltype(func(args...))>;
    void AddThread(int num=1);
    template<typename ...Ty>
    std::function<void()>MakeFunction(Ty...args);
    void DeleteThread(size_t num=1);
private:
    std::queue<Task>tasks;
    bool start;
    bool stop;
    bool pause;
    std::condition_variable con_var;
    std::mutex mtx;
};
template<typename Func,typename...Args>
void ThreadPool::ThreadPool::AddTask(Func func,Args ...args)
{
    std::function<void()>task=std::bind(func,args...);
    Task myTask;
    myTask.task=task;
    {
        std::lock_guard<std::mutex>lck(mtx);
        tasks.push(myTask);
    }
}

template<typename Func,typename ...Args>
auto ThreadPool::AddTaskWithRt(Func func,Args...args)->std::future<decltype(func(args...))>
{
    using retType=decltype(func(args...));
    std::packaged_task<retType>task(std::bind(func,args...));
    std::future<retType>future=task.get_future();
    {
        std::lock_guard<std::mutex>lck(mtx);
        Task mytask;
        mytask.task=task;
        tasks.push(mytask);
    }
    return future; 
}

#endif