#ifndef CONTROLEURROBOT_H
#define CONTROLEURROBOT_H

#include "Sinusoide.h"
#include "Robot.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "Threads.h"
#include "ActionPiston.h"
#include "Resultat.h"


class ControleurRobot
{
protected:
	Robot* robot;
	// tableau de sinusoides
	btAlignedObjectArray<Sinusoide*> tabSin;
	// tableau d'actions (pour les threads)
	btAlignedObjectArray<ActionPiston*> tabAction;
	int etape;
	int idRobot;
	btVector3 posInitial;
public:
	// Les Constructeurs
	// Sinusoides aléatoires
	ControleurRobot(Robot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);
	// Sinusoides connues
	ControleurRobot(Robot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);

	// les getters 
	btAlignedObjectArray<Sinusoide*> getTabSin();
	int getEtape();
	Robot* getRobot();

	//Les methodes
	// Methode effectuant l'etape suivante.
	void etapeSuivante();
	// Methode creant une instance Resultat
	Resultat* creerResultat();
};

#endif