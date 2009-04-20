//-----------------------------------------------------------------------------

#ifndef GL_PISTON_H
#define GL_PISTON_H

//-----------------------------------------------------------------------------

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/ConstraintSolver/btSliderConstraint.h"
#include "DemoApplication.h"

#include "Threads.h"
#include "WorldPhysic.h"
#include "Robot_Tetra.h"
#include "Caracteristiques.h"
#include "ControleurRobot.h"
#include "Sinusoide.h"
//-----------------------------------------------------------------------------


/// SliderConstraintDemo shows how to create a slider constraint
class GL_Piston : public DemoApplication
{
	//keep track of variables to delete memory at the end
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	class btBroadphaseInterface*	m_overlappingPairCache;

	class btCollisionDispatcher*	m_dispatcher;

	class btConstraintSolver*	m_constraintSolver;

	class btDefaultCollisionConfiguration* m_collisionConfiguration;
public:	
	ActionPiston *action[6];
	WorldPhysic * world;
	Robot_Tetra * robot;
	ControleurRobot* controleur;

public:
	// Le constructeur
	GL_Piston();
	// Le destructeur
	virtual ~GL_Piston();
	// initialiser la physique
	void	initPhysics();

	void	initModel();
	// Afficher les lignes / lignes de contrainte
	void	drawSliders();
	void	drawSliderConstraint(btSliderConstraint* constraint);


	virtual void clientMoveAndDisplay();

	virtual void displayCallback();

	static DemoApplication* Create()
	{
		GL_Piston* demo = new GL_Piston();
		demo->myinit();
		demo->initPhysics();
		return demo;
	}	
	void specialKeyboard(int key, int x, int y);
	void renderme();
	
};

#endif

