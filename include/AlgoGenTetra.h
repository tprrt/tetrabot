//  @ Project : Tetrabot
//  @ File Name : AlgoGenTetra.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef ALGOGENTETRA_H
#define ALGOGENTETRA_H

#include "AlgoGen.h"
#include "RobotTetra.h"

class AlgoGenTetra: public AlgoGen
{

public:
	// Le Constructeur
	AlgoGenTetra(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);

	//virtual ~AlgoGenTetra();
	// Methode permettant de lancer l' algoGen
	void run();

private:
	// Methode creant les Controleurs
	void creerControleurs(btDynamicsWorld* monde,int nbRobots);
	// Methode permettant de derouler l' algoGen
	static void* execute(void* algoGen_Tetra);
};
#endif /* ALGOGENTETRA_H */
