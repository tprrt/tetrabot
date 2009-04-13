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

	class btBroadphaseInterface*	m_overlappingPairCache;

	class btCollisionDispatcher*	m_dispatcher;

	class btConstraintSolver*	m_constraintSolver;

	class btDefaultCollisionConfiguration* m_collisionConfiguration;
private:
	// Le constructeur 
	// On controle qu'il n'y ai qu'une seule instance du monde
	// en rendant inaccessible le constructeur. 
	WorldPhysic();
public:
	// Initialisation du monde Physique (une seule instance possible)
	btDiscreteDynamicsWorld* initPhysic(btVector3& worldMin,btVector3& worldMax,btVector3& gravite);
	// Initialisation du Sol
	void initGround();
	// Affecter une Gravité
	void setGravite(btVector3& newGravite);
	btVector3 getGravite();


};


#endif