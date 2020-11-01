#include "threadpool.h"
using namespace std;
ThreadPool::ThreadPool(size_t size)
{
    for(size_t i=0;i<size;++i)
    {
        std::thread t(
            [this]()
            {
               while(!this->stop)
               {
                   unique_lock<mutex>lck(this->mtx);
                   this->con_var.wait(lck);
                   

               }
            }
        );
        t.detach();
    }
}

