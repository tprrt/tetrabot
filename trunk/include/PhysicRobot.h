/**
 * \file ActionPiston.h
 * \brief Définition de la classe abstraite Robot.
 *Cette classe contiendra tout les éléments du robot ainsi que les actions associes au robot.
 *Comme les robots peuvent etre differents, les actions sont des methodes VIRTUELLES PURES
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef PHYSICROBOT_H
#define PHYSICROBOT_H

#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicComponent.h"
#include "PhysicEdge.h"
#include "PhysicVertex.h"

/**
 * \class PhysicRobot
 * \brief composition du robot 
 */
class PhysicRobot{

public:
	btAlignedObjectArray<PhysicVertex *> Sommets;

	btAlignedObjectArray<PhysicEdge *> Arcs;

	/*btScalar incremente;*/

	int id;

public:	

	PhysicRobot();

	virtual ~PhysicRobot();

	int getID();
 
	btAlignedObjectArray<PhysicVertex *> getSommets();

	PhysicVertex *getSommet(int i);

	btAlignedObjectArray<PhysicEdge *> getArcs();

	PhysicEdge *getArc(int i);

	/*btScalar getIncremente();*/

	virtual void translate(const btVector3& to) = 0;

	virtual btVector3 getCenterOfMassPosition() = 0;
};

#endif /* Robot */
