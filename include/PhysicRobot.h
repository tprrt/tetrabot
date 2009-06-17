/**
 * \file PhysicRobot.h
 * \brief D�finition de la classe abstraite Robot.
	Cette classe contiendra tout les �l�ments du robot ainsi que les actions associes au robot.
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
	* \brief Constructeur de la classe PhysicRobot. Attribut un identificateur unique de mani�re automatique.
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
	* \param [i] : i�me sommet demand�.
	* \return Retourne le i�me sommet du tableau de sommets.
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
	* \param [i] : i�me arc demand�.
	* \return I�me arc composant le robot.
	*/
	PhysicEdge *getArc(int i);

 	/**
	* \fn virtual void translate(const btVector3& to) = 0;
	* \brief Permet de faire une translation sur le robot. 
		Cette m�thode est laiss� virtuelle pure car les robots peuvent �tre diff�rents de par leurs composants.
	* \param [to] : point repr�sentant la destination du robot. Une fois la m�thode ex�cut�e, le centre de masse du robot sera situ� au point [to].
	*/
	virtual void translate(const btVector3& to) = 0;

 	/**
	* \fn virtual btVector3 getCenterOfMassPosition() = 0;
	* \brief M�thode virtuelle pure calculant le centre de masse du robot.
		Cette m�thode est virtuelle pure car les composants des robots n'ont pas forc�ment la m�me dynamique.
	* \return Centre de masse du robot.
	*/
	virtual btVector3 getCenterOfMassPosition() = 0;
};

#endif /* Robot */
