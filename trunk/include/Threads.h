#ifndef THREADS_H
#define THREADS_H

#include <cstdio>
#include <cstdlib>

//#define USE_PARALLEL_SOLVER 1 //experimental parallel solver
#define USE_PARALLEL_DISPATCHER 1

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h"

#ifdef WIN32 // HEADERS SPECIFIQUES A LA CREATION DE THREADS
	#include <windows.h>
	void sleep(long seconde);
	void msleep(long milliseconde);
#else 
	#include <unistd.h>
	#define psleep(sec) sleep (sec)
	void msleep(long milliseconde);
	#include <pthread.h>
#endif // HEADERS SPECIFIQUES A LA CREATION DE THREADS

// FONCTION PERMETTANT DE CREER UN THREAD
	void* Thread(void* data,void* (*fct_exe)(void*));

// Fonction pour terminer un Thread
	void ExitThread(void* status);
#endif //THREADS_H
