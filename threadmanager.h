#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <condition_variable>

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
	bool stop_ = false;
    bool isRunning = false;
	int milliSecond = 1000;
	std::function<int()> cb = NULL;
	void run();
    std::thread th;
    std::mutex mtx;
    std::condition_variable conditionVariable;
};

#endif // THREADMANAGER_H
