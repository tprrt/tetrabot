/**
 * \file Action.h
 * \brief Exécute les actions avec un thread
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef ACTION_H
#define ACTION_H

#include "Threads.h"
/**
 * \class Action
 * \brief Classe exécutant les actions par le biais d'un thread
 */
class Action
{
protected:
	// ATTRIBUTS
	int id; /**< Identifiant d'une action */

public:
	// METHODES
	/**
	 * \fn Action(void)
	 * \brief Constructeur
	 */
	Action();

	//virtual ~Action();

	/**
	 * \fn int getID();
	 * \brief getter
	 * \return Identifiant de la classe.
	 */
	int getID();

	/**
	 * \fn void execute() ;
	 * \brief Méthode permettant d'exécuter une action avec un thread
	 */
	virtual void execute() = 0;
};

	/**
	 * \fn void actionThread(void* p_data) ;
	 * \brief Fonction utilisée par un thread et permettant d'exécuter une action avec un thread.
	 * \param p_data une action (de la classe Action ou dérivée) castée en void *.
	 */
void * actionThread (void* p_data );


#endif /* ACTION_H */
