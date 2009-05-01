#ifndef SINUSOIDE_H
#define SINUSOIDE_H

#include "Caracteristiques.h"
#include "btBulletDynamicsCommon.h"

class Sinusoide
{
protected:
	btScalar periode;
	btScalar amplitude;
	btScalar dephasage;
public:
	// Les Constructeurs
	Sinusoide(btScalar periode, btScalar amplitude, btScalar dephasage);
	Sinusoide(const Sinusoide& s);
	// Les getters
	btScalar getPeriode();
	btScalar getAmplitude();
	btScalar getDephasage();
	// Les setters
	void setPeriode(btScalar p);
	void setAmplitude(btScalar a);
	void setDephasage(btScalar d);
	// Les méthodes
	// methode calculant le sinus  en fonction de ses 3 attributs
	btScalar sinus(btScalar angle);
	

};
#endif