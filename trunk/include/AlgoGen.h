//  @ Project : Tetrabot
//  @ File Name : AlgoGen.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file AlgoGen.h
 * \brief Bases de notre algorithme g�n�tique.
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
 * \brief Cette classe abstraite permet de d�finir les bases d'un algorithme g�n�tique utilisant un robot et des controleurs de robot.
 */
class AlgoGen
{
public:
	// monde : monde Dynamique
	btDynamicsWorld* monde;/**< monde : monde virtuel d�crivant la physique selon le moteur bullet. */
	// tabCtrl : un vecteur de Controleurs de Robot
	btAlignedObjectArray<ControleurRobot*> tabCtrl;/**< tabCtrl : tableau regroupant les controleurs du robot.*/
	// tabAction : un vecteur d' Actions de Controleur de Robot
	btAlignedObjectArray<ActionControleurRobot*> tabAction;/**< tabAction : tableau regroupant les actions qu'effectuerons les controleurs du robot.*/
	// robot : c'est l'objet sur lequel est applique l' algoGen
	PhysicRobot* robot;/**< robot : Robot utilis� par l'algorithme g�n�tique.*/
	// pointDepart : point de depart
	btVector3 pointDepart;/**< pointDepart : point de d�part du robot.*/
	// mutation : coefficient de mutation ( par defaut c'est 5% )
	btScalar mutation;/**< mutation : pourcentage de la population de controleurs qui subira une mutation al�atoire lors du croisement.*/
	// nbEtapes : nombre d' etapes a effectuer par l' algoGen 
	int nbEtapes;/**< nbEtapes : monbre d'�tape ( mouvement ) que chaque controleur de robot devra r�aliser.*/
	// nbCroisements : nombre de croisements a effectuer par l' algoGen 
	int nbCroisements;/**< nbCroisements : nombre de croisements.*/
	// nbRobotsActifs : population de Robots pris en comtpe pour effectuer par l' algoGen 
	int nbRobotsActifs;/**< nbRobotsActifs : nombre de controleurs du robots maximal.*/

public:
	// Constructeur de la classe AlgoGen
	/**
	 * \fn AlgoGen(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);
	 * \brief Constructeur de la classe AlgoGen
	 * \param [monde] : monde virtuel d�crivant la physique selon le moteur bullet.
	 * \param [robot] : Robot � tester.
	 * \param [pointDepart] : point de d�part du robot.
	 * \param [mutation] : pourcentage de la population de controleurs qui subira une mutation al�atoire lors du croisement.
	 * \param [nbRobotsActifs] : nombre de controleur de robot souhait�.
	 * \param [nbEtapes] : nombre d'�tapes que chaque controleur devra r�aliser.
	 * \param [nbCroisements] : nombre de croisements souhait�.
	 */
	AlgoGen(btDynamicsWorld* monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation,int nbRobotsActifs,int nbEtapes,int nbCroisements);
	
	// Pour demarrer l' algoGen
	/**
	* \fn virtual void run() = 0;
	* \brief M�thode d�roulant l'algorithme.
		Cette m�thode est virtuelle pure pour permettre d'impl�menter son propre algorithme g�n�tique en fonction des attributs de la classe.
	*/
	virtual void run() = 0;

	//virtual ~AlgoGen();

private:
	// Pour creer de Controleurs de Robots
	/**
	* \fn virtual void creerControleurs(btDynamicsWorld* monde,int nbRobots) = 0;
	* \brief M�thode initialisant les controleurs du robot � tester.
	*/
	virtual void creerControleurs(btDynamicsWorld* monde,int nbRobots) = 0;
	
	// Methode executant l'algorithme Genetique
	/**
	* \fn static void* execute(void* algoGen);
	* \brief M�thode statique permettant de faire tourner l'algorithme dans un thread.
		Cette m�thode est � surcharger dans votre classe impl�mentant AlgoGen.
	* \param [algoGen] : instance de votre algorithme g�n�tique.
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

