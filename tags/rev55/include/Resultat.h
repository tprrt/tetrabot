#ifndef RESULTAT_H
#define RESULTAT_H

#include "btBulletDynamicsCommon.h"

class Resultat {

protected:
	btScalar distance;

	int id;

public:
	Resultat(int id,btScalar distanceParcouru);

	//virtual ~Resultat();

	btScalar getDistance();

	void setDistance(btScalar distance);

	int getID();
};

#endif
