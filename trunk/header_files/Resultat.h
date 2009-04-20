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
	// obtenir l'identifiant du resultat
	int getID();
	// operateurs de comparaison
	bool operator > (Resultat* r);
	bool operator < (Resultat* r);
};

#endif