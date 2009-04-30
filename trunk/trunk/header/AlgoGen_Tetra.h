#ifndef ALGOGEN_TETRA_H
#define ALGOGEN_TETRA_H

#include "AlgoGen.h"
#include "Robot_Tetra.h"

class AlgoGen_Tetra: public AlgoGen
{
public:
	AlgoGen_Tetra(btDynamicsWorld* monde,Robot* robot,const btVector3& startPoint,btScalar mutation,int nbRobots,int nbRobotsActifs,int nbEtapes,int nbCroisements);
public:
	void run();
private:
	void creerControleurs(btDynamicsWorld* monde,int nbRobots);
private:
	static void* execute(void* algoGen_Tetra);
};
#endif