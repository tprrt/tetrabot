#ifndef ROBOTWHELLS_H
#define ROBOTWHELLS_H
/* Created by GONZALEZ 
  june 3rd 2009
*/

#include "PhysicRobot.h"
#include "PhysicNoeud.h"
#include "PhysicPiston.h"

#include "ActionPiston.h"


class RobotWhells: public PhysicRobot
{

public:	
	btRigidBody* bodyCube;
	btVector3* end;
	
public:
	// Test avec GL
	RobotWhells(btDynamicsWorld* world,const btVector3& posInit);

	btVector3 getCenterOfMassPosition();
	
	// Deplacer le robot
	void translate(const btVector3& to);
};

#endif /* ROBOTWHELLS_H */