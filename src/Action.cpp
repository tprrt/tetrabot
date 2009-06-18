//  @ Project : Tetrabot
//  @ File Name : Action.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "Action.h"

// Constructeur de la classe action
Action::Action()
	{
		static int ID = 0;
		this->id = ID;
		ID++;
	}

// Retourne l'attribut id (identifiant) de l'action
int Action::getID() {
	return this->id;
}

// Permet l'exécution d'une action via un thread
void * actionThread ( void* p_data )
{
	// on recupère les donnees
	Action* a = (Action*) p_data ;

	// on exécute l'action
	a->execute();

	// on finit l'action 
	// Le code de retour est 1000 + id de l'action
	// dans le but de differencier l'action 0 du code de retour anormal: 0
	ExitThread((void*)(a->getID()+1000));

	return NULL;
}
