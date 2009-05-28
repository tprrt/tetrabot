#ifndef ROBOTTETRA
#define ROBOTTETRA


#include "Robot.h"
/*
#include "Noeud.h"
#include "Piston.h"
#include "Action.h"
#include "Caracteristiques.h"
#include "WorldPhysic.h"

*/
#include "ActionPiston.h"

class RobotTetra: public Robot
{
public:

	ActionPiston *action[6];
	
	btRigidBody* bodyCube;
	
	//ControleurRobot* controleur;
	
	// Test avec GL
	RobotTetra(btDynamicsWorld* world,const btVector3& posInit);

	// Test avec Ogre
	RobotTetra(btDynamicsWorld* world,Ogre::SceneManager * scene,const btVector3& posInit);

	btVector3 getCenterOfMassPosition();

	void stretch();

	void reduce();

	void move(int x, int y, int z);

};

#endif /* ROBOTTETRA */
