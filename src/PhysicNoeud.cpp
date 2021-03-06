//  @ Project : Tetrabot
//  @ File Name : PhysicNoeud.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "PhysicNoeud.h"

//-----------------------------------------------------------------------------

//Constructeur de la classe PhysicNoeud pour Ogre
PhysicNoeud::PhysicNoeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse): PhysicVertex(ownerWorld),PhysicComponent(ownerWorld)
{
	static int ID=0;
	this->id = ID;
	ID++;

	//this->World = ownerWorld;

	this->shapeNoeud = forme;
	
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(offset);

	this->bodyNoeud = localCreateRigidBody(masse, trans, this->shapeNoeud,nodeOgre);
	this->bodyNoeud->setActivationState(DISABLE_DEACTIVATION);
	// Friction boule/sol
	this->bodyNoeud->setFriction(RUBDOWN);
}
//Constructeur de la classe PhysicNoeud pour Bullet
PhysicNoeud::PhysicNoeud(btDynamicsWorld *ownerWorld,btConvexInternalShape* forme,const btVector3 & offset, btScalar masse):PhysicVertex(ownerWorld),PhysicComponent(ownerWorld)
{
	static int ID=0;
	this->id = ID;
	ID++;

	this->World = ownerWorld;

	this->shapeNoeud = forme;
	
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(offset);

	this->bodyNoeud = localCreateRigidBody(masse, trans, this->shapeNoeud);
	this->bodyNoeud->setActivationState(DISABLE_DEACTIVATION);
	// Friction boule/sol
	this->bodyNoeud->setFriction(RUBDOWN);
}
//Destructeur de la classe PhysicNoeud
PhysicNoeud::~PhysicNoeud()
{
	delete this->shapeNoeud;
	delete this->bodyNoeud;
}
// Methode pour obtenir le centre de masse
btVector3 PhysicNoeud::getCenterOfMassPosition()
{
	return this->bodyNoeud->getCenterOfMassPosition();
}

// Retourne le Body de l objet
btRigidBody* PhysicNoeud::getBody()
{
	return this->bodyNoeud;
}
//Parametre le Body de l objet
void PhysicNoeud::setBody(btRigidBody *body)
{
	this->bodyNoeud = body;
}
// Retourne le ShapeNoeud de l objet
btConvexInternalShape* PhysicNoeud::getShapeNoeud()
{
	return this->shapeNoeud;
}
//Parametre le ShapeNoeud de l objet
void PhysicNoeud::setShapeNoeud(btConvexInternalShape* shape)
{
	this->shapeNoeud = shape;
}


int PhysicNoeud::linkEdge(PhysicEdge *edge, char extremitee, btScalar rotationY, btScalar rotationZ)
{
	btRigidBody* bodyBox;
	btBoxShape* boxShape;
	btConeTwistConstraint* coneC;
	btTransform localA, localB;
	btScalar sens;
	btScalar sensANGLE;
	PhysicPiston* piston = (PhysicPiston*) edge;

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
	localA.getBasis().setEulerZYX(btScalar(0.),btScalar(0.),sensANGLE);
	
	// en rapport avec l'orientation de la boule
	localB.getBasis().setEulerZYX(btScalar(0.),rotationY,rotationZ);
	
	// Le sommet du cone definit par la contrainte conique doit etre a la base du carre
	// representant une extremite de piston
	localA.setOrigin(btVector3(sens*(boxShape->getHalfExtentsWithMargin().getX()), btScalar(0.), btScalar(0.)));

	/*
			Le point definit par localA doit etre distant du rayon de la boule pour que la boule et l'extremite
		du piston se touchent a peine. 
		Pour ce faire, on prends le vecteur directeur de la contrainte (axe X relatif de la boule)
		et on le multiplie par le Rayon de la boule
	*/
	btScalar Rayon = this->shapeNoeud->getImplicitShapeDimensions().getX();
	localB.setOrigin(localB.getBasis().getColumn(0)*Rayon);
	// Creation de la contrainte conique
	coneC = new btConeTwistConstraint(*bodyBox,*(this->bodyNoeud), localA, localB);
	// Definition de cone de la contrainte:
	// deux premiers param: definition du cercle (base du cone)
	// troisieme param: rotation de l'extremite du piston suivant l'axe X (cf localA et localB)
	// quatrieme param: "soft limit == hard limit" -> contrainte rigide?
	coneC->setLimit(CONE_ANGLE,CONE_ANGLE,btScalar(0.));
	coneC->setAngularOnly(true);
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

// Methode pour translater l objet
void PhysicNoeud::translate(const btVector3& to)
{
	this->bodyNoeud->translate(to);
}
