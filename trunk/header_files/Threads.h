#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>


//#define USE_PARALLEL_SOLVER 1 //experimental parallel solver
#define USE_PARALLEL_DISPATCHER 1

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h"

#ifdef USE_PARALLEL_DISPATCHER
	#include "BulletMultiThreaded/SpuGatheringCollisionDispatcher.h"
	#include "BulletMultiThreaded/PlatformDefinitions.h"

	#ifdef USE_LIBSPE2
		#include "BulletMultiThreaded/SpuLibspe2Support.h"
	#elif defined (WIN32)
		#include "BulletMultiThreaded/Win32ThreadSupport.h"
		#include "BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h"
	#elif defined (USE_PTHREADS)
		#include "BulletMultiThreaded/PosixThreadSupport.h"
		#include "BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h"
	#else
	//other platforms run the parallel code sequentially (until pthread support or other parallel implementation is added)
		#include "BulletMultiThreaded/SequentialThreadSupport.h"
		#include "BulletMultiThreaded/SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h"
	#endif //USE_LIBSPE2

	#ifdef USE_PARALLEL_SOLVER
		#include "BulletMultiThreaded/SpuParallelSolver.h"
		#include "BulletMultiThreaded/SpuSolverTask/SpuParallellSolverTask.h"
	#endif //USE_PARALLEL_SOLVER

#endif//USE_PARALLEL_DISPATCHER

#ifdef WIN32 // HEADERS SPECIFIQUES A LA CREATION DE THREADS
	#include <windows.h>
	void sleep(long milliSec);
#else 
	#include <unistd.h>
	#define psleep(sec) sleep ((sec/1000))
	#include <pthread.h>
#endif // HEADERS SPECIFIQUES A LA CREATION DE THREADS

// FONCTION PERMETTANT DE CREER UN THREAD
	void Thread(void* data,void* (*fct_exe)(void*));
#endif //THREADS_H
