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
int ActionControleurRobot::getEtape()
{
	return this->etape;
}

// Le setter
void ActionControleurRobot::setControleurRobot(ControleurRobot *controleurRobot)
{
	this->ctrlRobot = controleurRobot;
}
void ActionControleurRobot::setEtape(int numEtape)
{
	this->etape = numEtape;
}

//Methode executant l'Action
void ActionControleurRobot::execute()
{
	printf("Controleur [%d]: etape %d en cours...\n",this->ctrlRobot->getID(),this->getEtape());
	this->ctrlRobot->execute(this->etape);	
}