//  @ Project : Tetrabot
//  @ File Name : AlgoGen.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file AlgoGen.h
 * \brief Bases de notre algorithme génétique.
 * \author Frozen Brains
 * \version 0.1
 */
 
#ifndef ALGOGEN_H
#define ALGOGEN_H

#include "ControleurRobot.h"
#include "Resultat.h"
#include "ActionControleurRobot.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "ActionControleurRobot.h"

/**
 * \class AlgoGen
 * \brief Cette classe abstraite permet de définir les bases d'un algorithme génétique utilisant un robot et des controleurs de robot.
 */
class AlgoGen
{
public:
	// monde : monde Dynamique
	btDynamicsWorld* monde;/**< monde : monde virtuel décrivant la physique selon le moteur bullet. */
	// tabCtrl : un vecteur de Controleurs de Robot
	btAlignedObjectArray<ControleurRobot*> tabCtrl;/**< tabCtrl : tableau regroupant les controleurs du robot.*/
	// tabAction : un vecteur d' Actions de Controleur de Robot
	btAlignedObjectArray<ActionControleurRobot*> tabAction;/**< tabAction : tableau regroupant les actions qu'effectuerons les controleurs du robot.*/
	// robot : c'est l'objet sur lequel est applique l' algoGen
	PhysicRobot* robot;/**< robot : Robot utilisé par l'algorithme génétique.*/
	// pointDepart : point de depart
	btVector3 pointDepart;/**< pointDepart : point de départ du robot.*/
	// mutation : coefficient de mutation ( par defaut c'est 5% )
	btScalar mutation;/**< mutation : pourcentage de la population de controleurs qui subira une mutation aléatoire lors du croisement.*/
	// nbEtapes : nombre d' etapes a effectuer par l' algoGen 
	int nbEtapes;/**< nbEtapes : monbre d'étape ( mouvement ) que chaque controleur de robot devra réaliser.*/
	// nbCroisements : nombre de croisements a effectuer par l' algoGen 
	int nbCroisements;/**< nbCroisements : nombre de croisements.*/
	// nbRobotsActifs : population de Robots pris en comtpe pour effectuer par l' algoGen 
	int nbRobotsActifs;/**< nbRobotsActifs : nombre de controleurs du robots maximal.*/

public:
	// Constructeur de la classe AlgoGen
	/**
	 * \fn AlgoGen(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);
	 * \brief Constructeur de la classe AlgoGen
	 * \param [monde] : monde virtuel décrivant la physique selon le moteur bullet.
	 * \param [robot] : Robot à tester.
	 * \param [pointDepart] : point de départ du robot.
	 * \param [mutation] : pourcentage de la population de controleurs qui subira une mutation aléatoire lors du croisement.
	 * \param [nbRobotsActifs] : nombre de controleur de robot souhaité.
	 * \param [nbEtapes] : nombre d'étapes que chaque controleur devra réaliser.
	 * \param [nbCroisements] : nombre de croisements souhaité.
	 */
	AlgoGen(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);
	
	// Pour demarrer l' algoGen
	/**
	* \fn virtual void run() = 0;
	* \brief Méthode déroulant l'algorithme.
		Cette méthode est virtuelle pure pour permettre d'implémenter son propre algorithme génétique en fonction des attributs de la classe.
	*/
	virtual void run() = 0;

	//virtual ~AlgoGen();

private:
	// Pour creer de Controleurs de Robots
	/**
	* \fn virtual void creerControleurs(btDynamicsWorld* monde,int nbRobots) = 0;
	* \brief Méthode initialisant les controleurs du robot à tester.
	*/
	virtual void creerControleurs(btDynamicsWorld* monde,int nbRobots) = 0;
	
	// Methode executant l'algorithme Genetique
	/**
	* \fn static void* execute(void* algoGen);
	* \brief Méthode statique permettant de faire tourner l'algorithme dans un thread.
		Cette méthode est à surcharger dans votre classe implémentant AlgoGen.
	* \param [algoGen] : instance de votre algorithme génétique.
	* \return NULL
	*/
	static void* execute(void* algoGen)
	{
		//A IMPLEMENTER DANS VOTRE CLASSE DERIVEE
		// Methode executant l'algorithme Genetique
		return NULL;
	}

};

#endif /* ALGOGEN_H */

