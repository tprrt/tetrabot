//  @ Project : Tetrabot
//  @ File Name : PhysicPiston.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file PhysicPiston.h
 * \brief D�finition d'un piston.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef PHYSICPISTON_H
#define PHYSICPISTON_H

#include <cstdio>

#include "LinearMath/btIDebugDraw.h"
#include "Threads.h"
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/ConstraintSolver/btSliderConstraint.h"
#include "Application.h"
#include "characteristics.h"
#include "PhysicEdge.h"

/**
 * \class PhysicPiston
 * \brief Cette classe repr�sente un piston d�finit par deux extr�mit�es li�es entre eux par une contrainte lin�aire. 
	Le piston modifie son �tirement par le biais d'un moteur.
 */
class PhysicPiston: public PhysicEdge
{
protected:
	// Attributs:
	btScalar tailleMin;/**< tailleMin : longueur minimale du piston.*/

	btScalar tailleMax;/**< tailleMax : longueur maximale du piston. */

	btScalar velocite;/**< velocite : vitesse du piston. */

	bool estBloque;/**< estBloque : bool�en indicant si le piston est bloqu� ou non.*/

	// Forme des deux objets aux extr�mit�es du piston
	btBoxShape* shapeA;/**< shapeA : forme de l'extr�mit�e A du piston. */
	btBoxShape* shapeB;/**< shapeB : forme de l'extr�mit�e B du piston. */

	// Corps des deux objets aux extr�mit�es du piston
	btRigidBody* bodyA;/**< bodyA : objet rigide repr�sentant l'extr�mit�e A du piston. */
	btRigidBody* bodyB;/**< bodyB : objet rigide repr�sentant l'extr�mit�e B du piston. */

	// Contraintes liant les deux extr�mit�es du piston
	btSliderConstraint* contrainte;/**< contrainte : contrainte liant les deux extr�mit�es du piston. */

	// Contraintes coniques liant une boule a une extremite de piston
	btConeTwistConstraint* coneA;/**< coneA : contrainte conique liant l'extr�mit�e A du piston � un sommet (classe Vertex). */
	btConeTwistConstraint* coneB;/**< coneB : contrainte conique liant l'extr�mit�e B du piston � un sommet (classe Vertex). */

public:
	// Les Constructeurs
	// Constructeur par copie
	// PhysicPiston(PhysicPiston* piston);

	// Pour Ogre
	/**
	 * \fn PhysicPiston(btDynamicsWorld* ownerWorld,Ogre::SceneNode* nodeOgre, const btVector3& positionOffset,btScalar min,btScalar max,btScalar vitesse);
	 * \brief Constructeur de la classe PhysicPiston en relation avec le moteur graphique Ogre.
	 * \param [ownerWorld] :  description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 * \param [nodeOgre] : noeud de sc�ne d'Ogre repr�sentant grapghiquement le piston.
	 * \param [positionOffset] : position initiale du piston.
	 * \param [min] : longueur minimale du piston.
	 * \param [max] : longueur maximale du piston.
	  * \param [vitesse] : vitesse du moteur dupiston.
	 */
	PhysicPiston(btDynamicsWorld* ownerWorld,Ogre::SceneNode* nodeOgre, const btVector3& positionOffset,btScalar min,btScalar max,btScalar vitesse);

	// Pour GL
	/**
	 * \fn PhysicPiston(btDynamicsWorld* ownerWorld,Ogre::SceneNode* nodeOgre, const btVector3& positionOffset,btScalar min,btScalar max,btScalar vitesse);
	 * \brief Constructeur de la classe PhysicPiston.
	 * \param [ownerWorld] :  description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 * \param [positionOffset] : position initiale du piston.
	 * \param [min] : longueur minimale du piston.
	 * \param [max] : longueur maximale du piston.
	  * \param [vitesse] : vitesse du moteur dupiston.
	 */
	PhysicPiston(btDynamicsWorld* ownerWorld, const btVector3& positionOffset,btScalar min,btScalar max,btScalar vitesse);

	// Le Destructeur
	/** 
	* \fn virtual ~PhysicPiston();
	* \brief Destructeur
	*/
	~PhysicPiston();

	// methode retournant le centre de gravite
	/**
	* \fn btVector3 getCenterOfMassPosition();
	* \brief M�thode calculant le centre de masse du piston (surcharge de la classe Composant).
		Le centre de masse est le milieu des centres de masses des extr�mit�es du piston.
	* \return Centre de masse du piston.
	*/
	btVector3 getCenterOfMassPosition();

	// les getters & setters
	/**
	 * \fn btSliderConstraint* getContrainte();
	 * \brief getter
	* \return Contrainte lin�aire liant les deux extr�mit�es du piston.
	 */
	btSliderConstraint* getContrainte();

	/**
	 * \fn void setContrainte(btSliderConstraint* constraint);
	 * \brief setter
	* \param [constraint] : nouvelle contrainte � appliquer sur le piston.
	* \deprecated La contrainte lin�aire du piston est cr��e dans le constructeur.
	 */
	void setContrainte(btSliderConstraint* constraint);

	/**
	 * \fn btRigidBody* getBodyA();
	 * \brief getter
	* \return Objet rigide repr�sentant l'extr�mit�e A du piston.
	 */
	btRigidBody* getBodyA();

	/**
	 * \fn void setBodyA(btRigidBody* body);
	 * \brief setter
	* \param [body] : nouvel objet rigide pour d�finir l'extr�mit�e A du piston.
	* \deprecated L'objet rigide se cr�e dans le constructeur.
	 */
	void setBodyA(btRigidBody* body);

