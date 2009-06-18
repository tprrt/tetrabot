/**
 * \file PhysicNoeud.h
 * \brief Définition d'un nœud de robot.
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
 * \brief Représentation d'un nœud de robot. Ce nœud peut avoir n'importe quelle forme, mais est constitué d'un seul objet (rigide) physique.
 */
class PhysicNoeud: public PhysicVertex
{
protected:

	btConvexInternalShape* shapeNoeud;/**< forme d'un nœud selon le moteur physique Bullet.*/

	btRigidBody* bodyNoeud;/**< objet rigide d'un nœud selon le moteur physique Bullet.*/

public:
	//Constructeur de la classe PhysicNoeud pour Ogre
	/**
	 * \fn PhysicNoeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse)
	 * \brief Constructeur de la classe PhysicNoeud en relation avec le moteur graphique Ogre.
	 * \param ownerWorld description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 * \param nodeOgre noeud de scène d'Ogre représentant grapghiquement le noeud.
	 * \param forme forme souhaitée que le noeud doit avoir selon le moteur physique Bullet.
	 * \param positionOffset position initiale du noeud.
	 * \param masse poids du noeud.
	 */
	PhysicNoeud(btDynamicsWorld *ownerWorld,Ogre::SceneNode * nodeOgre,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse);

	//Constructeur de la classe PhysicNoeud pour Bullet
	/**
	 * \fn PhysicNoeud(btDynamicsWorld *ownerWorld,btConvexInternalShape* forme,const btVector3 & offset,btScalar masse)
	 * \brief Constructeur de la classe PhysicNoeud.
	 * \param ownerWorld description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 * \param forme forme souhaité que le noeud doit avoir selon le moteur physique Bullet.
	 * \param positionOffset position initiale du nœud.
	 * \param masse poids du nœud.
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
	 * \fn btVector3 getCenterOfMassPosition()
	 * \brief Méthode calculant le centre de masse du nœud (surcharge de la classe Composant).
	 * Le centre de masse est le centre de masse de l'objet physique.
	 * \return Centre de masse du nœud.
	 */
	btVector3 getCenterOfMassPosition();

	// Retourne le Body de l objet
	/**
	 * \fn btRigidBody* getBody()
	 * \brief getter
	 * \return Objet rigide représentant le noeud.
	 */
	btRigidBody* getBody();

	//Parametre le Body de l objet
	/**
	 * \fn void setBody(btRigidBody* body)
	 * \brief setter
	 * \param body nouvel objet représentant le noeud.
	 * \deprecated La création de l'objet rigide s'effectue dans le constructeur.
	 */
	void setBody(btRigidBody* body);

	// Retourne le ShapeNoeud de l objet
	/**
	 * \fn btConvexInternalShape* getShapeNoeud();
	 * \brief getter
	 * \return Forme du nœud selon le moteur physique Bullet.
	 */
	btConvexInternalShape* getShapeNoeud();

	//Parametre le ShapeNoeud de l objet
	/**
	 * \fn void setShapeNoeud(btConvexInternalShape* shape);
	 * \brief setter
	 * \param shape nouvelle forme du nœud.
	 */
	void setShapeNoeud(btConvexInternalShape* shape);

	/**
	 * \fn int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ);
	 * \brief Méthode permettant de lier un arc au nœud.
	 * Deux attributs décrivent deux angles permettant de faire une rotation autour du nœud.
	 * Ainsi on peut lier l'arc à n'importe quel point de la surface du nœud.
	 * Il est à noter que l'on effectue une rotation suivant l'axe Y en premier, puis suivant l'axe Z.
	 * \param edge arc à lier au nœud.
	 * \param extremitee charactère désignant une des extrémitées de l'arc à lier.
	 * \ rotationY angle en radians de rotation autour de l'axe Y.
	 * \ rotationZ angle en radians de rotation autour de l'axe Z.
	 */
	int linkEdge(PhysicEdge* edge, char extremitee, btScalar rotationY, btScalar rotationZ);

	// Methode pour translater l objet
	/**
	 * \fn void translate(const btVector3& to);
	 * \brief Méthode effectuant une translation du noeud.
	 * \param to point représentant la destination du centre de masse du noeud.
	 * Une fois la méthode exécutée, le centre de masse du noeud sera situé au point [to].
	 */
	void translate(const btVector3& to);
};
#endif
