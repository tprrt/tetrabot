#ifndef COMPOSANT_H
#define COMPOSANT_H

#include "btBulletDynamicsCommon.h"

#include "TetraMotionState.h"

class Composant {

protected:
	int id;

	btDynamicsWorld *World;
public:

	int getID();

	btDynamicsWorld* getWorld();

	void setWorld(btDynamicsWorld* newWorld);
	
	// Création d'un corps pour Ogre
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre);

	// Création d'un corps pour GL
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);

	// methode a implementer: retourne le centre de gravite
	virtual btVector3 getCenterOfMassPosition() = 0;
};

#endif /* COMPOSANT_H */
