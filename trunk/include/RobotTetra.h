/**
 * \file RobotTetra.h
 * \brief Robot à la forme tétrahedrique.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef ROBOTTETRA
#define ROBOTTETRA


#include "PhysicRobot.h"
#include "PhysicNoeud.h"
#include "PhysicPiston.h"
/*
#include "Action.h"
#include "Caracteristiques.h"
#include "PhysicWorld.h"
*/
#include "ActionPiston.h"
// JAZZ MODIF :  1 JUIN 2009 : 2h42
#include "Threads.h"
// JAZZ MODIF :  1 JUIN 2009 : 3h31
#include "AlgoGenTetra.h"
/**
* \class RobotTetra
* \brief Classe créant un robot tétrahédrique composé de noeuds sphériques et de pistons.
*/
class RobotTetra: public PhysicRobot
{
protected:

	ActionPiston*	action[6];/** < action : Tableau d'Action utilisées par les pistons du robot.*/

public:	
	btRigidBody* bodyCube;
	btVector3* end;/** < end : Point d'intéraction avec le robot. */
	
public:
	// Test avec GL
	/**
	* \fn RobotWheels(btDynamicsWorld* world,const btVector3& posInit);
	* \brief Constructeur du robot.
	* \param [world] : définition du monde selon le moteur physique Bullet.
	* \param [posInit] : position initiale du robot: une translation est donc effectuée pour que le robot soit précisement à ce point.
	*/
	RobotTetra(btDynamicsWorld* world,const btVector3& posInit);

	// Test avec Ogre
	/**
	* \fn RobotWheels(btDynamicsWorld* world,const btVector3& posInit);
	* \brief Constructeur du robot en relation avec le moteur graphique Ogre. 
		Seul les noeuds du robot sont en relations avec Ogre: ils sont suffisants pour représenter le robot sous Ogre.
	* \param [world] : définition du monde selon le moteur physique Bullet.
	* \param [scene] : Scène du moteur Ogre contenant toutes les représentations des noeuds du robot tétrahédrique.
	* \param [posInit] : position initiale du robot: une translation est donc effectuée pour que le robot soit précisement à ce point.
	*/
	RobotTetra(btDynamicsWorld* world,Ogre::SceneManager * scene,const btVector3& posInit);

	/**
	* \fn btVector3 getCenterOfMassPosition();
	* \brief Méthode calculant le centre de masse du robot.
	* \return Centre de masse du robot.
	*/
	btVector3 getCenterOfMassPosition();
	
	/**
	* \fn bool IsNotInArea(const btVector3 &G,const btVector3 &end2);
	* \brief Détermine si les deux points sont distant d'au moins 5 unitées de mesure.
	* \param [G] : Premier point.
	* \param [end2] : Second point.
	* \return Vrai si la distance est supérieur à 5. Faux sinon.
	*/
	bool IsNotInArea(const btVector3 &G,const btVector3 &end2);
	// methode pour faire marcher le robot
	/**
	* \fn static void* marcherRobot(void* demo);
	* \brief Méthode utilisée par un thread pour déplacer le robot. Le robot se déplace tant que la méthode IsNotInArea est vraie.
	* \param [demo] : Instance de la classe RobotTetra à manipuler.
	* \return NULL.
	*/
	static void* marcherRobot(void* demo);
	// Taille mini piston 
	/**
	* \fn void nanoRobot();
	* \brief Methode réduisant au minimum la longueur des pistons du robot.
	*/
	void nanoRobot();
	
	// Taille maxi piston 
	/**
	* \fn void maxiRobot();
	* \brief Méthode étirant au maximum la longueur des pistons du robot.
	*/
	void maxiRobot();

	// Deplacer le robot
	/**
	* \fn void translate(const btVector3& to);
	* \brief Permet de faire une translation sur le robot. 
	* \param [to] : point représentant la destination du robot. Une fois la méthode exécutée, le centre de masse du robot sera situé au point [to].
	*/
	void translate(const btVector3& to);
	// JAZZ MODIF :  1 JUIN 2009 : 2h42
	// Lance des Threads
	//void StartThread(btScalar a, btScalar b, btScalar c);
	/**
	* \fn void StartThread(const btVector3 &ending);
	* \brief Méthode générant un thread pour déplacer le robot à un point donné.
	* \param [ending] : Point d'arrivé. Le robot se dirige vers ce dernier.
	*/
	void StartThread(btVector3 ending);

	// JAZZ MODIF : 1 JUIN 2009 : 11h52
	/**
	* \fn void Deplacement(unsigned char key);
	* \brief Déplace le robot en fonction de la touche appuyée passée en paramètre.
		Les déplacements peuvent être locaux ( etirement d'un piston ) ou généraux (déplacement de toute la structure vers un point).
	* \param [key] : touche appuyée.
	*/
	void Deplacement(unsigned char key);
};

#endif /* ROBOT_TETRA */
