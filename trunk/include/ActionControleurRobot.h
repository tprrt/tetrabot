/**
 * \file ActionControleurRobot.h
 * \brief Gère une action pour un contrôleur de robot.
 * \author Frozen Brains
 * \version 0.1
 */


#ifndef ACTIONCONTROLEURROBOT_H
#define ACTIONCONTROLEURROBOT_H

#include "ControleurRobot.h"
/**
 * \class ActionControleurRobot
 * \brief Gère une action d'un contrôleur de robot (classe controleurRobot).
 * Cette classe est utilisée par  l'algorithme génétique en vue de faire effectuer un mouvement à un robot par le biais d'un contrôleur de robot.
 */
class ActionControleurRobot: public Action
{
	// Les Attributs
protected:

	ControleurRobot* ctrlRobot; /**< ctrlRobot : Contrôleur du Robot */

	int etape; /**< etape : numéro de l'étape à effectuer par l'algorithme génétique*/

public:
	// Methodes
	/**
	 * \fn ActionControleurRobot(ControleurRobot* controleurRobot);
	 * \brief Constructeur de la classe ActionControleurRobot.
	 * \param [controleurRobot] :  Contrôleur du Robot.
	 */
	ActionControleurRobot(ControleurRobot* controleurRobot);

	//virtual ~ActionControleurRobot();

	/**
	* \fn ControleurRobot* getControleurRobot()
	* \brief getter
	* \return l'attribut ctrlRobot (Contrôleur du Robot).
	*/
	ControleurRobot* getControleurRobot();

	/**
	* \fn int getEtape()
	* \brief getter
	* \return numéro de l'étape à effectuer par l'algorithme génétique.
	*/
	int getEtape();

	/**
	* \fn void setControleurRobot(ControleurRobot* controleurRobot);
	* \brief setter paramètre l'attribut ctrlRobot (Controleur du Robot)
	* \param [controleurRobot] : Contrôleur du Robot.
	*/
	void setControleurRobot(ControleurRobot* controleurRobot);

	/**
	* \fn void setEtape(int numEtape);
	* \brief setter  Paramètre l'attribut étape
	* \param [numEtape] : numéro de l'étape à effectuer par l'algorithme génétique.
	*/
	void setEtape(int numEtape);

	/**
	* \fn void execute();
	* \brief Méthode permettant d'exécuter un mouvement d'un contrôleur de robot.
	*/
	void execute();

};
#endif /* ACTIONCONTROLEURROBOT_H */
