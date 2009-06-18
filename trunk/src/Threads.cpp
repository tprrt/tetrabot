#include "Threads.h"

void* Thread(void* data,void* (*fct_exe)(void*))
{
	#ifdef WIN32
		DWORD threadID;
		return CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)fct_exe,data,  0, &threadID);
		
	#else
		pthread_t thread_action;
		pthread_create (&thread_action, NULL,fct_exe, data);
		return (void*)thread_action;
	#endif
}

#ifdef WIN32
void sleep(long seconde)
{
	Sleep((DWORD)(seconde*1000));
}

void msleep(long milliseconde)
{
	Sleep((DWORD)milliseconde);
}
#else
void msleep(long milliseconde)
{
	usleep(milliseconde*1000);
}
#endif

#ifdef WIN32
void ExitThread(void* status)
{
	ExitThread((DWORD) &status);
}
#else
void ExitThread(void* status)
{
	pthread_exit (status);
}
#endif
