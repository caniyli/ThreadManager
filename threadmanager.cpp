#include "threadmanager.h"

ThreadManager::ThreadManager()
{
}

ThreadManager::~ThreadManager()
{
}

void ThreadManager::start()
{
	if (cb == NULL) {
		std::cout << "Thread başlatılamadı fonksiyon girilmeli" << std::endl;
		return;
	}
	stop_ = false;
	if (!th.joinable()) 
		th = std::thread(&ThreadManager::run, this);
	else
		std::cout << "Thread zaten çalışıyor" << std::endl;
}

void ThreadManager::stop()
{
	stop_ = true;
	conditionVariable.notify_all();
}

void ThreadManager::wait()
{
	th.join();
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
	conditionVariable.notify_one();
}

void ThreadManager::run()
{
	while (true) {
		{
			std::unique_lock<std::mutex> lock(mtx);
			conditionVariable.wait_for(lock,
									   std::chrono::milliseconds(milliSecond));
		}
		if (stop_)
			break;
		int temp = cb();
		if (temp)
			break;
	}
	std::cout << "Thread sona erdi" << std::endl;
}
