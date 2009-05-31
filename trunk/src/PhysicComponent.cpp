#include "PhysicComponent.h"

int PhysicComponent::getID() {
	return this->id;
}

btDynamicsWorld *PhysicComponent::getWorld() {
	return this->World;
}

void PhysicComponent::setWorld(btDynamicsWorld* newWorld) {
	this->World = newWorld;
}

// Création d'un corps pour Ogre
btRigidBody* PhysicComponent::localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre) {

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
btRigidBody* PhysicComponent::localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape) {

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

