#include "ActionControleurRobot.h"

// Le constructeur
ActionControleurRobot::ActionControleurRobot(ControleurRobot *controleurRobot)
{
	this->ctrlRobot = controleurRobot;
}

// Le getter
ControleurRobot* ActionControleurRobot::getControleurRobot()
{
	return this->ctrlRobot;
}

// Le setter
void ActionControleurRobot::setControleurRobot(ControleurRobot *controleurRobot)
{
	this->ctrlRobot = controleurRobot;
}

//Methode executant l'Action
void ActionControleurRobot::execute()
{
	printf("Robot [%d]: etape %d en cours...\n",this->ctrlRobot->getRobot()->getID(),this->ctrlRobot->getEtape()+1);
	this->ctrlRobot->etapeSuivante();	
}