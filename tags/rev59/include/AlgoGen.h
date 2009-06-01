#ifndef ALGOGEN_H
#define ALGOGEN_H

#include "ControleurRobot.h"
#include "Resultat.h"
#include "ActionControleurRobot.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "ActionControleurRobot.h"

class AlgoGen
{
public:

	btDynamicsWorld* monde;

	btAlignedObjectArray<ControleurRobot*> tabCtrl;

	btAlignedObjectArray<ActionControleurRobot*> tabAction;

	PhysicRobot* robot;

	btVector3 pointDepart;

	btScalar mutation;

	int nbEtapes;

	int nbCroisements;

	int nbRobotsActifs;

public:

	AlgoGen(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);

	virtual void run() = 0;

	//virtual ~AlgoGen();

private:
	virtual void creerControleurs(btDynamicsWorld* monde,int nbRobots) = 0;

	static void* execute(void* algoGen)
	{
		//A IMPLEMENTER DANS VOTRE CLASSE DERIVEE
		// Methode executant l'algorithme Genetique
		return NULL;
	}

};

#endif /* ALGOGEN_H */

