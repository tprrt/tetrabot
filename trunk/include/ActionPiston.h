/**
 * \file ActionPiston.h
 * \brief Gere un �tirement d'un piston
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef ACTIONPISTON_H
#define ACTIONPISTON_H

#include "PhysicPiston.h"
#include "Action.h"

/**
 * \class ActionPiston
 * \brief parametre l'action � effectuer sur un piston. 
 */
class ActionPiston: public Action
{
protected:
	// ATTRIBUTS
	
	PhysicPiston* piston; /**< piston : c'est le piston auquel est associe l'action */
	
	btScalar tailleVoulue; /**< tailleVoulue : nouvelle taille du piston */

public:
	// METHODES
	
	/**
	 * \fn ActionPiston(PhysicPiston* piston, btScalar taille);
	 * \brief Constructeur de la classe ActionPiston
	 * \param [piston] :  piston sur lequel l'action s'effectue.
	 * \param [taille] : taille souhait�e du piston.
	 */
	ActionPiston(PhysicPiston*,btScalar);

	//virtual ~ActionPiston();

	/**
	 * \fn btScalar getTailleVoulue();
	 * \brief getter
	 * \return taille du piston voulue pour cette action.
	 */
	btScalar getTailleVoulue();
	
	/**
	 * \fn PhysicPiston* getPiston();
	 * \brief getter 
	 * \return Piston sur lequel l'action s'effectue.
	 */
	PhysicPiston* getPiston();

	/**
	 * \fn void setTailleVoulue(btScalar taille);
	 * \brief setter
	 * \param [taille] : longueur du piston voulue pour cette action. 
	 */
	void setTailleVoulue(btScalar taille);

	/**
	 * \fn void setPiston(PhysicPiston* p);
	 * \brief setter 
	 * \param [p] : piston � associer � cette action.
	 */
	void setPiston(PhysicPiston* p);
	
	/**
	 * \fn void execute();
	 * \brief M�thode effectuant un changement de la taille (voulue) d'un piston.
	 */
	void execute();
};
#endif /* ACTIONPISTON_H */
