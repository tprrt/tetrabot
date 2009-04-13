#include "Action.h"

Action::Action(Piston * piston, btScalar tailleVoulu)
{
	this->piston = piston;
	this->tailleVoulu = tailleVoulu;
}
void Action::execute()
{
	piston->actionnerPiston(this->tailleVoulu);
}
void Action::setPiston(Piston *p){ this->piston = p;}
void Action::setTailleVoulu(btScalar taille){this->tailleVoulu = taille;}
void Action::setAll(Piston *p, btScalar taille)
{
	this->piston = p;
	this->tailleVoulu = taille;
}

void* actionThread( void* p_data ){
	printf("bouger!!!!\n");
	// on recup les donnees
	Action* a = (Action*) p_data ;
	// on exécute l'action
	a->execute();	
	// on finit l'action 
	return NULL;
}
