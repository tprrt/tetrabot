//  @ Project : Tetrabot
//  @ File Name : PhysicEdge.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef PHYSICEDGE_H
#define PHYSICEDGE_H

#include "PhysicComponent.h"

class PhysicEdge : virtual public PhysicComponent
{
public:
	//Constructeur de la classe PhysicEdge
	PhysicEdge(btDynamicsWorld *world): PhysicComponent(world)
	{
	}
	//Destructeur de la classe PhysicEdge
	virtual ~PhysicEdge()
	{
	}
	// Methode pour actionner un edge
	virtual int actionnerEdge(btScalar tailleVoulu) = 0;
	virtual void lock() = 0;
	virtual void unlock() = 0;
};
#endif
