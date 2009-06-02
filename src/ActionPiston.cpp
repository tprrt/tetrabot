#include "ActionPiston.h"

ActionPiston::ActionPiston(PhysicPiston * piston, btScalar tailleVoulu)
{
	this->piston = piston;
	this->tailleVoulu = tailleVoulu;
}

void ActionPiston::execute()
{
	//printf("Piston [%d]: taille voulu : %f\n",piston->getID(),tailleVoulu);
	piston->actionnerEdge(this->tailleVoulu);
}

// Les Getters
btScalar ActionPiston::getTailleVoulu()
{
	return this->tailleVoulu;
}
PhysicPiston* ActionPiston::getPiston()
{
	return this->piston;
}

//Les Setters
void ActionPiston::setPiston(PhysicPiston *p)
{ 
	this->piston = p;
}
void ActionPiston::setTailleVoulu(btScalar taille)
{
	this->tailleVoulu = taille;
}

