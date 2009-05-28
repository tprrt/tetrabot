//-----------------------------------------------------------------------------

#ifndef GL_PISTON_H
#define GL_PISTON_H

//-----------------------------------------------------------------------------

#include <cstdio> //printf debugging

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/ConstraintSolver/btSliderConstraint.h"
#include "Application.h"
#include "Threads.h"
#include "WorldPhysic.h"
#include "RobotTetra.h"
#include "Caracteristiques.h"
#include "ControleurRobot.h"
#include "Sinusoide.h"
#include "Piston.h"
#include "Noeud.h"
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
class GL_Piston : public Application
{
public:
	//keep track of variables to delete memory at the end
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	class btBroadphaseInterface*	m_overlappingPairCache;

	class btCollisionDispatcher*	m_dispatcher;

	class btConstraintSolver*	m_constraintSolver;

	class btDefaultCollisionConfiguration* m_collisionConfiguration;
	
	ActionPiston *action[6];

	WorldPhysic * world;

	RobotTetra * robot;

	ControleurRobot* controleur;

	btRigidBody* bodyCube;

	btRigidBody* bodyPave;

public:

	GL_Piston();

	virtual ~GL_Piston();

	void	initPhysics();

	void	initModel();

	void	drawSliders();

	void	drawSliderConstraint(btSliderConstraint* constraint);

	virtual void clientMoveAndDisplay();

	virtual void displayCallback();

	static Application* Create()
	{
		GL_Piston* demo = new GL_Piston();
		demo->myinit();
		demo->initPhysics();
		return demo;
	}	
	void specialKeyboard(int key, int x, int y);
	void keyboardCallback(unsigned char key, int x, int y);
	bool IsNotInArea(const btVector3 &G,const btVector3 &end2);
	void renderme();

	// methode pour faire marcher le robot
	static void* marcherRobot(void* demo);
};

#endif

