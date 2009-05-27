#include "Action.h"


Action::Action()
	{
		static int ID = 0;
		this->id = ID;
		ID++;
	}


int Action::getID() {
	return this->id;
}

void * actionThread ( void* p_data )
{
	// on recup les donnees
	Action* a = (Action*) p_data ;

	// on exécute l'action
	a->execute();

	// on finit l'action 
	// Le code de retour est 1000 + id de l'action
	// dans le but de differencier l'action 0 du code de retour anormal: 0
	ExitThread((void*)(a->getID()+1000));

	return NULL;
}
