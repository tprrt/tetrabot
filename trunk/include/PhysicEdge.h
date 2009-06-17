//  @ Project : Tetrabot
//  @ File Name : PhysicEdge.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file PhysicEdge.h
 * \brief D�finition d'un arc de robot. Les arcs sont des composant capables de changer de taille.
 * \author Frozen Brains
 * \version 0.1
 */
 
#ifndef PHYSICEDGE_H
#define PHYSICEDGE_H

#include "PhysicComponent.h"
/**
 * \class PhysicEdge
 * \brief Repr�sentation, de mani�re abstraite, d'un arc de robot.  Un arc est un composant capable de changer de taille.
 */
class PhysicEdge : virtual public PhysicComponent
{
public:
	//Constructeur de la classe PhysicEdge
	/**
	 * \fn PhysicEdge(btDynamicsWorld *world);
	 * \brief Constructeur de la classe PhysicEdge
	 * \param [world] :  description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 */
	PhysicEdge(btDynamicsWorld *world): PhysicComponent(world)
	{
	}
	
	//Destructeur de la classe PhysicEdge
	/** 
	* \fn virtual ~PhysicEdge();
	* \brief Destructeur
	*/
	virtual ~PhysicEdge()
	{
	}
	
	// Methode pour actionner un edge
	/**
	 * \fn virtual int actionnerEdge(btScalar tailleVoulu) = 0;
	 * \brief M�thode virtuelle pure permettant de changer la taille de l'arc.
	 * \param [tailleVoulu] :  taille souhait�e.
	 * \return Une valeur diff�rente de z�ro signifirai un disfonctionnement de l'arc.
	 */
	virtual int actionnerEdge(btScalar tailleVoulu) = 0;
	
	/**
	* \fn virtual void lock() = 0;
	* \brief M�thode virtuelle pure blocquant l'arc � sa taille courante. Cette m�thode d�pand de la repr�sentation d'un arc de robot.
	*/
	virtual void lock() = 0;
	
	/**
	* \fn virtual void unlock() = 0;
	* \brief M�thode virtuelle pure d�verouillant l'arc. Cette m�thode d�pand de la repr�sentation d'un arc de robot.
	*/
	virtual void unlock() = 0;
};
#endif
