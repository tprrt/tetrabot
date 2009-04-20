#ifndef SINUSOIDE_H
#define SINUSOIDE_H

#include "Caracteristiques.h"
#include "btBulletDynamicsCommon.h"

class Sinusoide
{
public:
	btScalar periode;
	btScalar amplitude;
	btScalar dephasage;
public:
	// Le Constructeur
	Sinusoide(btScalar periode, btScalar amplitude, btScalar dephasage)
	{
		this->periode = periode;
		this->amplitude = amplitude;
		this->dephasage = dephasage;
	}

	// Les méthodes
	// methode calculant le sinus  en fonction de ses 3 attributs
	btScalar sinus(btScalar angle)
	{
		return (btScalar(amplitude/btScalar(2.F) * sin(dephasage + angle*2*M_PI/periode)));
	}

};
#endif