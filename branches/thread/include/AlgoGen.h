//  @ Project : Tetrabot
//  @ File Name : AlgoGen.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

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
	// monde : monde Dynamique
	btDynamicsWorld* monde;
	// tabCtrl : un vecteur de Controleurs de Robot
	btAlignedObjectArray<ControleurRobot*> tabCtrl;
	// tabAction : un vecteur d' Actions de Controleur de Robot
	btAlignedObjectArray<ActionControleurRobot*> tabAction;
	// robot : c'est l'objet sur lequel est applique l' algoGen
	PhysicRobot* robot;
	// pointDepart : point de depart
	btVector3 pointDepart;
	// mutation : coefficient de mutation ( par defaut c'est 5% )
	btScalar mutation;
	// nbEtapes : nombre d' etapes a effectuer par l' algoGen 
	int nbEtapes;
	// nbCroisements : nombre de croisements a effectuer par l' algoGen 
	int nbCroisements;
	// nbRobotsActifs : population de Robots pris en comtpe pour effectuer par l' algoGen 
	int nbRobotsActifs;

public:
	// Constructeur de la classe AlgoGen
	AlgoGen(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);
	// Pour demarrer l' algoGen
	virtual void run() = 0;

	//virtual ~AlgoGen();

private:
	// Pour creer de Controleurs de Robots
	virtual void creerControleurs(btDynamicsWorld* monde,int nbRobots) = 0;
	
	// Methode executant l'algorithme Genetique
	static void* execute(void* algoGen)
	{
		//A IMPLEMENTER DANS VOTRE CLASSE DERIVEE
		// Methode executant l'algorithme Genetique
		return NULL;
	}

};

#endif /* ALGOGEN_H */

