#ifndef CONTROLEURROBOT_H
#define CONTROLEURROBOT_H

#include "Sinusoide.h"
#include "Robot.h"
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
	Robot* robot;

	btAlignedObjectArray<Sinusoide*> tabSin;

	btAlignedObjectArray<ActionPiston*> tabAction;

	int etape;

	int id;

	btVector3 posInitial;

	Resultat* resultat;

public:
	ControleurRobot(Robot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);

	ControleurRobot(Robot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);

	~ControleurRobot();

	btAlignedObjectArray<Sinusoide*> getTabSin();

	int getEtape();

	Robot* getRobot();

	Resultat* getResultat();

	// retourne l'identifiant du controleur
	int getID();

	//Les methodes
	// Methode effectuant l'etape  numEtape.
	void execute(int numEtape);

	// Methode creant une instance Resultat
	void updateResultat();

private:
	// methode appelée lors de a creation du controleur
	// pour lui ttribuer un identificateur.
	void setID();
};

#endif /* CONTROLEURROBOT_H */
