//  @ Project : Tetrabot
//  @ File Name : PhysicComponent.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "PhysicComponent.h"

// Retourne l identifieur de l objet
int PhysicComponent::getID() {
	return this->id;
}

// Retourne le monde
btDynamicsWorld *PhysicComponent::getWorld() {
	return this->World;
}

//Parametre le monde
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

