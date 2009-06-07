#ifndef ROBOTTETRA
#define ROBOTTETRA


#include "PhysicRobot.h"
#include "PhysicNoeud.h"
#include "PhysicPiston.h"
/*
#include "Action.h"
#include "Caracteristiques.h"
#include "WorldPhysic.h"
*/
#include "ActionPiston.h"

class RobotTetra: public PhysicRobot
{
protected:

	ActionPiston *action[6];
public:	
	btRigidBody* bodyCube;
	
public:
	// Test avec GL
	RobotTetra(btDynamicsWorld* world,const btVector3& posInit);

	// Test avec Ogre
	RobotTetra(btDynamicsWorld* world,Ogre::SceneManager * scene,const btVector3& posInit);

	btVector3 getCenterOfMassPosition();
	
	bool IsNotInArea(const btVector3 &G,const btVector3 &end2);
	// methode pour faire marcher le robot
	static void* marcherRobot(void* demo);
	// Taille mini piston 
	void nanoRobot();
	// Taille maxi piston 
	void maxiRobot();

	// Deplacer le robot
	void translate(const btVector3& to);
};

#endif /* ROBOT_TETRA */