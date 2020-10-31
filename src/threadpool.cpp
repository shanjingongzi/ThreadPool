#include "threadpool.h"
using namespace std;
ThreadPool::ThreadPool(size_t size)
{
    for(size_t i=0;i<size;++i)
    {
        thread t(
            [this]()
            {
                while(!this->stop)
                {
                    unique_lock<mutex>lck(this->mtx);
                    this->con_var.wait(lck);
                    lck.lock();
                    Task task;
                    if(!this->tasks.empty())
                    {
                        task=this->tasks.front();
                        this->tasks.pop(); 
                        
                    }
                    lck.unlock();
                    task.task();
                    lck.lock();
                }
            }
        );
        t.detach();
    }
}

