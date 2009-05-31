#include "AlgoGen.h"

AlgoGen::AlgoGen(btDynamicsWorld* monde,Robot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements)
{
		this->nbEtapes = nbEtapes;

		this->nbCroisements = nbCroisements;

		this->nbRobotsActifs = nbRobotsActifs;

		this->robot = robot;

		this->pointDepart = startPoint;

		this->mutation = mutation;
}

AlgoGen::~AlgoGen() {
	delete this->robot;
	delete this->monde;

	for(int i=0;i<this->tabAction.size();i++){
		delete this->tabAction[i];
	}
	for(int i=0;i<this->tabCtrl.size();i++){
		delete this->tabCtrl[i];
	}
}
