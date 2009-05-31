#ifndef PHYSICEDGE_H
#define PHYSICEDGE_H

#include "PhysicComponent.h"

class PhysicEdge : virtual public PhysicComponent
{
public:
	PhysicEdge(btDynamicsWorld *world): PhysicComponent(world)
	{
	}
	virtual ~PhysicEdge()
	{
	}

	virtual int actionnerEdge(btScalar tailleVoulu) = 0;
	virtual void lock() = 0;
	virtual void unlock() = 0;
};
#endif
