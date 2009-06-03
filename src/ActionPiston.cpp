//  @ Project : Tetrabot
//  @ File Name : ActionPiston.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "ActionPiston.h"

//Constructeur de la classe ActionPiston
ActionPiston::ActionPiston(PhysicPiston * piston, btScalar tailleVoulue)
{
	this->piston = piston;
	this->tailleVoulue = tailleVoulue;
}

// Methode permettant un changement de la taille (voulue) d'un piston
void ActionPiston::execute()
{
	//printf("Piston [%d]: taille voulue : %f\n",piston->getID(),tailleVoulue);
	piston->actionnerEdge(this->tailleVoulue);
}

// Les Getters
// Retourne la taille voulue pour cette action
btScalar ActionPiston::getTailleVoulue()
{
	return this->tailleVoulue;
}

//Retourne l'objet de l'action : piston
PhysicPiston* ActionPiston::getPiston()
{
	return this->piston;
}

//Les Setters
//Parametre le piston pour cette action
void ActionPiston::setPiston(PhysicPiston *p)
{ 
	this->piston = p;
}
// Parametre la taille voulue pour cette action 
void ActionPiston::setTailleVoulue(btScalar taille)
{
	this->tailleVoulue = taille;
}

