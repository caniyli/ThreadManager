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
	stop_ = true;
	th = new std::thread(&ThreadManager::run, this);
}

void ThreadManager::stop()
{
	conditionVariable.notify_all();
	th->detach();
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
	/*std::lock_guard<std::mutex> G(mtx);
	std::cout << "notify" << std::endl;
	conditionVariable.notify_one();
    //th->detach();*/
}

void ThreadManager::run()
{
	std::unique_lock<std::mutex> lock(mtx);

	while (conditionVariable.wait_for(lock,
									  std::chrono::milliseconds(milliSecond)) ==
		   std::cv_status::timeout) {
		int temp = cb();
		if (temp)
			break;
	}
	std::cout << "Thread sona erdi" << std::endl;
}
