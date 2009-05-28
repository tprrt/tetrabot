#include "Composant.h"

int Composant::getID() {
	return this->id;
}

btDynamicsWorld *Composant::getWorld() {
	return this->World;
}

void Composant::setWorld(btDynamicsWorld* newWorld) {
	this->World = newWorld;
}

// Création d'un corps pour Ogre
btRigidBody* Composant::localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre) {

	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0,0,0);

	if (isDynamic) {
		shape->calculateLocalInertia(mass,localInertia);
	}
	btMotionState* myMotionState = new TetraMotionState(startTransform, nodeOgre);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	World->addRigidBody(body);
	return body;
}

	// Création d'un corps pour GL
btRigidBody* Composant::localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape) {

	bool isDynamic = (mass != 0.f);
	btVector3 localInertia(0,0,0);

	if (isDynamic) {
		shape->calculateLocalInertia(mass,localInertia);
	}

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);

	World->addRigidBody(body);

	return body;
}
