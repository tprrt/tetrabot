#ifndef ROBOTTETRA
#define ROBOTTETRA


#include "PhysicRobot.h"
#include "PhysicNoeud.h"
#include "PhysicPiston.h"
/*
#include "Action.h"
#include "Caracteristiques.h"
#include "PhysicWorld.h"
*/
#include "ActionPiston.h"
// JAZZ MODIF :  1 JUIN 2009 : 2h42
#include "Threads.h"
// JAZZ MODIF :  1 JUIN 2009 : 3h31
#include "AlgoGenTetra.h"

class RobotTetra: public PhysicRobot
{
protected:

	ActionPiston*	action[6];
	ActionPiston*	actionFuture[6];

public:	
	btRigidBody* bodyCube;
	btVector3* end;
	btVector3* endFuture;
	
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
	// JAZZ MODIF :  1 JUIN 2009 : 2h42
	// Lance des Threads
	//void StartThread(btScalar a, btScalar b, btScalar c);
	void StartThread(btVector3 ending);
	
	// JAZZ MODIF : 1 JUIN 2009 : 11h52
	void Deplacement(unsigned char key);
	
	//JAZZ MODIF : 7 JUIN 2009 : 12H37
	// Permet de verifier s'il y a des actions prevues et de les commencer s'il n'y a pas de d'action en cours
	// True : on remplit le tableau Action
	// False : on remplit le tableau ActionFuture
	bool gestionAction(void);
	
	// Methode pour purger les threads
	void purgeThread(void);
};

#endif /* ROBOT_TETRA */
