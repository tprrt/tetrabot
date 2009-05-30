//-----------------------------------------------------------------------------

#ifndef NOEUD_H
#define NOEUD_H

#include "LinearMath/btIDebugDraw.h"
#include "btBulletDynamicsCommon.h"
#include "Caracteristiques.h"
#include "Piston.h"
#include "Composant.h"
#include "BulletCollision/CollisionShapes/btConvexInternalShape.h"

/// Piston shows how to create a slider constraint
class Noeud: virtual public Composant
{
protected:
	btConvexInternalShape* shapeNoeud;

	btRigidBody* bodyNoeud;

public:
	Noeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse);

	Noeud(btDynamicsWorld *ownerWorld,btConvexInternalShape* forme,const btVector3 & offset, btScalar masse);

	virtual ~Noeud();

	btVector3 getCenterOfMassPosition();


	btRigidBody* getBody();

	void setBody(btRigidBody* body);

	btConvexInternalShape* getShapeNoeud();

	void setShapeNoeud(btConvexInternalShape* shape);

	int lierPiston(Piston* piston, char extremitee, btScalar rotationY, btScalar rotationZ);
};
#endif
