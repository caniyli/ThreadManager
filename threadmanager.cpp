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
	if (!isRunning) {
		th = std::thread(&ThreadManager::run, this);
		isRunning = true;
	} else
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
	std::unique_lock<std::mutex> lock(mtx);

	while (true) {
		conditionVariable.wait_for(lock,
								   std::chrono::milliseconds(milliSecond));
		if (stop_)
			break;
		int temp = cb();
		if (temp)
			break;
	}
	std::cout << "Thread sona erdi" << std::endl;
	isRunning = false;
}
