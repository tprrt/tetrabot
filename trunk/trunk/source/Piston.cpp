#include "Piston.h"
#include <stdio.h> //printf debugging
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btIDebugDraw.h"
#include "Noeud.h"
#include "Threads.h"


#ifndef TAILLE_CUBE
#define TAILLE_CUBE 1.F
#endif

Piston::Piston(btDynamicsWorld* ownerWorld,Ogre::SceneNode* nodeOgre, const btVector3& positionOffset,btScalar min,btScalar max,btScalar vitesse)
:tailleMin(min),tailleMax(max),velocite(vitesse),estBloque(false),coneA(0),coneB(0)
{
	// Affecter un IDentificateur au piston
	static int ID = 0;
	this->id = ID;
	ID++;
	this->World = ownerWorld;
	// ajouter les formes des Objets A et B
	shapeA = new btBoxShape(btVector3(TAILLE_CUBE,TAILLE_CUBE,TAILLE_CUBE));
	shapeB = new btBoxShape(btVector3(TAILLE_CUBE,TAILLE_CUBE,TAILLE_CUBE));
		
	// add dynamic rigid body A1
	btTransform trans;
	trans.setIdentity();

	trans.setOrigin(positionOffset);
	bodyA = localCreateRigidBody(POIDS_EXTREMITE_PISTON, trans, shapeA,nodeOgre);
	bodyA->setActivationState(DISABLE_DEACTIVATION);

	// add dynamic rigid body B1
	// mettre bodyB tel que le piston soit a sa longueur maximale sur l'axe X
	trans.setOrigin(positionOffset+btVector3(max,0.F,0.F));
	bodyB = localCreateRigidBody(POIDS_EXTREMITE_PISTON, trans, shapeB,nodeOgre);
	bodyB->setActivationState(DISABLE_DEACTIVATION);

	// create slider constraint between A and B and add it to world
	btTransform frameInA, frameInB;
	frameInA = btTransform::getIdentity();
	frameInB = btTransform::getIdentity();
	frameInA.getBasis().setEulerZYX(0,0,0);
	frameInB.getBasis().setEulerZYX(0,0,0);
	contrainte = new btSliderConstraint(*bodyA, *bodyB, frameInA, frameInB, true);
	contrainte->setLowerLinLimit(min);
	contrainte->setUpperLinLimit(max);
	// Pas d'angle de rotation des bodies
	contrainte->setLowerAngLimit(0.F);
	contrainte->setUpperAngLimit(0.F);
	// Force du piston
	this->contrainte->setMaxLinMotorForce(FORCE_PISTON);
	World->addConstraint(contrainte, true);

	// On desactive les contacts entres les cubes (s'il y a plusieurs pistons par exemple)
	// Les cubes peuvent donc se rentrer dedans
	bodyA->setCollisionFlags(4/*CF_NO_CONTACT_RESPONSE*/);
	bodyB->setCollisionFlags(4); 
}

Piston::Piston(btDynamicsWorld* ownerWorld,const btVector3& positionOffset,btScalar min,btScalar max,btScalar vitesse)
:tailleMin(min),tailleMax(max),velocite(vitesse),estBloque(false),coneA(0),coneB(0)
{
	// Affecter un IDentificateur au piston
	static int ID = 0;
	this->id = ID;
	ID++;
	this->World = ownerWorld;
	// ajouter les formes des Objets A et B
	shapeA = new btBoxShape(btVector3(TAILLE_CUBE,TAILLE_CUBE,TAILLE_CUBE));
	shapeB = new btBoxShape(btVector3(TAILLE_CUBE,TAILLE_CUBE,TAILLE_CUBE));
		
	// add dynamic rigid body A1
	btTransform trans;
	trans.setIdentity();

	trans.setOrigin(positionOffset);
	bodyA = localCreateRigidBody(POIDS_EXTREMITE_PISTON, trans, shapeA);
	bodyA->setActivationState(DISABLE_DEACTIVATION);

	// add dynamic rigid body B1
	// mettre bodyB tel que le piston soit a sa longueur maximale sur l'axe X
	trans.setOrigin(positionOffset+btVector3(max,0.F,0.F));
	bodyB = localCreateRigidBody(POIDS_EXTREMITE_PISTON, trans, shapeB);
	bodyB->setActivationState(DISABLE_DEACTIVATION);

	// create slider constraint between A and B and add it to world
	btTransform frameInA, frameInB;
	frameInA = btTransform::getIdentity();
	frameInB = btTransform::getIdentity();
	frameInA.getBasis().setEulerZYX(0,0,0);
	frameInB.getBasis().setEulerZYX(0,0,0);
	contrainte = new btSliderConstraint(*bodyA, *bodyB, frameInA, frameInB, true);
	contrainte->setLowerLinLimit(min);
	contrainte->setUpperLinLimit(max);
	// Pas d'angle de rotation des bodies
	contrainte->setLowerAngLimit(0.F);
	contrainte->setUpperAngLimit(0.F);
	// Force du piston
	this->contrainte->setMaxLinMotorForce(FORCE_PISTON);
	// on ajoute la contrainte au monde
	World->addConstraint(contrainte, true);

	// On desactive les contacts entres les cubes (s'il y a plusieurs pistons par exemple)
	// Les cubes peuvent donc se rentrer dedans
	bodyA->setCollisionFlags(4/*CF_NO_CONTACT_RESPONSE*/);
	bodyB->setCollisionFlags(4); 
}

