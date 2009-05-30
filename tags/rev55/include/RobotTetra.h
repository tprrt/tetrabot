#ifndef ROBOTTETRA_H
#define ROBOTTETRA_H


#include "Robot.h"
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

	virtual ~RobotTetra();

	btVector3 getCenterOfMassPosition();

	void stretch();

	void reduce();

	void move(int x, int y, int z);

};

#endif /* ROBOTTETRA_H*/
