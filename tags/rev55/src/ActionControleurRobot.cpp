#include "ActionControleurRobot.h"

ActionControleurRobot::ActionControleurRobot(ControleurRobot *controleurRobot)
{
	this->ctrlRobot = controleurRobot;
}

ActionControleurRobot::~ActionControleurRobot() {
	delete this->ctrlRobot;
}

ControleurRobot* ActionControleurRobot::getControleurRobot()
{
	return this->ctrlRobot;
}

int ActionControleurRobot::getEtape()
{
	return this->etape;
}


void ActionControleurRobot::setControleurRobot(ControleurRobot *controleurRobot)
{
	this->ctrlRobot = controleurRobot;
}

void ActionControleurRobot::setEtape(int numEtape)
{
	this->etape = numEtape;
}


void ActionControleurRobot::execute()
{
	printf("Controleur [%d]: etape %d en cours...\n",this->ctrlRobot->getID(),this->getEtape());
	this->ctrlRobot->execute(this->etape);	
}