Piston::~Piston()
{
	// Détruire la contrainte
	delete this->contrainte;
	// Détruire les shapes
	delete this->shapeA;
	delete this->shapeB;
	// Détruire les objets
	delete this->bodyA;
	delete this->bodyB;
}

btVector3 Piston::getCenterOfMassPosition()
{
	return btVector3((this->bodyA->getCenterOfMassPosition()+ this->bodyB->getCenterOfMassPosition())*btScalar(0.5F));
}

btRigidBody* Piston::getBodyA()
{ 
	return this->bodyA;
}
btRigidBody* Piston::getBodyB()
{ 
	return this->bodyB;
}
void Piston::setBodyA(btRigidBody *body)
{ 
	this->bodyA = body;
}
void Piston::setBodyB(btRigidBody *body)
{ 
	this->bodyB = body;
}
btBoxShape* Piston::getShapeA()
{ 
	return this->shapeA;
}
btBoxShape* Piston::getShapeB()
{ 
	return this->shapeB;
}
void Piston::setShapeA(btBoxShape* newShape)
{
	this->shapeA = newShape;
}
void Piston::setShapeB(btBoxShape* newShape)
{
	this->shapeB = newShape;
}
btSliderConstraint* Piston::getContrainte()
{ 
	return this->contrainte;
}
void Piston::setContrainte(btSliderConstraint *constraint)
{ 
	this->contrainte = constraint;
}
btScalar Piston::getTailleMin()
{ 
	return this->tailleMin;
}
btScalar Piston::getTailleMax()
{ 
	return this->tailleMax;
}
void Piston::setTailleMin(btScalar tailleVoulu)
{ 
	this->tailleMin = tailleVoulu;
	if((this->contrainte->getLowerLinLimit())!=(this->contrainte->getLowerLinLimit()))
		this->contrainte->setLowerLinLimit(tailleVoulu);
}
void Piston::setTailleMax(btScalar tailleVoulu)
{ 
	this->tailleMax = tailleVoulu;
	if((this->contrainte->getUpperLinLimit())!=(this->contrainte->getUpperLinLimit()))
		this->contrainte->setUpperLinLimit(tailleVoulu);
}

btScalar Piston::getLength()
{
	return this->bodyA->getCenterOfMassPosition().distance(this->bodyB->getCenterOfMassPosition());
}


/*
int Piston::lierNoeud(Noeud* boule, char extremitee)
{
	btRigidBody* body;
	btBoxShape* boxShape;
	btConeTwistConstraint* coneC;
	btTransform localA, localB;
	// verifier que extremitee est soit A/a ou B/b
	if(!(extremitee=='A'||extremitee=='a'||extremitee=='B'||extremitee=='b'))
	{
		// Erreur: caractere inconnu
		return -1;
	}
	// On recupere le bout du piston approprie
	// Et on determine si on va placer la boule a droite ou a gauche du piston (sens)
	btScalar sens;
	if(extremitee=='A'||extremitee=='a')
	{
		body = this->bodyA;
		boxShape = this->shapeA;
		sens = btScalar(-1.);

	}
	else
	{
		body = this->bodyB;
		boxShape = this->shapeB;
		sens = btScalar(1.);
		
	}

	
	// Creation de la contrainte conique
	// Pour que la boule soit a l'exterieur du piston (en attendant de trouver comment utiliser la direction d'un objet)
	localA.setIdentity(); localB.setIdentity();
	// Pour que la contrainte conique soit suivant l'axe X.
	localA.getBasis().setEulerZYX(M_PI_2,0,0);
	localB.getBasis().setEulerZYX(M_PI_2,0,0);
	// le sommet du cone definit par la contrainte conique doit etre a la base du carre
	// representant une extremite de piston
	localA.setOrigin(btVector3(sens*(boxShape->getHalfExtentsWithMargin().getX()), btScalar(0.), btScalar(0.)));
	// le point definit par localA doit etre distant du rayon de la boule pour que la boule et l'extremite
	// du piston se touchent a peine.
	localB.setOrigin(btVector3(-sens*(boule->getShapeNoeud()->getRadius()),0,0));
	coneC = new btConeTwistConstraint(*body,*boule->getBody(), localA, localB);
	// Definition de cone de la contrainte:
	// deux premiers param: definition du cercle (base du cone)
	// troisieme param: rotation de l'extremite du piston suivant l'axe X (cf localA et localB)
	// quatrieme param: "soft limit == hard limit" -> contrainte rigide?
	coneC->setLimit(M_PI_4,M_PI_4,0.01F,1.F);
	this->World->addConstraint(coneC, false); 
	return 0;
} */

