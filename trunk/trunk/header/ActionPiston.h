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
	// Le constructeur
	ActionPiston(Piston*,btScalar);
public:
	// Les getters et setters
	btScalar getTailleVoulu();
	Piston* getPiston();
	void setTailleVoulu(btScalar taille);
	void setPiston(Piston* p);
	//Methode executant l'action
	void execute();
};
#endif