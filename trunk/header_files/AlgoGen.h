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
	// Les attributs
	btDynamicsWorld* monde;
	btAlignedObjectArray<ControleurRobot*> tabCtrl;
	btAlignedObjectArray<Resultat*> tabResultat;
	btAlignedObjectArray<ActionControleurRobot*> tabAction;
	int nbEtapes;
	int nbCroisements;
	int nbRobotsActifs;
	int nbRobotMax;
public:
	// Le Constructeur
	AlgoGen(btDynamicsWorld* monde,int nbRobots,int nbRobotsActifs,int nbRobotMax,int nbEtapes,int nbCroisements)
	{
		// Affectation des parametres
		this->nbEtapes = nbEtapes;
		this->nbCroisements = nbCroisements;
		this->nbRobotsActifs = nbRobotsActifs;
		this->nbRobotMax = nbRobotMax;
	}
public:
	// Methode dans laquelle on va creer un thread qui 
	//executera la methode execute de votre classe derivee
	virtual void run()=0;
private:
	virtual void creerControleurs(btDynamicsWorld* monde,int nbRobots)=0;
	static  void* execute(void* algoGen)
	{
		//A IMPLEMENTER DANS VOTRE CLASSE DERIVEE
		// Methode executant l'algorithme Genetique
		return NULL;
	}
	

};

#endif