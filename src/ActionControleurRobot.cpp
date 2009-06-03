//  @ Project : Tetrabot
//  @ File Name : ActionControleurRobot.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "ActionControleurRobot.h"

// Constructeur de la classe ActionControleurRobot
ActionControleurRobot::ActionControleurRobot(ControleurRobot *controleurRobot)
{
	this->ctrlRobot = controleurRobot;
}

// Retourne l'attribut ctrlRobot ( Controleur du Robot )
ControleurRobot* ActionControleurRobot::getControleurRobot()
{
	return this->ctrlRobot;
}

// Retourne l'attribut etape (nombre d'etape a effectuer par l'algorithme genetique)
int ActionControleurRobot::getEtape()
{
	return this->etape;
}

// Parametre l'attribut ctrlRobot ( Controleur du Robot )
void ActionControleurRobot::setControleurRobot(ControleurRobot *controleurRobot)
{
	this->ctrlRobot = controleurRobot;
}

// Parametre l'attribut etape (nombre d'etape a effectuer par l'algorithme genetique)
void ActionControleurRobot::setEtape(int numEtape)
{
	this->etape = numEtape;
}

// Methode pour execute une etape de l'algoGen
void ActionControleurRobot::execute()
{
	printf("Execution de l'etape %d, signature IDControleur : %d\n",this->getEtape(),this->ctrlRobot->getID());
	this->ctrlRobot->execute(this->etape);	
}

