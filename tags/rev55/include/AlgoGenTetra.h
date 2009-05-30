#ifndef ALGOGENTETRA_H
#define ALGOGENTETRA_H

#include "AlgoGen.h"
#include "RobotTetra.h"

class AlgoGenTetra: public AlgoGen
{

public:
	AlgoGenTetra(btDynamicsWorld* monde,Robot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);

	//virtual ~AlgoGenTetra();

	void run();

private:
	void creerControleurs(btDynamicsWorld* monde,int nbRobots);

	static void* execute(void* algoGen_Tetra);
};
#endif /* ALGOGENTETRA_H */
