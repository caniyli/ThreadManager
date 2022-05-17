#include "threadmanager.h"

ThreadManager::ThreadManager()
{
}

ThreadManager::~ThreadManager()
{
    delete th;
}

void ThreadManager::start()
{
	startTime = std::chrono::steady_clock::now();
	stop_ = true;
	waitforEnd = false;
	th = new std::thread(&ThreadManager::run, this);
}

void ThreadManager::stop()
{
}

void ThreadManager::wait()
{
	th->join();
}

void ThreadManager::setFunc(std::function<int()> cb)
{
	this->cb = cb;
}

void ThreadManager::setInterval(int x)
{
	milliSecond = x;
}

void ThreadManager::notify()
{
	std::cout << "thread notify" << std::endl;
}

void ThreadManager::run()
{
	while (stop_) {
		int temp = cb();
        if(temp) break;
		std::this_thread::sleep_for(std::chrono::milliseconds(milliSecond));
	}
}
