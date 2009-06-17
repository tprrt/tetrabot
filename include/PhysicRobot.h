/**
 * \file PhysicRobot.h
 * \brief Définition de la classe abstraite Robot.
	Cette classe contiendra tout les éléments du robot ainsi que les actions associes au robot.
	Comme les robots peuvent etre differents, les actions sont des methodes VIRTUELLES PURES
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
	btAlignedObjectArray<PhysicVertex *> Sommets; /**< Tableau de Sommets du robots */

	btAlignedObjectArray<PhysicEdge *> Arcs; /**< Tableau des Arcs du robots */

	int id; /**< identifieur du robot */

public:	
	// METHODE
	/**
	* \fn PhysicRobot();
	* \brief Constructeur de la classe PhysicRobot. Attribut un identificateur unique de manière automatique.
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
	* \return Identificateur du robot.
	*/
	int getID();
 
 	/**
	* \fn btAlignedObjectArray<PhysicVertex *> getSommets();
	* \brief getter
	* \return Tableau de Sommets du robot.
	*/
	btAlignedObjectArray<PhysicVertex *> getSommets();

 	/**
	* \fn PhysicVertex *getSommet(int i);
	* \brief getter
	* \param [i] : ième sommet demandé.
	* \return Retourne le ième sommet du tableau de sommets.
	*/
	PhysicVertex *getSommet(int i);
 	/**
	* \fn btAlignedObjectArray<PhysicEdge *> getArcs();
	* \brief getter
	* \return Tableau des arcs composant le robot.
	*/
	btAlignedObjectArray<PhysicEdge *> getArcs();

 	/**
	* \fn PhysicEdge *getArc(int i);
	* \brief getter
	* \param [i] : ième arc demandé.
	* \return Ième arc composant le robot.
	*/
	PhysicEdge *getArc(int i);

 	/**
	* \fn virtual void translate(const btVector3& to) = 0;
	* \brief Permet de faire une translation sur le robot. 
		Cette méthode est laissé virtuelle pure car les robots peuvent être différents de par leurs composants.
	* \param [to] : point représentant la destination du robot. Une fois la méthode exécutée, le centre de masse du robot sera situé au point [to].
	*/
	virtual void translate(const btVector3& to) = 0;

 	/**
	* \fn virtual btVector3 getCenterOfMassPosition() = 0;
	* \brief Méthode virtuelle pure calculant le centre de masse du robot.
		Cette méthode est virtuelle pure car les composants des robots n'ont pas forcément la même dynamique.
	* \return Centre de masse du robot.
	*/
	virtual btVector3 getCenterOfMassPosition() = 0;
};

#endif /* Robot */
