#ifndef ACTIONPISTON_H
#define ACTIONPISTON_H

#include "PhysicPiston.h"
#include "Action.h"

class ActionPiston: public Action
{
protected:
	PhysicPiston* piston;

	btScalar tailleVoulu;

public:

	ActionPiston(PhysicPiston*,btScalar);


	//virtual ~ActionPiston();


	btScalar getTailleVoulu();

	PhysicPiston* getPiston();

	void setTailleVoulu(btScalar taille);

	void setPiston(PhysicPiston* p);

	void execute();
};
#endif /* ACTIONPISTON_H */
