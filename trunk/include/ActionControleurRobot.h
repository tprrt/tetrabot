/**
 * \file ActionControleurRobot.h
 * \brief Gere les actions des controleurs robots
 * \author Frozen Brains
 * \version 0.1
 */


#ifndef ACTIONCONTROLEURROBOT_H
#define ACTIONCONTROLEURROBOT_H

#include "ControleurRobot.h"
/**
 * \class ActionControleurRobot
 * \brief Gere les actions des controleurs robots
 */
class ActionControleurRobot: public Action
{
	// Les Attributs
protected:

	/**< ctrlRobot : Controleur du Robot */
	ControleurRobot* ctrlRobot;
	
	/**< etape : nombre d'etape a effectuer par l'algorithme genetique*/
	int etape;

public:
	// Methodes
	/**
	 * \fn ActionControleurRobot(ControleurRobot* controleurRobot);
	 * \brief Constructeur de la classe ActionControleurRobot
	 * \param controleurRobot  Controleur du Robot
	 */
	ActionControleurRobot(ControleurRobot* controleurRobot);

	//virtual ~ActionControleurRobot();

	/**
	* \fn ControleurRobot* getControleurRobot()
	* \brief getter
	* \ return l'attribut ctrlRobot ( Controleur du Robot )
	*/
	ControleurRobot* getControleurRobot();
	
	/**
	* \fn int getEtape()
	* \brief getter
	* \ return l'attribut etape (nombre d'etape a effectuer par l'algorithme genetique)
	*/
	
	int getEtape();
	
	/**
	* \fn void setControleurRobot(ControleurRobot* controleurRobot);
	* \brief setter parametre l'attribut ctrlRobot ( Controleur du Robot )
	* \param controleurRobot ( Controleur du Robot )
	*/
	
	void setControleurRobot(ControleurRobot* controleurRobot);
	
	/**
	* \fn void setEtape(int numEtape);
	* \brief setter  Parametre l'attribut etape 
	* \param numEtape (nombre d'etape a effectuer par l'algorithme genetique)
	*/

	void setEtape(int numEtape);
	
	/**
	* \fn void execute();
	* \brief Methode pour execute une etape de l'algoGen
	*/
	void execute();
};
#endif /* ACTIONCONTROLEURROBOT_H */
