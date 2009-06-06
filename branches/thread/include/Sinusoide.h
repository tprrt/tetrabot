#ifndef SINUSOIDE_H
#define SINUSOIDE_H

#include "characteristics.h"
#include "btBulletDynamicsCommon.h"

class Sinusoide
{
protected:
	btScalar periode;
	btScalar amplitude;
	btScalar dephasage;
public:
	Sinusoide(btScalar periode, btScalar amplitude, btScalar dephasage);

	Sinusoide(const Sinusoide& s);

	virtual ~Sinusoide();

	btScalar getPeriode();

	btScalar getAmplitude();

	btScalar getDephasage();


	void setPeriode(btScalar p);

	void setAmplitude(btScalar a);

	void setDephasage(btScalar d);

	btScalar sinus(btScalar angle);

};
#endif
