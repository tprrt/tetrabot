//  @ Project : Tetrabot
//  @ File Name : ActionPiston.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef ACTIONPISTON_H
#define ACTIONPISTON_H

#include "PhysicPiston.h"
#include "Action.h"

class ActionPiston: public Action
{
protected:
	// piston : c'est le piston auquel est associe l'action
	PhysicPiston* piston;
	// tailleVoulue : nouvelle taille du piston
	btScalar tailleVoulue;

public:

	//Constructeur de la classe ActionPiston
	ActionPiston(PhysicPiston*,btScalar);


	//virtual ~ActionPiston();

	// Retourne la taille voulue pour cette action
	btScalar getTailleVoulue();
	
	//Retourne l'objet de l'action : piston
	PhysicPiston* getPiston();

	// Parametre la taille voulue pour cette action 
	void setTailleVoulue(btScalar taille);

	//Parametre le piston pour cette action
	void setPiston(PhysicPiston* p);
	// Methode permettant un changement de la taille (voulue) d'un piston
	void execute();
};
#endif /* ACTIONPISTON_H */
