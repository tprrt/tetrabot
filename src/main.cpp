//  @ Project : Tetrabot
//  @ File Name : main.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#ifdef WIN32
#include "windows.h"
#else
#include <Ogre.h>
#endif
#else
#include <OGRE/Ogre.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>

#include "GLTetraRendering.h"
#include "btBulletDynamicsCommon.h"
#include "GlutStuff.h"
#include "GLDebugDrawer.h"
#include "TetraRendering.h"

GLDebugDrawer	gDebugDrawer;

#ifdef __cplusplus
extern "C" {
#endif


int main(int argc, char *argv[])
{
	if(argc>1)
	{
		if(strcmp(argv[1],"-D")==0 || strcmp(argv[1],"-d")==0)
		{// DEBUG MODE
			GLTetraRendering* RobotDemo = new GLTetraRendering();
			RobotDemo->initPhysics();
			//RobotDemo->getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);
			//RobotDemo->setDebugMode(btIDebugDraw::DBG_DrawConstraints+btIDebugDraw::DBG_DrawConstraintLimits);
			return glutmain(argc, argv,640,480,"TetraBot", RobotDemo);
		}
		if(strcmp(argv[1],"-v")==0 || strcmp(argv[1],"--version")==0)
		{// VERSION MODE
			printf("TETRABOT version 12.243 alpha\n");
		}
		if(strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0)
		{// VERSION MODE
			printf("Usage : tetrabot [OPTION]\n");
			printf("Ce projet vise à modéliser, simuler et faire évoluer un robot de type tétraédrique dans un environnement martien.\n\n");
			printf("  -d, -D\t\tdesactiver l' interface graphique OGRE\n");
			printf("  -h, --help\t\tafficher l'aide-mémoire\n");
			printf("  -v, --version\t\tafficher le nom et la version du logiciel\n\n");
			printf("Rapporter toutes anomalies sur <http://forum.artilect.fr>.\n");

		}
	}
	else
	{// OGRE MODE
		try 
		{
			TetraRendering *rendering = new TetraRendering();
			rendering->createScene();
			rendering->run();

			delete rendering;
		} 
		catch(Ogre::Exception& e) 
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}
		catch(...)
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, "Autre exception", "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " << std::endl;
#endif
		}
	return 0;
	}
}

	
#ifdef __cplusplus
}
#endif

