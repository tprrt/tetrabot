#ifndef ACTIONCONTROLEURROBOT_H
#define ACTIONCONTROLEURROBOT_H

#include "ControleurRobot.h"

class ActionControleurRobot: public Action
{
	// Les Attributs
protected:
	ControleurRobot* ctrlRobot;

	int etape;

public:
	ActionControleurRobot(ControleurRobot* controleurRobot);

	//virtual ~ActionControleurRobot();

	ControleurRobot* getControleurRobot();

	int getEtape();

	void setControleurRobot(ControleurRobot* controleurRobot);

	void setEtape(int numEtape);

	void execute();
};
#endif /* ACTIONCONTROLEURROBOT_H */
