#include "threadmanager.h"
#include <iostream>
int i = 0;
int run()
{
	
	i += 1;
    std::cout << "Asking Worker to Stop  " << i << std::endl;
    
	if (i > 10)
		return -1;

	return 0;
}

int main()
{
	ThreadManager threadManager;
	threadManager.setFunc(run);
	threadManager.setInterval(100);
	threadManager.start();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    threadManager.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(6000));
    /*std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "---1";
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
    
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));*/
	return 0;
}
