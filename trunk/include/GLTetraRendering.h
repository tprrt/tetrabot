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
	
	ActionPiston *action[6];

	PhysicWorld * world;

	RobotTetra * robot;

	ControleurRobot* controleur;

	btRigidBody* bodyCube;

	btRigidBody* bodyPave;

public:

	GLTetraRendering();

	virtual ~GLTetraRendering();

	void	initPhysics();

	void	initModel();

	void	drawSliders();

	void	drawSliderConstraint(btSliderConstraint* constraint);

	virtual void clientMoveAndDisplay();

	virtual void displayCallback();

	static Application* Create()
	{
		GLTetraRendering* demo = new GLTetraRendering();
		demo->myinit();
		demo->initPhysics();
		return demo;
	}

	void specialKeyboard(int key, int x, int y);

	void keyboardCallback(unsigned char key, int x, int y);

	bool IsNotInArea(const btVector3 &G,const btVector3 &end2);

	void renderme();

	// methode pour faire marcher le robot
	//static void* marcherRobot(void* demo);
};

#endif /* GLTETRARENDERING_H */

