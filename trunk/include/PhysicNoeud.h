//  @ Project : Tetrabot
//  @ File Name : PhysicNoeud.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

//-----------------------------------------------------------------------------

#ifndef PHYSICNOEUD_H
#define PHYSICNOEUD_H

#include <cstdio>
#include "LinearMath/btIDebugDraw.h"
#include "btBulletDynamicsCommon.h"
#include "characteristics.h"
#include "PhysicPiston.h"
#include "PhysicVertex.h"
#include "BulletCollision/CollisionShapes/btConvexInternalShape.h"

/// Piston shows how to create a slider constraint
class PhysicNoeud: public PhysicVertex
{
protected:

	btConvexInternalShape* shapeNoeud;

	btRigidBody* bodyNoeud;

public:
	//Constructeur de la classe PhysicNoeud pour Ogre
	PhysicNoeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse);

	//Constructeur de la classe PhysicNoeud pour Bullet
	PhysicNoeud(btDynamicsWorld *ownerWorld,btConvexInternalShape* forme,const btVector3 & offset, btScalar masse);
	
	//Destructeur de la classe
	~PhysicNoeud();

	// Methode pour obtenir le centre de masse
	btVector3 getCenterOfMassPosition();

	// Retourne le Body de l objet
	btRigidBody* getBody();

	//Parametre le Body de l objet
	void setBody(btRigidBody* body);

	// Retourne le ShapeNoeud de l objet
	btConvexInternalShape* getShapeNoeud();

	//Parametre le ShapeNoeud de l objet
	void setShapeNoeud(btConvexInternalShape* shape);

	int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ);

	// Methode pour translater l objet
	void translate(const btVector3& to);
};
#endif