void Piston::bloquerPiston()
{
	if(!this->estBloque)
	{
		printf("Piston [%d]: blocage en cours...\n",this->id);
		this->contrainte->setLowerLinLimit(this->getLength());
		this->contrainte->setUpperLinLimit(this->getLength());
		this->estBloque = true;
	}
}
void Piston::debloquerPiston()
{
	if(this->getEstBloque())
	{
		printf("Piston [%d]: deblocage en cours...\n",this->id);
		// Pour débloquer le Piston, il suffit de lui attribuer les memes caracteristiques que contrainte
		this->contrainte->setLowerLinLimit(this->tailleMin);
		this->contrainte->setUpperLinLimit(this->tailleMax);
		this->estBloque = false;
	}
}

bool Piston::getEstBloque()
{
	// (this->contrainte->getLowerLinLimit() == this->contrainte->getUpperLinLimit());
	return this->estBloque;
}

int Piston::actionnerPiston(btScalar tailleVoulu)
{
	btScalar sens,ecart;
	bool arreterPiston;
	int timeOut = 40*ATTENTE_PISTON;// (40*10)*25 ms <=> 10 seconde
	
	// Restraindre un peu les limites d'allongement du piston
	contrainte->setLowerLinLimit(btScalar(this->tailleMin - 0.1));
	contrainte->setUpperLinLimit(btScalar(this->tailleMax - 0.1));
	// Moteur actif: oui
	this->contrainte->setPoweredLinMotor(true);
	// Marge d'erreur de 2% de la longueur de mobilite du piston
	btScalar margeErreur = btScalar(2.F*(this->tailleMax-this->tailleMin)/100.F);
	if(tailleVoulu > this->getLength()-margeErreur)
	{
		sens = btScalar(1.F);
	}
	else
	{
		sens = btScalar(-1.F);
	}
	this->debloquerPiston();
	// velocité du piston
	this->contrainte->setTargetLinMotorVelocity(this->velocite*sens);
	do
	{
		timeOut--;
		ecart = btScalar(tailleVoulu - this->getLength());
		if(ecart<0) ecart = -ecart;
		arreterPiston = (ecart-margeErreur<=0)
			||(sens==1&& (this->getLength()>=tailleVoulu)) // On a depassé la taille voulu pour sens à 1
			||(sens==-1 && (this->getLength()<=tailleVoulu)); // On a depassé la taille voulu pour sens à -1
		msleep(25);

	}
	while((timeOut>0)&&(!arreterPiston));
	// Afficher Reussite ou echec
	if(timeOut <= 0 )
	{
		printf("Piston [%d]: ---- Echec! ---- \n",this->id);
	}
	else
	{
		printf("Piston [%d]: ---- Success! ---- \n",this->id);
	}
	// Arreter le moteur
	this->contrainte->setPoweredLinMotor(false);

	// Bloquer le piston
	this->bloquerPiston();

	return 0;
}

btConeTwistConstraint* Piston::getConeA()
{ 
	return this->coneA;
}
btConeTwistConstraint* Piston::getConeB()
{ 
	return this->coneB;
}
void Piston::setConeA(btConeTwistConstraint *contrainteConique)
{ 
	this->coneA = contrainteConique;
}
void Piston::setConeB(btConeTwistConstraint *contrainteConique)
{ 
	this->coneB = contrainteConique;
}
