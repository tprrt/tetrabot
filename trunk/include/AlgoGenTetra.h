//  @ Project : Tetrabot
//  @ File Name : AlgoGenTetra.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file AlgoGenTetra.h
 * \brief Algorithme g�n�tique sp�cifique au robot tetrah�drique.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef ALGOGENTETRA_H
#define ALGOGENTETRA_H

#include "AlgoGen.h"
#include "RobotTetra.h"

/**
 * \class AlgoGenTetra
 * \brief Cette classe defini l'algorithme g�n�tique utilisant un robot t�trah�drique. Elle impl�mente la classe AlgoGen.
 */
class AlgoGenTetra: public AlgoGen
{

public:
	// Le Constructeur
	/**
	 * \fn AlgoGenTetra(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);
	 * \brief Constructeur de la classe AlgoGen
	 * \param [monde] : monde virtuel d�crivant la physique selon le moteur bullet.
	 * \param [robot] : Robot � tester.
	 * \param [pointDepart] : point de d�part du robot.
	 * \param [mutation] : pourcentage de la population de controleurs qui subira une mutation al�atoire lors du croisement.
	 * \param [nbRobotsActifs] : nombre de controleur de robot souhait�.
	 * \param [nbEtapes] : nombre d'�tapes que chaque controleur devra r�aliser.
	 * \param [nbCroisements] : nombre de croisements souhait�.
	 */
	AlgoGenTetra(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);

	//virtual ~AlgoGenTetra();
	// Methode permettant de lancer l' algoGen
	/**
	* \fn void run();
	* \brief M�thode d�roulant l'algorithme g�n�tique.
	*/
	void run();

private:
	// Methode creant les Controleurs
	/**
	* \fn void creerControleurs(btDynamicsWorld* monde,int nbRobots);
	* \brief M�thode initialisant les controleurs du robot t�trah�drique � tester.
	*/
	void creerControleurs(btDynamicsWorld* monde,int nbRobots);
	
	// Methode permettant de derouler l' algoGen
	/**
	* \fn static void* execute(void* algoGen);
	* \brief M�thode statique permettant de faire tourner l'algorithme dans un thread.
	* \param [algoGen_Tetra] : instance de l'algorithme g�n�tique pour un robot t�trah�drique.
	* \return NULL : ne retourne rien.
	*/
	static void* execute(void* algoGen_Tetra);
};
#endif /* ALGOGENTETRA_H */
