#ifndef PHYSICVERTEX_H
#define PHYSICVERTEX_H
#include "PhysicComponent.h"
/**
 * \file PhysicVertex.h
 * \brief Définition d'un sommet de robot. Les sommets sont utilisés pour relier plusieurs arcs.
 * \author Frozen Brains
 * \version 0.1
 */
 
 /**
 * \class PhysicVertex
 * \brief Représentation abstraite d'un sommet ( vertex ) de robot, composant reliant plusieurs arcs entre eux.
 */
class PhysicVertex: virtual public PhysicComponent
{
public:
	/**
	* \fn PhysicVertex(btDynamicsWorld *world):PhysicComponent(world);
	* \brief Constructeur.
	* \param [world] :  description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	*/
	PhysicVertex(btDynamicsWorld *world):PhysicComponent(world)
	{
	}
	// link a Vertex to an Edge
	/**
	* \fn virtual int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ) =0;
	* \brief Méthode virtuelle pure permettant de lier au sommet un arc. 
		Cette méthode devra être implémentée dans les classes dérivées car les arcs n'ont pas forcément la même structure.
		Deux attributs décrivent deux angles permettant de faire une rotation autour du sommet.
		Ainsi on peut lier l'arc à n'importe quel point de la surface du sommet.
		Il est à noter que l'on effectue une rotation suivant l'axe Y en premier, puis suivant l'axe Z.
		
	* \param [edge] :  arc à lier au sommet.
	* \ [extremitee] : charactère désignant une des extrémitées de l'arc à lier.
	* \ [rotationY] : angle en radian de rotation autour de l'axe Y.
	* \ [rotationZ] : angle en radian de rotation autour de l'axe Z.
	*/
	virtual int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ) =0;
};
#endif