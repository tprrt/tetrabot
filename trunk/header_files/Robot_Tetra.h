#ifndef ROBOT_TETRA
#define ROBOT_TETRA

#include "Robot.h"
#include "Boule.h"
#include "Piston.h"
#include "Action.h"
#include <Ogre.h>
class Robot_Tetra: public Robot<Boule*,Piston*>
{
public:
	Robot_Tetra(btDynamicsWorld* world,Ogre::SceneManager * scene);
	void deplacer();
	
};

#endif