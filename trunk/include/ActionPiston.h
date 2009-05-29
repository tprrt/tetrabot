#ifndef ACTIONPISTON_H
#define ACTIONPISTON_H

#include "Piston.h"
#include "Action.h"

class ActionPiston: public Action
{
protected:
	Piston* piston;

	btScalar tailleVoulu;

public:

	ActionPiston(Piston*,btScalar);

	virtual ~ActionPiston();
	btScalar getTailleVoulu();

	Piston* getPiston();

	void setTailleVoulu(btScalar taille);

	void setPiston(Piston* p);

	void execute();
};
#endif /* ACTIONPISTON_H */
