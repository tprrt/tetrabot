#include "Threads.h"
#include <stdio.h>



void Thread(void* data,void* (*fct_exe)(void*))
{
	#ifdef WIN32
		DWORD threadID;
		CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)fct_exe,data,  0, &threadID);
		
	#else
		pthread_t thread_action;
		pthread_create (&thread_action, NULL,fct_exe, data);
	#endif
}

#ifdef WIN32
void sleep(long milliSec)
{
	Sleep((DWORD)milliSec);
}
#endif