#ifndef THREAD_POOL_H
#define THREAD_POOL_H
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
        Task(){};
        Task(std::function<void()>infunc,Leavel inleavel=ONE):task(infunc),leavel(inleavel){}
   };
}
class ThreadPool
{
public:
    ThreadPool();
    ThreadPool(size_t size);
    template<typename Func,typename...Args>
    inline auto AddTask(Func func,Args...args)->std::future<decltype(func(args...))>;
    void AddThread(int num=1);
    template<typename ...Ty>
    std::function<void()>MakeFunction(Ty...args);
    void DeleteThread(size_t num=1);
private:
    std::queue<Task>tasks;
    bool stop;
    std::condition_variable con_var;
    std::mutex mtx;
};
template<typename Func,typename ...Args>
inline auto ThreadPool::AddTask(Func func,Args...args)->std::future<decltype(func(args...))>
{
    using retType=decltype(func(args...));
    auto task=std::make_shared<std::packaged_task<retType()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
    std::future<retType>fut;
    fut=task->get_future();
    {
        std::lock_guard<std::mutex>locker(mtx);
        tasks.emplace(Task(std::move([task]{(*task)();})));
    }
    con_var.notify_one();
    return fut;
}
#endif