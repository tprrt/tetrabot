#ifndef PHYSICVERTEX_H
#define PHYSICVERTEX_H
#include "PhysicComponent.h"
/**
 * \file PhysicVertex.h
 * \brief D�finition d'un sommet de robot. Les sommets sont utilis�s pour relier plusieurs arcs.
 * \author Frozen Brains
 * \version 0.1
 */
 
 /**
 * \class PhysicVertex
 * \brief Repr�sentation abstraite d'un sommet ( vertex ) de robot, composant reliant plusieurs arcs entre eux.
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
	* \brief M�thode virtuelle pure permettant de lier au sommet un arc. 
		Cette m�thode devra �tre impl�ment�e dans les classes d�riv�es car les arcs n'ont pas forc�ment la m�me structure.
		Deux attributs d�crivent deux angles permettant de faire une rotation autour du sommet.
		Ainsi on peut lier l'arc � n'importe quel point de la surface du sommet.
		Il est � noter que l'on effectue une rotation suivant l'axe Y en premier, puis suivant l'axe Z.
		
	* \param [edge] :  arc � lier au sommet.
	* \ [extremitee] : charact�re d�signant une des extr�mit�es de l'arc � lier.
	* \ [rotationY] : angle en radian de rotation autour de l'axe Y.
	* \ [rotationZ] : angle en radian de rotation autour de l'axe Z.
	*/
	virtual int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ) =0;
};
#endif