#ifndef COMPOSANT_H
#define COMPOSANT_H
#include <Ogre.h>
#include "TetraMotionState.h"

class Composant
{
	// Attributs
protected:
	int id;
	btDynamicsWorld* World;
	// Les methodes
public:
	int getID()
	{
		return this->id;
	}

	btDynamicsWorld* getWorld()
	{
		return this->World;
	}
	void setWorld(btDynamicsWorld* newWorld)
	{
		this->World = newWorld;
	}
	
	// Création d'un corps pour Ogre
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre)
	{
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			shape->calculateLocalInertia(mass,localInertia);

		btMotionState* myMotionState = new TetraMotionState(startTransform,nodeOgre);
			
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		World->addRigidBody(body);
		return body;
	}

	// Création d'un corps pour GL
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
	{
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			shape->calculateLocalInertia(mass,localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
			
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		World->addRigidBody(body);
		return body;
	}
	// methode a implementer: retourne le centre de gravite
	virtual btVector3 getCenterOfMassPosition()=0;
};

#endif
