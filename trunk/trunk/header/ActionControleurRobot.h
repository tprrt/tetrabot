#ifndef ACTIONCONTROLEURROBOT_H
#define ACTIONCONTROLEURROBOT_H

#include "ControleurRobot.h"

class ActionControleurRobot: public Action
{
	// Les Attributs
protected:
	ControleurRobot* ctrlRobot;
	int etape;
	// Le constructeur
public:
	ActionControleurRobot(ControleurRobot* controleurRobot);
	// Le getter
	ControleurRobot* getControleurRobot();
	int getEtape();
	// Le setter
	void setControleurRobot(ControleurRobot* controleurRobot);
	void setEtape(int numEtape);
	//Methode executant l'action
	void execute();

};
#endif