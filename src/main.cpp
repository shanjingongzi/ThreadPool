#include<iostream>
#include "threadpool.h"
using namespace std;
int main()
{
    ThreadPool threadpool(10);
    threadpool.AddTask([](){return 1;});
}