	/**
	 * \fn btRigidBody* getBodyB();
	 * \brief getter
	* \return Objet rigide repr�sentant l'extr�mit�e B du piston.
	 */
	btRigidBody* getBodyB();

	/**
	 * \fn void setBodyB(btRigidBody* body);
	 * \brief setter
	* \param [body] :  nouvel objet rigide pour d�finir l'extr�mit�e B du piston.
	* \deprecated L'objet rigide se cr�e dans le constructeur.
	 */
	void setBodyB(btRigidBody* body);

	/**
	 * \fn btBoxShape* getShapeA();
	 * \brief getter
	* \return Forme de l'extr�mit�e A du piston.
	 */
	btBoxShape* getShapeA();

	/**
	 * \fn void setShapeA(btBoxShape* newShape);
	 * \brief setter
	* \param [newShape] : nouvelle forme de l'objet repr�sentant l'extr�mit�e A du piston.
	* \deprecated La forme de l'extr�mit�e A du piston est cr��e dans le constructeur.
	 */
	void setShapeA(btBoxShape* newShape);

	/**
	 * \fn btBoxShape* getShapeB();
	 * \brief getter
	* \return Forme de l'extr�mit�e A du piston.
	 */
	btBoxShape* getShapeB();

	/**
	 * \fn void setShapeB(btBoxShape* newShape);
	 * \brief setter
	* \param [newShape] : nouvelle forme de l'objet repr�sentant l'extr�mit�e B du piston.
	* \deprecated La forme de l'extr�mit�e B du piston est cr��e dans le constructeur.
	 */
	void setShapeB(btBoxShape* newShape);

	/**
	 * \fn btScalar getTailleMin();
	 * \brief getter
	* \return Taille minimale du piston.
	 */
	btScalar getTailleMin();

	/**
	 * \fn btScalar getTailleMax();
	 * \brief getter
	* \return Taille maximale du piston.
	 */
	btScalar getTailleMax();

	/**
	 * \fn void setTailleMin(btScalar tailleVoulu);
	 * \brief setter
	* \param [tailleVoulu] : nouvelle taille minimale du piston.
	 */
	void setTailleMin(btScalar tailleVoulu);

	/**
	 * \fn void setTailleMax(btScalar tailleVoulu);
	 * \brief setter
	* \param [tailleVoulu] : nouvelle taille maximale du piston.
	 */
	void setTailleMax(btScalar tailleVoulu);

	/**
	 * \fn btConeTwistConstraint* getConeA();
	 * \brief getter
	* \return contrainte conique liant l'extr�mit�e A du piston � un sommet (classe Vertex) ou NULL si la liaison n'a pas encore �t� effectu�e.
	 */
	btConeTwistConstraint* getConeA();

	/**
	 * \fn btConeTwistConstraint* getConeB();
	 * \brief getter
	* \return contrainte conique liant l'extr�mit�e B du piston � un sommet (classe Vertex) ou NULL si la liaison n'a pas encore �t� effectu�e.
	 */
	btConeTwistConstraint* getConeB();

	/**
	 * \fn void setConeA(btConeTwistConstraint* contrainteConique);
	 * \brief setter
	* \param [contrainteConique] : contrainte conique liant l'extr�mit�e A du piston � un sommet (classe Vertex). 
	 */
	void setConeA(btConeTwistConstraint* contrainteConique);

	/**
	 * \fn void setConeB(btConeTwistConstraint* contrainteConique);
	 * \brief setter
	* \param [contrainteConique] : contrainte conique liant l'extr�mit�e B du piston � un sommet (classe Vertex). 
	 */
	void setConeB(btConeTwistConstraint* contrainteConique);

	// methode permettant de connaitre la taille du piston
	/**
	 * \fn btScalar getLength();
	 * \brief M�thode calculant la taille courante du piston.
	* \return taille courante du piston.
	 */
	btScalar getLength();

	// methode permettant de faire bouger un piston � la taille voulu
	/**
	 * \fn int actionnerEdge(btScalar tailleVoulu);
	 * \brief M�thode permettant de changer la taille du piston.
	 * \param [tailleVoulu] :  taille souhait�e.
	 * \return Une valeur diff�rente de z�ro signifie un disfonctionnement du piston.
	 */
	int actionnerEdge(btScalar tailleVoulu);

	// methode permettant de bloquer le piston
	/**
	* \fn void lock();
	* \brief M�thode  blocquant le piston � sa taille courante.
	*/
	void lock();

	// methode permettant de debloquer le piston
	/**
	* \fn void unlock();
	* \brief M�thode  d�blocquant le piston.
	*/
	void unlock();

	// methode permettant connaitre le statut du piston (bloqu� ou non)
	/**
	 * \fn btScalar getLength();
	 * \brief M�thode retournant le statut du piston
	* \return True si le piston est bloqu�, False dans le cas contraire.
	 */
	bool getEstBloque();

	/**
	* \fn void translate(const btVector3& to);
	* \brief M�thode effectuant une translation du piston (translation effectu�e sur chacune des deux extr�mit�es). 
	* \param [to] : point repr�sentant la destination du centre de masse du piston.
		Une fois la m�thode ex�cut�e, le centre de masse du piston sera situ� au point [to].
	*/
	void translate(const btVector3 &to);
};
#endif /* PISTON_H */
