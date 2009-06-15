/**
 * \file ActionControleurRobot.h
 * \brief Gere une action pour un controleur de robot.
 * \author Frozen Brains
 * \version 0.1
 */


#ifndef ACTIONCONTROLEURROBOT_H
#define ACTIONCONTROLEURROBOT_H

#include "ControleurRobot.h"
/**
 * \class ActionControleurRobot
 * \brief G�re une action d'un controleur de robot (classe controleuRobot). 
	Cette classe est utilis�e par  l'algorithme genetique en vue de faire effectuer un mouvement � un robot par le biais d'un controleur de robot.
 */
class ActionControleurRobot: public Action
{
	// Les Attributs
protected:

	ControleurRobot* ctrlRobot; /**< ctrlRobot : Controleur du Robot */
	
	int etape; /**< etape : num�ro de l'�tape � effectuer par l'algorithme genetique*/

public:
	// Methodes
	/**
	 * \fn ActionControleurRobot(ControleurRobot* controleurRobot);
	 * \brief Constructeur de la classe ActionControleurRobot.
	 * \param [controleurRobot] :  Controleur du Robot.
	 */
	ActionControleurRobot(ControleurRobot* controleurRobot);

	//virtual ~ActionControleurRobot();

	/**
	* \fn ControleurRobot* getControleurRobot()
	* \brief getter
	* \return l'attribut ctrlRobot ( Controleur du Robot ).
	*/
	ControleurRobot* getControleurRobot();
	
	/**
	* \fn int getEtape()
	* \brief getter
	* \return num�ro de l'�tape � effectuer par l'algorithme g�n�tique.
	*/
	
	int getEtape();
	
	/**
	* \fn void setControleurRobot(ControleurRobot* controleurRobot);
	* \brief setter parametre l'attribut ctrlRobot ( Controleur du Robot )
	* \param [controleurRobot] : Controleur du Robot.
	*/
	
	void setControleurRobot(ControleurRobot* controleurRobot);
	
	/**
	* \fn void setEtape(int numEtape);
	* \brief setter  Parametre l'attribut etape 
	* \param [numEtape] : num�ro de l'�tape � effectuer par l'algorithme g�n�tique.
	*/

	void setEtape(int numEtape);
	
	/**
	* \fn void execute();
	* \brief M�thode permettant d'ex�cuter un mouvement d'un controleur de robot.
	*/
	void execute();

};
#endif /* ACTIONCONTROLEURROBOT_H */
