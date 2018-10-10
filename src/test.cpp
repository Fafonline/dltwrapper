#include <iostream>
#include <thread>
#include <chrono>

#include "DLTLogger.h"



#ifdef __LINUX__
#include <pthread.h>
#endif


void call_from_thread()
{
	std::string s = "thread1";
	DLTCtx("LOOP", "Secondary thread");

	pthread_setname_np(pthread_self(), s.c_str()); // set the name (pthread_self() returns the pthread_t of the current thread)
	pthread_getname_np(pthread_self(), (char*)(&s.c_str()[0]), s.size());

	while(true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		static bool toggle = 1;
		DLTLog("LOOP",DLT_LOG_INFO,"[%s] %s",s.c_str(),(toggle?"tic":"toc"));
		toggle =!toggle;
	}
}




int main(int arg, char* argv[])
{
	DLT_REGISTER_APP("TEST","DLT test context");

	DLTCtx("MAIN","Main process");

	DLTLog("MAIN",DLT_LOG_INFO,"Test started");

	std::thread l_loop(call_from_thread);

	l_loop.join();

	DLTLog("MAIN",DLT_LOG_INFO,"exit");

	DLT_UNREGISTER_APP();

	return 0;
}
