#include "threadpool.h"
using namespace std;
ThreadPool::ThreadPool(size_t size):stop(false)
{
    for(size_t i=0;i<size;++i)
    {
        std::thread t(
            [this]()
            {
               while(!this->stop)
               {
                   Task preTask;
                   {
                       unique_lock<mutex>lck(this->mtx);
                       this->con_var.wait(lck,[this](){return !(this->tasks.empty());});
                       if(!tasks.empty())
                       {
                            preTask=std::move(tasks.front());
                            tasks.pop();
                       }
                   }
                   preTask.task();
               }
            }
        );
        t.detach();
    }
}

