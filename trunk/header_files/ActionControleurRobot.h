#ifndef ACTIONCONTROLEURROBOT_H
#define ACTIONCONTROLEURROBOT_H

#include "ControleurRobot.h"

class ActionControleurRobot: public Action
{
	// Les Attributs
protected:
	ControleurRobot* ctrlRobot;
	// Le constructeur
public:
	ActionControleurRobot(ControleurRobot* controleurRobot);
	// Le getter
	ControleurRobot* getControleurRobot();
	// Le setter
	void setControleurRobot(ControleurRobot* controleurRobot);
	//Methode executant l'action
	void execute();

};
#endif