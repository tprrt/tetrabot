#ifndef PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H

#include "btBulletDynamicsCommon.h"

#include "TetraMotionState.h"

class PhysicComponent {

protected:
	int id;

	btDynamicsWorld *World;

public:
	PhysicComponent(btDynamicsWorld *world):World(world)
	{
	};

	virtual ~PhysicComponent()
	{
	};

	int getID();

	btDynamicsWorld* getWorld();

	void setWorld(btDynamicsWorld* newWorld);
	
	// Création d'un corps pour Ogre
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre);

	// Création d'un corps pour GL
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);

	// methode a implementer: retourne le centre de gravite
	virtual btVector3 getCenterOfMassPosition() = 0;

	// methode a implanter: translation du composant
	virtual void translate(const btVector3& to) = 0;
};

#endif /* PHYSIC_COMPONENT_H */
