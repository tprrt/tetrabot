//  @ Project : Tetrabot
//  @ File Name : PhysicComponent.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H

#include "btBulletDynamicsCommon.h"

#include "TetraMotionState.h"

class PhysicComponent {

protected:
	// id : identifieur de l objet
	int id;
	// World : le monde 
	btDynamicsWorld *World;

public:
	// Constructeur de la classe PhysicComponent
	PhysicComponent(btDynamicsWorld *world):World(world)
	{
	};
	// Destructeur de la classe PhysicComponent
	virtual ~PhysicComponent()
	{
	};
	// Retourne l identifieur de l objet
	int getID();
	// Retourne le monde 
	btDynamicsWorld* getWorld();
	// Parametre le monde
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
