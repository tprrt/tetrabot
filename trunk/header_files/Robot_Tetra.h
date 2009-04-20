#ifndef ROBOT_TETRA
#define ROBOT_TETRA

#include "Robot.h"
#include "Noeud.h"
#include "Piston.h"
#include "Action.h"
#include <Ogre.h>
class Robot_Tetra: public Robot
{
public:
	// Test avec GL
	Robot_Tetra(btDynamicsWorld* world,btVector3& posInit);
	// Test avec Ogre
	Robot_Tetra(btDynamicsWorld* world,Ogre::SceneManager * scene,btVector3& posInit);
	// methode  implementees
	btVector3 getCenterOfMassPosition();
	
};

#endif