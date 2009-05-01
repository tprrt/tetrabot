//-----------------------------------------------------------------------------

#ifndef NOEUD_H
#define NOEUD_H

//-----------------------------------------------------------------------------

#include "btBulletDynamicsCommon.h"
#include "Caracteristiques.h"
#include "Piston.h"
#include "Composant.h"
#include "BulletCollision\CollisionShapes\btConvexInternalShape.h"

#include "TetraMotionState.h"

//-----------------------------------------------------------------------------



/// Piston shows how to create a slider constraint
class Noeud: virtual public Composant
{
protected:
	// Attributs:
	// Attributs de la Noeud
	btConvexInternalShape* shapeNoeud;
	btRigidBody* bodyNoeud;
public:
	// Les Constructeurs
	// Constructeur pour Ogre
	Noeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse);
	// Constructeur pour GL
	Noeud(btDynamicsWorld *ownerWorld,btConvexInternalShape* forme,const btVector3 & offset, btScalar masse);
	// Le Destructeur
	~Noeud();
	// methode retournant le centre de gravite
	btVector3 getCenterOfMassPosition();
	// les getters & setters
	btRigidBody* getBody();
	void setBody(btRigidBody* body);
	btConvexInternalShape* getShapeNoeud();
	void setShapeNoeud(btConvexInternalShape* shape);
	// Methode liant une boule à un piston
	int lierPiston(Piston* piston,char extremitee,btScalar rotationY,btScalar rotationZ);
};
#endif