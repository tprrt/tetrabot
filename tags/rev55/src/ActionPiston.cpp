#include "ActionPiston.h"

ActionPiston::ActionPiston(Piston * piston, btScalar tailleVoulu)
{
	this->piston = piston;
	this->tailleVoulu = tailleVoulu;
}

ActionPiston::~ActionPiston() {
	delete this->piston;
}

void ActionPiston::execute()
{
	printf("Piston [%d]: taille voulu : %f\n",piston->getID(),tailleVoulu);
	piston->actionnerPiston(this->tailleVoulu);
}

btScalar ActionPiston::getTailleVoulu()
{
	return this->tailleVoulu;
}

Piston* ActionPiston::getPiston()
{
	return this->piston;
}

void ActionPiston::setPiston(Piston *p)
{ 
	this->piston = p;
}

void ActionPiston::setTailleVoulu(btScalar taille)
{
	this->tailleVoulu = taille;
}

