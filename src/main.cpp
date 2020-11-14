#include<iostream>
#include "threadpool.h"
using namespace std;

void printer(const string &str)
{
    cout<<str<<endl;
}
int add(int a,int b)
{
    return a+b;
}
int main()
{
    ThreadPool threadpool(10);
    auto result=threadpool.AddTask(add,1,1);
    threadpool.AddTask(printer,"hello world");
    cout<<result.get()<<endl;
    system("pause");
}