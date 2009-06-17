/**
 * \file RobotTetra.h
 * \brief Robot � la forme t�trahedrique.
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
* \brief Classe cr�ant un robot t�trah�drique compos� de noeuds sph�riques et de pistons.
*/
class RobotTetra: public PhysicRobot
{
protected:

	ActionPiston*	action[6];/** < action : Tableau d'Action utilis�es par les pistons du robot.*/

public:	
	btRigidBody* bodyCube;
	btVector3* end;/** < end : Point d'int�raction avec le robot. */
	
public:
	// Test avec GL
	/**
	* \fn RobotWheels(btDynamicsWorld* world,const btVector3& posInit);
	* \brief Constructeur du robot.
	* \param [world] : d�finition du monde selon le moteur physique Bullet.
	* \param [posInit] : position initiale du robot: une translation est donc effectu�e pour que le robot soit pr�cisement � ce point.
	*/
	RobotTetra(btDynamicsWorld* world,const btVector3& posInit);

	// Test avec Ogre
	/**
	* \fn RobotWheels(btDynamicsWorld* world,const btVector3& posInit);
	* \brief Constructeur du robot en relation avec le moteur graphique Ogre. 
		Seul les noeuds du robot sont en relations avec Ogre: ils sont suffisants pour repr�senter le robot sous Ogre.
	* \param [world] : d�finition du monde selon le moteur physique Bullet.
	* \param [scene] : Sc�ne du moteur Ogre contenant toutes les repr�sentations des noeuds du robot t�trah�drique.
	* \param [posInit] : position initiale du robot: une translation est donc effectu�e pour que le robot soit pr�cisement � ce point.
	*/
	RobotTetra(btDynamicsWorld* world,Ogre::SceneManager * scene,const btVector3& posInit);

	/**
	* \fn btVector3 getCenterOfMassPosition();
	* \brief M�thode calculant le centre de masse du robot.
	* \return Centre de masse du robot.
	*/
	btVector3 getCenterOfMassPosition();
	
	/**
	* \fn bool IsNotInArea(const btVector3 &G,const btVector3 &end2);
	* \brief D�termine si les deux points sont distant d'au moins 5 unit�es de mesure.
	* \param [G] : Premier point.
	* \param [end2] : Second point.
	* \return Vrai si la distance est sup�rieur � 5. Faux sinon.
	*/
	bool IsNotInArea(const btVector3 &G,const btVector3 &end2);
	// methode pour faire marcher le robot
	/**
	* \fn static void* marcherRobot(void* demo);
	* \brief M�thode utilis�e par un thread pour d�placer le robot. Le robot se d�place tant que la m�thode IsNotInArea est vraie.
	* \param [demo] : Instance de la classe RobotTetra � manipuler.
	* \return NULL.
	*/
	static void* marcherRobot(void* demo);
	// Taille mini piston 
	/**
	* \fn void nanoRobot();
	* \brief Methode r�duisant au minimum la longueur des pistons du robot.
	*/
	void nanoRobot();
	
	// Taille maxi piston 
	/**
	* \fn void maxiRobot();
	* \brief M�thode �tirant au maximum la longueur des pistons du robot.
	*/
	void maxiRobot();

	// Deplacer le robot
	/**
	* \fn void translate(const btVector3& to);
	* \brief Permet de faire une translation sur le robot. 
	* \param [to] : point repr�sentant la destination du robot. Une fois la m�thode ex�cut�e, le centre de masse du robot sera situ� au point [to].
	*/
	void translate(const btVector3& to);
	// JAZZ MODIF :  1 JUIN 2009 : 2h42
	// Lance des Threads
	//void StartThread(btScalar a, btScalar b, btScalar c);
	/**
	* \fn void StartThread(const btVector3 &ending);
	* \brief M�thode g�n�rant un thread pour d�placer le robot � un point donn�.
	* \param [ending] : Point d'arriv�. Le robot se dirige vers ce dernier.
	*/
	void StartThread(btVector3 ending);

	// JAZZ MODIF : 1 JUIN 2009 : 11h52
	/**
	* \fn void Deplacement(unsigned char key);
	* \brief D�place le robot en fonction de la touche appuy�e pass�e en param�tre.
		Les d�placements peuvent �tre locaux ( etirement d'un piston ) ou g�n�raux (d�placement de toute la structure vers un point).
	* \param [key] : touche appuy�e.
	*/
	void Deplacement(unsigned char key);
};

#endif /* ROBOT_TETRA */
