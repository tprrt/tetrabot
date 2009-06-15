/**
 * \file RobotWheels.h
 * \brief Robot bi-pyramidale dans lequel les deux pyramides sont liées entre elles par un piston.
	Ce robot a la forme de deux roues d'où son nom.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef ROBOTWHEELS_H
#define ROBOTWHEELS_H

#include "PhysicRobot.h"
#include "PhysicNoeud.h"
#include "PhysicPiston.h"

#include "ActionPiston.h"

/**
* \class RobotWheels
* \brief Robot bi-pyramidale dans lequel les deux pyramides sont liées entre elles par un piston.
	Le robot est composé de pistons et de noeuds sphériques hormis pour les deux noeuds des sommets des piramides,
	qui sont cylindriques.
	Par ailleur, les pistons ont des caractéristiques différentes les uns des autres.
*/
class RobotWheels: public PhysicRobot
{

public:	
	btRigidBody* bodyCube;
	btVector3* end;
	
public:
	// Test avec GL
	/**
	* \fn RobotWheels(btDynamicsWorld* world,const btVector3& posInit);
	* \brief Constructeur du robot.
	* \param [world] : définition du monde selon le moteur physique Bullet.
	* \param [posInit] : position initiale du robot: une translation est donc effectuée pour que le robot soit précisement à ce point.
	*/
	RobotWheels(btDynamicsWorld* world,const btVector3& posInit);

	/**
	* \fn btVector3 getCenterOfMassPosition();
	* \brief Méthode calculant le centre de masse du robot.
	* \return Centre de masse du robot.
	*/
	btVector3 getCenterOfMassPosition();
	
	// Deplacer le robot
	/**
	* \fn void translate(const btVector3& to);
	* \brief Permet de faire une translation sur le robot. 
	* \param [to] : point représentant la destination du robot. Une fois la méthode exécutée, le centre de masse du robot sera situé au point [to].
	*/
	void translate(const btVector3& to);
};

#endif /* ROBOTWHEELS_H */