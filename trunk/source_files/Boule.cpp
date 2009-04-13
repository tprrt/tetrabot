#include "Boule.h"
#include <stdio.h> //printf debugging
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btIDebugDraw.h"

//-----------------------------------------------------------------------------



Boule::Boule(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,const btVector3 & offset, btScalar rayon,btScalar masse)
{
	static int ID=0;
	this->id = ID;
	ID++;

	this->World = ownerWorld;

	this->shapeBoule = new btSphereShape(rayon);
	
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(offset);

	this->bodyBoule = localCreateRigidBody(masse, trans, this->shapeBoule,nodeOgre);
	this->bodyBoule->setActivationState(DISABLE_DEACTIVATION);
	// Friction boule/sol
	this->bodyBoule->setFriction(FRICTION);
}

Boule::~Boule()
{
	delete this->shapeBoule;
	delete this->bodyBoule;
}




btRigidBody* Boule::getBody()
{
	return this->bodyBoule;
}
void Boule::setBody(btRigidBody *body)
{
	this->bodyBoule = body;
}

btSphereShape* Boule::getShapeBoule()
{
	return this->shapeBoule;
}
void Boule::setShapeBoule(btSphereShape *shape)
{
	this->shapeBoule = shape;
}


int Boule::lierPiston(Piston *piston, char extremitee, btScalar rotationY, btScalar rotationZ)
{
	btRigidBody* bodyBox;
	btBoxShape* boxShape;
	btConeTwistConstraint* coneC;
	btTransform localA, localB;
	btScalar sens;
	btScalar sensANGLE;

	// verifier que extremitee est soit A/a ou B/b
	if(!(extremitee=='A'||extremitee=='a'||extremitee=='B'||extremitee=='b'))
	{
		// Erreur: caractere inconnu
		return -1;
	}
	// On recupere le bout du piston approprie
	// Et on determine si on va placer la boule a droite ou a gauche du piston (sens et sensANGLE)
	if(extremitee=='A'||extremitee=='a')
	{
		bodyBox = piston->getBodyA();
		boxShape = piston->getShapeA();
		sens = btScalar(-1.);
		sensANGLE = btScalar(0.);

	}
	else
	{
		bodyBox = piston->getBodyB();
		boxShape = piston->getShapeB();
		sens = btScalar(1.);
		sensANGLE = btScalar(M_PI);
		
	}

	localA.setIdentity(); 
	localB.setIdentity();
	
	// En rapport avec l'orientation de l'extremitee du piston
	localA.getBasis().setEulerZYX(0,0,sensANGLE);
	
	// en rapport avec l'orientation de la boule
	localB.getBasis().setEulerZYX(0,rotationY,rotationZ);
	
	// Le sommet du cone definit par la contrainte conique doit etre a la base du carre
	// representant une extremite de piston
	localA.setOrigin(btVector3(sens*(boxShape->getHalfExtentsWithMargin().getX()), btScalar(0.), btScalar(0.)));

	/*
			Le point definit par localA doit etre distant du rayon de la boule pour que la boule et l'extremite
		du piston se touchent a peine. 
		Pour ce faire, on prends le vecteur directeur de la contrainte (axe X relatif de la boule)
		et on le multiplie par le Rayon de la boule
	*/
	btScalar Rayon = this->shapeBoule->getRadius();
	localB.setOrigin(localB.getBasis().getColumn(0)*Rayon);
	// Creation de la contrainte conique
	coneC = new btConeTwistConstraint(*bodyBox,*this->bodyBoule, localA, localB);
	// Definition de cone de la contrainte:
	// deux premiers param: definition du cercle (base du cone)
	// troisieme param: rotation de l'extremite du piston suivant l'axe X (cf localA et localB)
	// quatrieme param: "soft limit == hard limit" -> contrainte rigide?
	coneC->setLimit(ANGLES_CONE,ANGLES_CONE,btScalar(0.),btScalar(1.));

	// On applique la contrainte au monde
	this->World->addConstraint(coneC, false);
	// On sauvegarde la contrainte conique dans la classe piston
	if(extremitee=='A'||extremitee=='a'){
		piston->setConeA(coneC);
	}
	else{
		piston->setConeB(coneC);
	}

	// echelle du cone graphique pour le debug
	coneC->setDbgDrawSize(btScalar(5.F));
	return 0;
}