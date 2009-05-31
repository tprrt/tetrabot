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
	PhysicNoeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse);


	PhysicNoeud(btDynamicsWorld *ownerWorld,btConvexInternalShape* forme,const btVector3 & offset, btScalar masse);

	~PhysicNoeud();

	btVector3 getCenterOfMassPosition();


	btRigidBody* getBody();

	void setBody(btRigidBody* body);

	btConvexInternalShape* getShapeNoeud();

	void setShapeNoeud(btConvexInternalShape* shape);

	int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ);

	void translate(const btVector3& to);
};
#endif
