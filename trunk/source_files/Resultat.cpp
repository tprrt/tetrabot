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

// Operateurs de comparaison
bool Resultat::operator >(Resultat* r)
{
	return this->distance > r->distance;
}

bool Resultat::operator <(Resultat* r)
{
	return this->distance < r->distance;
}