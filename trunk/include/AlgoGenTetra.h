﻿/**
 * \file AlgoGenTetra.h
 * \brief Algorithme génétique spécifique au robot tetraédrique.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef ALGOGENTETRA_H
#define ALGOGENTETRA_H

#include "AlgoGen.h"
#include "RobotTetra.h"

/**
 * \class AlgoGenTetra
 * \brief Cette classe definit l'algorithme génétique utilisant un robot tétraédrique. Elle implémente la classe AlgoGen.
 */
class AlgoGenTetra: public AlgoGen
{

public:
	// Le Constructeur
	/**
	 * \fn AlgoGenTetra(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements)
	 * \brief Constructeur de la classe AlgoGen
	 * \param monde monde virtuel décrivant la physique selon le moteur bullet.
	 * \param robot Robot à tester.
	 * \param pointDepart point de départ du robot.
	 * \param mutation pourcentage de la population de contrôleurs qui subira une mutation aléatoire lors du croisement.
	 * \param nbRobotsActifs nombre de contrôleur de robot souhaité.
	 * \param nbEtapes nombre d'étapes que chaque contrôleur devra réaliser.
	 * \param nbCroisements nombre de croisements souhaité.
	 */
	AlgoGenTetra(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);

	//virtual ~AlgoGenTetra();
	// Methode permettant de lancer l' algoGen
	/**
	 * \fn void run();
	 * \brief Méthode déroulant l'algorithme génétique.
	 */
	void run();

private:
	// Methode creant les Controleurs
	/**
	 * \fn void creerControleurs(btDynamicsWorld* monde,int nbRobots);
	 * \brief Méthode initialisant les contrôleurs du robot tétraédrique à tester.
	 */
	void creerControleurs(btDynamicsWorld* monde,int nbRobots);

	// Methode permettant de derouler l' algoGen
	/**
	 * \fn static void* execute(void* algoGen);
	 * \brief Méthode statique permettant de faire tourner l'algorithme dans un thread.
	 * \param algoGen_Tetra instance de l'algorithme génétique pour un robot tétrahédrique.
	 */
	static void* execute(void* algoGen_Tetra);
};
#endif /* ALGOGENTETRA_H */
