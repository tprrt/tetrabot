#ifndef PHYSICVERTEX_H
#define PHYSICVERTEX_H
#include "PhysicComponent.h"

class PhysicVertex: virtual public PhysicComponent
{
public:
	PhysicVertex(btDynamicsWorld *world):PhysicComponent(world)
	{
	}
	// link a Vertex to an Edge
	virtual int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ) =0;
};
#endif