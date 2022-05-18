#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <future>

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();
	void start();
	void stop();
	void wait();
	void setFunc(std::function<int(void)> cb);
	void setInterval(int x);
	void notify();

private:
	int milliSecond = 1000;
	std::function<int()> cb;
	void run();
    std::thread *th;
    std::mutex mtx;
    std::condition_variable conditionVariable;
};

#endif // THREADMANAGER_H
