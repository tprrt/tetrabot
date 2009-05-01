#ifndef RESULTAT_H
#define RESULTAT_H

#include "btBulletDynamicsCommon.h"

class Resultat
{
	// Attributs
protected:
	btScalar distance;
	int id;
	// Le constructeur
public:
	Resultat(int id,btScalar distanceParcouru);
	//les getters
	btScalar getDistance();
	//les setters
	void setDistance(btScalar distance);
	// obtenir l'identifiant du resultat
	int getID();
};

#endif