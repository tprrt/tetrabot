#ifndef CONTROLEURROBOT_H
#define CONTROLEURROBOT_H

#include "Sinusoide.h"
#include "PhysicRobot.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "Threads.h"
#include "ActionPiston.h"
#include "Resultat.h"

// pour les fonctions rand() et srand(...)
#include <cstdlib>
// redefinition de la constante RAND_MAX
#define RAND_MAX 0xffff 

class ControleurRobot
{
protected:
	PhysicRobot* robot;

	btAlignedObjectArray<Sinusoide*> tabSin;

	btAlignedObjectArray<ActionPiston*> tabAction;

	int etape;

	int id;

	btVector3 posInitial;

	Resultat* resultat;

public:
	ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);

	ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);

	~ControleurRobot();

	btAlignedObjectArray<Sinusoide*> getTabSin();

	int getEtape();

	PhysicRobot* getRobot();

	Resultat* getResultat();

	// retourne l'identifiant du controleur
	int getID();

	//Les methodes
	// Methode effectuant l'etape  numEtape.
	void execute(int numEtape);

	// Methode creant une instance Resultat
	void updateResultat();

private:
	// methode appel�e lors de a creation du controleur
	// pour lui ttribuer un identificateur.
	void setID();
};

#endif /* CONTROLEURROBOT_H */