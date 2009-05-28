/*
	Définition de la classe abstraite Robot.
Cette classe contiendra tout les éléments du robot ainsi que les actions associes au robot.
Comme les robots peuvent etre differents, les actions sont des methodes VIRTUELLES PURES
*/
#ifndef ROBOT_H
#define ROBOT_H

#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "Composant.h"
#include "Piston.h"
#include "Noeud.h"

class Robot{

public:
	btAlignedObjectArray<Noeud *> Sommets;

	btAlignedObjectArray<Piston *> Arcs;

	btScalar incremente;

	int id;

public:
	Robot();

	virtual ~Robot();

	int getID();
 
	btAlignedObjectArray<Noeud *> getSommets();

	Noeud *getSommet(int i);

	btAlignedObjectArray<Piston *> getArcs();

	Piston *getArc(int i);

	btScalar getIncremente();

	void translate(const btVector3& to);

	bool IsNotInArea(const btVector3 &G,const btVector3 &end2);

	virtual btVector3 getCenterOfMassPosition() = 0;

	virtual void move(int x, int y, int z) = 0;

};

#endif /* Robot */
