//-----------------------------------------------------------------------------

#ifndef PISTON_H
#define PISTON_H

//-----------------------------------------------------------------------------

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/ConstraintSolver/btSliderConstraint.h"
#include "DemoApplication.h"
#include "Caracteristiques.h"
#include "TetraMotionState.h"
#include "Composant.h"

//-----------------------------------------------------------------------------


/// Piston shows how to create a slider constraint
class Piston: virtual public Composant
{
protected:
	// Attributs:
	btScalar tailleMin;
	btScalar tailleMax;
	btScalar velocite;
	bool estBloque;
	// Forme des deux objets aux extrémitées du piston
	btBoxShape* shapeA;
	btBoxShape* shapeB;
	// Corps des deux objets aux extrémitées du piston
	btRigidBody* bodyA;
	btRigidBody* bodyB;
	// Contraintes liant les deux extrémitées du piston
	btSliderConstraint* contrainte;
	// Contraintes coniques liant une boule a une extremite de piston
	btConeTwistConstraint* coneA;
	btConeTwistConstraint* coneB;

public:
	// Le Constructeur
	Piston::Piston(btDynamicsWorld* ownerWorld,Ogre::SceneNode* nodeOgre, const btVector3& positionOffset,btScalar min,btScalar max,btScalar vitesse);
	// Le Destructeur
	~Piston();
	// les getters & setters
	btSliderConstraint* getContrainte();
	void setContrainte(btSliderConstraint* constraint);
	btRigidBody* getBodyA();
	void setBodyA(btRigidBody* body);
	btRigidBody* getBodyB();
	void setBodyB(btRigidBody* body);
	btBoxShape* getShapeA();
	void setShapeA(btBoxShape* newShape);
	btBoxShape* getShapeB();
	void setShapeB(btBoxShape* newShape);
	btScalar getTailleMin();
	btScalar getTailleMax();
	void setTailleMin(btScalar tailleVoulu);
	void setTailleMax(btScalar tailleVoulu);
	btConeTwistConstraint* getConeA();
	btConeTwistConstraint* getConeB();
	void setConeA(btConeTwistConstraint* contrainteConique);
	void setConeB(btConeTwistConstraint* contrainteConique);

	// methode permettant de connaitre la taille du piston
	btScalar getLength();
	// methode permettant de faire bouger un piston à la taille voulu
	int actionnerPiston(btScalar tailleVoulu);
	// methode permettant de bloquer le piston
	void bloquerPiston();
	// methode permettant de debloquer le piston
	void debloquerPiston();
	// methode permettant connaitre le statut du piston (bloqué ou non)
	bool isBlocked();
};
#endif
