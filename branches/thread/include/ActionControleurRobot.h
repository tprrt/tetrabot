//  @ Project : Tetrabot
//  @ File Name : ActionControleurRobot.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef ACTIONCONTROLEURROBOT_H
#define ACTIONCONTROLEURROBOT_H

#include "ControleurRobot.h"

class ActionControleurRobot: public Action
{
	// Les Attributs
protected:

	//ctrlRobot : Controleur du Robot
	ControleurRobot* ctrlRobot;
	
	//etape : nombre d'etape a effectuer par l'algorithme genetique
	int etape;

public:
	// Constructeur de la classe ActionControleurRobot
	ActionControleurRobot(ControleurRobot* controleurRobot);

	//virtual ~ActionControleurRobot();
	
	// Retourne l'attribut ctrlRobot ( Controleur du Robot )
	ControleurRobot* getControleurRobot();
	// Retourne l'attribut etape (nombre d'etape a effectuer par l'algorithme genetique)
	int getEtape();
	// Parametre l'attribut ctrlRobot ( Controleur du Robot )
	void setControleurRobot(ControleurRobot* controleurRobot);
	// Parametre l'attribut etape (nombre d'etape a effectuer par l'algorithme genetique)
	void setEtape(int numEtape);
	// Methode pour execute une etape de l'algoGen
	void execute();
};
#endif /* ACTIONCONTROLEURROBOT_H */
