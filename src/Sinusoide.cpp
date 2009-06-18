#include "Sinusoide.h"

Sinusoide::Sinusoide(btScalar periode, btScalar amplitude, btScalar dephasage)
{
	this->periode = periode;
	this->amplitude = amplitude;
	this->dephasage = dephasage;
}

Sinusoide::Sinusoide(const Sinusoide& s)
{
	this->periode = s.periode;
	this->amplitude = s.amplitude;
	this->dephasage = s.dephasage;
}
// destructeur
Sinusoide::~Sinusoide(){
	//delete &this->periode;
	//delete &this->amplitude;
	//delete &this->dephasage;
}
// Les getters
btScalar Sinusoide::getPeriode()
{
	return this->periode;
}
btScalar Sinusoide::getAmplitude()
{
	return this->amplitude;
}
btScalar Sinusoide::getDephasage()
{
	return this->dephasage;
}
// Les setters
void Sinusoide::setPeriode(btScalar p)
{
	this->periode = p;
}
void Sinusoide::setAmplitude(btScalar a)
{
	this->amplitude = a;
}
void Sinusoide::setDephasage(btScalar d)
{
	this->dephasage = d;
}

btScalar Sinusoide::sinus(btScalar angle)
{
	return (btScalar(amplitude * sin(dephasage + angle*2*M_PI/periode)));
}
