//-----------------------------------------------------------------------------

#ifndef BOULE_H
#define BOULE_H

//-----------------------------------------------------------------------------

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/ConstraintSolver/btSliderConstraint.h"
#include "DemoApplication.h"
#include "Caracteristiques.h"
#include "Piston.h"
#include "Composant.h"

#include "TetraMotionState.h"

//-----------------------------------------------------------------------------



/// Piston shows how to create a slider constraint
class Boule: virtual public Composant
{
protected:
	// Attributs:
	// Attributs de la Boule
	btSphereShape* shapeBoule;
	btRigidBody* bodyBoule;
public:
	// Le Constructeur
	Boule(btDynamicsWorld*,Ogre::SceneNode * ,const btVector3&,btScalar,btScalar);
	// Le Destructeur
	~Boule();
	// les getters & setters
	btRigidBody* getBody();
	void setBody(btRigidBody* body);
	btSphereShape* getShapeBoule();
	void setShapeBoule(btSphereShape* shape);
	// Methode liant une boule à un piston
	int lierPiston(Piston* piston,char extremitee,btScalar rotationY,btScalar rotationZ);
};
#endif