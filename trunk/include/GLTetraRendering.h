//  @ Project : Tetrabot
//  @ File Name : GLTetraRendering.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

//-----------------------------------------------------------------------------

#ifndef GLTETRARENDERING_H
#define GLTETRARENDERING_H

//-----------------------------------------------------------------------------

#include <cstdio> //printf debugging

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/ConstraintSolver/btSliderConstraint.h"
#include "Application.h"
#include "Threads.h"
#include "PhysicWorld.h"
#include "WorldInfo.h"
#include "RobotTetra.h"
#include "characteristics.h"
#include "ControleurRobot.h"
#include "Sinusoide.h"
#include "PhysicPiston.h"
#include "PhysicNoeud.h"
#include "Action.h"
#include "LinearMath/btIDebugDraw.h"
#include "GLDebugDrawer.h"
#include "BMF_Api.h"
#include "GL_ShapeDrawer.h"
#include "GlutStuff.h"
//Pour TEST
#include "AlgoGenTetra.h"
//-----------------------------------------------------------------------------


/// SliderConstraintDemo shows how to create a slider constraint
class GLTetraRendering : public Application
{
public:
	//keep track of variables to delete memory at the end
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	class btBroadphaseInterface*	m_overlappingPairCache;

	class btCollisionDispatcher*	m_dispatcher;

	class btConstraintSolver*	m_constraintSolver;

	class btDefaultCollisionConfiguration* m_collisionConfiguration;
	
	// action : tableau des actions des pistons
	ActionPiston *action[6];

	PhysicWorld * world;
	// robot : robot qui est dans le monde bullet
	RobotTetra * robot;
	
	// bodyCube : indicateur de la position cible
	btRigidBody* bodyCube;
	
	// bodyPave : indicateur de piston
	btRigidBody* bodyPave;

public:
	// Constructeur de la classe GLTetraRendering pour initialiser les Actions des pistons d un robot 
	GLTetraRendering();
	// Destructeur de la classe GLTetraRendering
	virtual ~GLTetraRendering();
	// Methode pour initialiser le monde bullet et pour creer un robot
	void	initPhysics();

	void	initModel();

	void	drawSliders();

	void	drawSliderConstraint(btSliderConstraint* constraint);

	virtual void clientMoveAndDisplay();
	// Methode pour dessiner les contraintes lienaires des pistons du robot
	virtual void displayCallback();

	static Application* Create()
	{
		GLTetraRendering* demo = new GLTetraRendering();
		demo->myinit();
		demo->initPhysics();
		return demo;
	}
	// Methode pour interagir avec bullet ( touches clavier Fn )
	void specialKeyboard(int key, int x, int y);
	// Methode pour interagir avec bullet ( touches clavier )
	void keyboardCallback(unsigned char key, int x, int y);

	//Methode pour configuer l affichage de ecran
	void renderme();
};

#endif /* GLTETRARENDERING_H */

