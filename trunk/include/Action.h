/**
 * \file Action.h
 * \brief Execute les actions avec un thread
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef ACTION_H
#define ACTION_H

#include "Threads.h"
/**
 * \class Action
 * \brief Classe executant les actions avec un thread
 */
class Action
{
protected:
	// ATTRIBUTS
	int id; /**< Identifieur d'une action */

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
	 * \return l'identifieur de la classe
	 */
	int getID();

	/**
	 * \fn void execute(Ogre::SceneNode *b1, Ogre::SceneNode *b2) ;
	 * \brief Méthode permettant d'executer un action avec un thread
	 */
	virtual void execute() = 0;
};

	/**
	 * \fn void actionThread(void* p_data) ;
	 * \brief Fonction permettant de convertir du void* en action* et d'executer un action avec un thread
	 * \param p_data une actionPiston caster en void *
	 */
void * actionThread (void* p_data );


#endif /* ACTION_H */
