/**
 * \file ActionPiston.h
 * \brief Définition de la classe abstraite Robot.
 *Cette classe contiendra tout les éléments du robot ainsi que les actions associes au robot.
 *Comme les robots peuvent etre differents, les actions sont des methodes VIRTUELLES PURES
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef PHYSICROBOT_H
#define PHYSICROBOT_H

#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicComponent.h"
#include "PhysicEdge.h"
#include "PhysicVertex.h"

/**
 * \class PhysicRobot
 * \brief composition du robot 
 */
class PhysicRobot{

public:
	// ATTRIBUTS
	btAlignedObjectArray<PhysicVertex *> Sommets; /**< Sommets du robots */

	btAlignedObjectArray<PhysicEdge *> Arcs; /**< Arcs du robots */

	int id; /**< identifieur du robot */

public:	
	// METHODE
	/**
	* \fn PhysicRobot();
	* \brief Constructeur de la classe PhysicRobot
	*/
	PhysicRobot();
	/**
	* \fn virtual ~PhysicRobot();
	* \brief Destructeur de la classe PhysicRobot
	*/
	virtual ~PhysicRobot();

	/**
	* \fn int getID();
	* \brief getter
	* \return id
	*/
	int getID();
 
 	/**
	* \fn btAlignedObjectArray<PhysicVertex *> getSommets();
	* \brief getter
	* \return Sommets
	*/
	btAlignedObjectArray<PhysicVertex *> getSommets();

 	/**
	* \fn PhysicVertex *getSommet(int i);
	* \brief getter
	* \return Sommets[i]
	*/
	PhysicVertex *getSommet(int i);
 	/**
	* \fn btAlignedObjectArray<PhysicEdge *> getArcs();
	* \brief getter
	* \return Arcs
	*/
	btAlignedObjectArray<PhysicEdge *> getArcs();

 	/**
	* \fn PhysicEdge *getArc(int i);
	* \brief getter
	* \return Arcs[i]
	*/
	PhysicEdge *getArc(int i);

 	/**
	* \fn virtual void translate(const btVector3& to) = 0;
	* \brief pour translater la position du robot
	*/
	virtual void translate(const btVector3& to) = 0;

 	/**
	* \fn virtual btVector3 getCenterOfMassPosition()
	* \brief getter
	* \return le centre de gravité du robot
	*/
	virtual btVector3 getCenterOfMassPosition() = 0;
};

#endif /* Robot */
