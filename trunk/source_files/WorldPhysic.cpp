#include "WorldPhysic.h"

btDiscreteDynamicsWorld* WorldPhysic::initPhysic(btVector3& worldMin,btVector3& worldMax,btVector3& gravite)
{
	static int nbInstance = 0;
	if(nbInstance==0)
	{
		m_collisionConfiguration = new btDefaultCollisionConfiguration();
		m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	
		m_overlappingPairCache = new btAxisSweep3(worldMin,worldMax);

	#if SLIDER_DEMO_USE_ODE_SOLVER
		m_constraintSolver = new btOdeQuickstepConstraintSolver();
	#else
		m_constraintSolver = new btSequentialImpulseConstraintSolver();
	#endif
		m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_overlappingPairCache,m_constraintSolver,m_collisionConfiguration);
		//	wp->getSolverInfo().m_numIterations = 20; // default is 10
		this->m_gravite = gravite;
		m_dynamicsWorld->setGravity(gravite);
		
		nbInstance++;
	}
	return m_dynamicsWorld;
}

void WorldPhysic::initGround()
{
	// Création d'un sol
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(1.F),btScalar(50.)));
	m_collisionShapes.push_back(groundShape);
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-6,0));
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);	
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0,myMotionState,groundShape,btVector3(0,0,0));
	m_ground = new btRigidBody(rbInfo);
	this->m_dynamicsWorld->addRigidBody(m_ground);
}

void WorldPhysic::setGravite(btVector3& newGravite)
{
	this->m_dynamicsWorld->setGravity(newGravite);
	this->m_gravite = newGravite;
}

btVector3 WorldPhysic::getGravite(){ return this->m_gravite;}