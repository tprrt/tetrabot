#ifndef WORLD_PHYSIC_H
#define WORLD_PHYSIC_H

#include "btBulletDynamicsCommon.h"

class WorldPhysic
{
public:
	// Attributs
	btDiscreteDynamicsWorld * m_dynamicsWorld;
	btVector3 m_gravite;
	btRigidBody* m_ground;
	
	//keep track of variables to delete memory at the end
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	btAlignedObjectArray<btTriangleMesh*> m_trimeshes;

	class btBroadphaseInterface*	m_overlappingPairCache;

	class btCollisionDispatcher*	m_dispatcher;

	class btConstraintSolver*	m_constraintSolver;

	class btDefaultCollisionConfiguration* m_collisionConfiguration;
public:
	// Le constructeur 
	WorldPhysic(const btVector3& worldMin,const btVector3& worldMax,const btVector3& gravite);
public:
	// Initialisation du Sol
	void initGround(const char* filename);
	// Affecter une Gravité
	void setGravite(const btVector3& newGravite);
	btVector3 getGravite();


};


#endif