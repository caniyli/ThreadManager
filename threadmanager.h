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
	bool stop_ = true;
	bool waitforEnd = false;
	int miliSecond = 1000;
	std::function<int()> cb;
	void run();
	std::chrono::steady_clock::time_point startTime;
    std::thread *th;
    std::condition_variable cv;
    std::mutex m;
};

#endif // THREADMANAGER_H
