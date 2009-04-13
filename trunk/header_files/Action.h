#ifndef ACTION
#define ACTION

#include "Piston.h"

class Action
{
public:
	Piston* piston;
	btScalar tailleVoulu;
public:
	Action(Piston*,btScalar);
	void execute();
	void setPiston(Piston* p);
	void setTailleVoulu(btScalar taille);
	void setAll(Piston* p,btScalar taille);

};

void * actionThread ( void* p_data );

#endif