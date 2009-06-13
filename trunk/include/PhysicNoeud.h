//  @ Project : Tetrabot
//  @ File Name : PhysicNoeud.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file PhysicNoeud.h
 * \brief D�finition d'un noeud de robot.
 * \author Frozen Brains
 * \version 0.1
 */
//-----------------------------------------------------------------------------

#ifndef PHYSICNOEUD_H
#define PHYSICNOEUD_H

#include <cstdio>
#include "LinearMath/btIDebugDraw.h"
#include "btBulletDynamicsCommon.h"
#include "characteristics.h"
#include "PhysicPiston.h"
#include "PhysicVertex.h"
#include "BulletCollision/CollisionShapes/btConvexInternalShape.h"
/**
 * \class PhysicNoeud
 * \brief Repr�sentation d'un noeud de robot. Ce noeud peut avoir n'importe quelle forme, mais est constitu� d'un seul objet( rigide ) physique.
 */
class PhysicNoeud: public PhysicVertex
{
protected:

	btConvexInternalShape* shapeNoeud;/**< shapeNoeud : forme d'un noeud selon le moteur physique Bullet.*/

	btRigidBody* bodyNoeud;/**< bodyNoeud : objet rigide d'un noeud selon le moteur physique Bullet.*/

public:
	//Constructeur de la classe PhysicNoeud pour Ogre
	/**
	 * \fn PhysicNoeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse);
	 * \brief Constructeur de la classe PhysicNoeud en relation avec le moteur graphique Ogre.
	 * \param [ownerWorld] :  description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 * \param [nodeOgre] : noeud de sc�ne d'Ogre repr�sentant grapghiquement le noeud.
	 * \param [forme] : forme souhait� que le noeud doit avoir selon le moteur physique Bullet.
	 * \param [positionOffset] : position initiale du noeud.
	 * \param [masse] : poids du noeud.
	 */
	PhysicNoeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse);

	//Constructeur de la classe PhysicNoeud pour Bullet
	/**
	 * \fn PhysicNoeud(btDynamicsWorld *ownerWorld,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse);
	 * \brief Constructeur de la classe PhysicNoeud.
	 * \param [ownerWorld] :  description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 * \param [forme] : forme souhait� que le noeud doit avoir selon le moteur physique Bullet.
	 * \param [positionOffset] : position initiale du noeud.
	 * \param [masse] : poids du noeud.
	 */
	PhysicNoeud(btDynamicsWorld *ownerWorld,btConvexInternalShape* forme,const btVector3 & offset, btScalar masse);
	
	//Destructeur de la classe
	/** 
	* \fn ~PhysicNoeud();
	* \brief Destructeur
	*/
	~PhysicNoeud();

	// Methode pour obtenir le centre de masse
	/**
	* \fn btVector3 getCenterOfMassPosition();
	* \brief M�thode calculant le centre de masse du noeud (surcharge de la classe Composant).
		Le centre de masse est le centre de masse de l'objet physique.
	* \return Centre de masse du noeud.
	*/
	btVector3 getCenterOfMassPosition();

	// Retourne le Body de l objet
	/**
	* \fn btRigidBody* getBody();
	* \brief getter
	* \return Objet rigide repr�sentant le noeud.
	*/
	btRigidBody* getBody();

	//Parametre le Body de l objet
	/**
	* \fn void setBody(btRigidBody* body);
	* \brief setter
	* \param [body] : nouveau objet repr�sentant le noeud.
	* \deprecated La cr�ation de l'objet rigide s'effectue dans le constructeur. 
	*/
	void setBody(btRigidBody* body);

	// Retourne le ShapeNoeud de l objet
	/**
	* \fn btConvexInternalShape* getShapeNoeud();
	* \brief getter
	* \return Forme du noeud selon le moteur physique Bullet.
	*/
	btConvexInternalShape* getShapeNoeud();

	//Parametre le ShapeNoeud de l objet
	/**
	* \fn void setShapeNoeud(btConvexInternalShape* shape);
	* \brief setter
	* \param [shape] : nouvelle forme du noeud.
	*/
	void setShapeNoeud(btConvexInternalShape* shape);

	/**
	* \fn int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ);
	* \brief M�thode permettant de lier au noeud un arc. 
		Deux attributs d�crivent deux angles permettant de faire une rotation autour du noeud.
		Ainsi on peut lier l'arc � n'importe quel point de la surface du noeud.
		Il est � noter que l'on effectue une rotation suivant l'axe Y en premier, puis suivant l'axe Z.
		
	* \param [edge] :  arc � lier au noeud.
	* \ [extremitee] : charact�re d�signant une des extr�mit�es de l'arc � lier.
	* \ [rotationY] : angle en radian de rotation autour de l'axe Y.
	* \ [rotationZ] : angle en radian de rotation autour de l'axe Z.
	*/
	int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ);

	// Methode pour translater l objet
	/**
	* \fn void translate(const btVector3& to);
	* \brief M�thode effectuant une translation du noeud. 
	* \param [to] : point repr�sentant la destination du centre de masse du noeud.
		Une fois la m�thode ex�cut�e, le centre de masse du noeud sera situ� au point [to].
	*/
	void translate(const btVector3& to);
};
#endif
