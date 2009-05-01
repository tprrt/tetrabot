#include "Resultat.h"

Resultat::Resultat(int id,btScalar distanceParcouru)
:id(id),
distance(distanceParcouru)
{
}

int Resultat::getID()
{
	return this->id;
}

btScalar Resultat::getDistance()
{
	return this->distance;
}

void Resultat::setDistance(btScalar distance)
{
	this->distance = distance;
}
