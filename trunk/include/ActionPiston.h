/**
 * \file ActionPiston.h
 * \brief Gere les action des pistons
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef ACTIONPISTON_H
#define ACTIONPISTON_H

#include "PhysicPiston.h"
#include "Action.h"

/**
 * \class ActionPiston
 * \brief parametre l'action d'un piston 
 */
class ActionPiston: public Action
{
protected:
	// ATTRIBUTS
	/**< piston : c'est le piston auquel est associe l'action */
	PhysicPiston* piston;
	/**< tailleVoulue : nouvelle taille du piston */
	btScalar tailleVoulue;

public:
	// METHODES
	
	/**
	 * \fn ActionPiston(PhysicPiston*,btScalar);
	 * \brief Constructeur de la classe ActionPiston
	 * \param PhysicPiston*  
	 * \param btScalar	
	 */
	ActionPiston(PhysicPiston*,btScalar);

	//virtual ~ActionPiston();

	/**
	 * \fn btScalar getTailleVoulue();
	 * \brief getter
	 * \return la taille voulue pour cette action
	 */
	btScalar getTailleVoulue();
	
	/**
	 * \fn PhysicPiston* getPiston();
	 * \brief getter
	 * \return l'objet de l'action : piston
	 */
	PhysicPiston* getPiston();

	/**
	 * \fn PhysicPiston* getPiston();
	 * \brief setter Parametre la taille voulue pour cette action 
	 * \param taille
	 */
	void setTailleVoulue(btScalar taille);

	/**
	 * \fn void setPiston(PhysicPiston* p);
	 * \brief setter Parametre le piston pour cette action
	 * \param p 
	 */
	void setPiston(PhysicPiston* p);
	
	/**
	 * \fn void execute();
	 * \brief Methode permettant un changement de la taille (voulue) d'un piston
	 */
	void execute();
};
#endif /* ACTIONPISTON_H */
