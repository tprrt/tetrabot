#include "GL_Piston.h"
#include "btBulletDynamicsCommon.h"

#include "GlutStuff.h"

#include "GLDebugDrawer.h"

GLDebugDrawer	gDebugDrawer;


int main(int argc,char** argv)
{
	GL_Piston* RobotDemo = new GL_Piston();

        RobotDemo->initPhysics();
		//RobotDemo->getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);
		//RobotDemo->setDebugMode(btIDebugDraw::DBG_DrawConstraints+btIDebugDraw::DBG_DrawConstraintLimits);
       
        return glutmain(argc, argv,640,480,"TetraBot Demo.", RobotDemo);

}




/*
 * main.h
 *
 *  Created on: 12 févr. 2009
 *      Author: Thomas PERROT
 */

/*
#include <cstdio>
#include <cstdlib>
#include <iostream>

//#include <OGRE/OgreConfig.h>
//#include <OIS/OIS.h>
//#include <CEGUI/CEGUI.h>
//#include <btBulletDynamicsCommon.h>
//#include <btBulletCollisionCommon.h>

#include "TetraRendering.h"


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <Ogre.h>
#else
#include <OGRE/Ogre.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char *argv[])
#endif
{
	try {
        TetraRendering *rendering = new TetraRendering();
		rendering->createScene();
		rendering->run();

		delete rendering;
    } catch(Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
#endif
    }
	catch(...){
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox( NULL, "Autre exception", "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else

        std::cerr << "An exception has occured: " << std::endl;
#endif
	}
    return 0;
}

#ifdef __cplusplus
}
#endif
*/