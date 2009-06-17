//  @ Project : Tetrabot
//  @ File Name : PhysicPiston.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file PhysicPiston.h
 * \brief Définition d'un piston.
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
 * \brief Cette classe représente un piston définit par deux extrémitées liées entre eux par une contrainte linéaire. 
	Le piston modifie son étirement par le biais d'un moteur.
 */
class PhysicPiston: public PhysicEdge
{
protected:
	// Attributs:
	btScalar tailleMin;/**< tailleMin : longueur minimale du piston.*/

	btScalar tailleMax;/**< tailleMax : longueur maximale du piston. */

	btScalar velocite;/**< velocite : vitesse du piston. */

	bool estBloque;/**< estBloque : booléen indicant si le piston est bloqué ou non.*/

	// Forme des deux objets aux extrémitées du piston
	btBoxShape* shapeA;/**< shapeA : forme de l'extrémitée A du piston. */
	btBoxShape* shapeB;/**< shapeB : forme de l'extrémitée B du piston. */

	// Corps des deux objets aux extrémitées du piston
	btRigidBody* bodyA;/**< bodyA : objet rigide représentant l'extrémitée A du piston. */
	btRigidBody* bodyB;/**< bodyB : objet rigide représentant l'extrémitée B du piston. */

	// Contraintes liant les deux extrémitées du piston
	btSliderConstraint* contrainte;/**< contrainte : contrainte liant les deux extrémitées du piston. */

	// Contraintes coniques liant une boule a une extremite de piston
	btConeTwistConstraint* coneA;/**< coneA : contrainte conique liant l'extrémitée A du piston à un sommet (classe Vertex). */
	btConeTwistConstraint* coneB;/**< coneB : contrainte conique liant l'extrémitée B du piston à un sommet (classe Vertex). */

public:
	// Les Constructeurs
	// Constructeur par copie
	// PhysicPiston(PhysicPiston* piston);

	// Pour Ogre
	/**
	 * \fn PhysicPiston(btDynamicsWorld* ownerWorld,Ogre::SceneNode* nodeOgre, const btVector3& positionOffset,btScalar min,btScalar max,btScalar vitesse);
	 * \brief Constructeur de la classe PhysicPiston en relation avec le moteur graphique Ogre.
	 * \param [ownerWorld] :  description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 * \param [nodeOgre] : noeud de scène d'Ogre représentant grapghiquement le piston.
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
	* \brief Méthode calculant le centre de masse du piston (surcharge de la classe Composant).
		Le centre de masse est le milieu des centres de masses des extrémitées du piston.
	* \return Centre de masse du piston.
	*/
	btVector3 getCenterOfMassPosition();

	// les getters & setters
	/**
	 * \fn btSliderConstraint* getContrainte();
	 * \brief getter
	* \return Contrainte linéaire liant les deux extrémitées du piston.
	 */
	btSliderConstraint* getContrainte();

	/**
	 * \fn void setContrainte(btSliderConstraint* constraint);
	 * \brief setter
	* \param [constraint] : nouvelle contrainte à appliquer sur le piston.
	* \deprecated La contrainte linéaire du piston est créée dans le constructeur.
	 */
	void setContrainte(btSliderConstraint* constraint);

	/**
	 * \fn btRigidBody* getBodyA();
	 * \brief getter
	* \return Objet rigide représentant l'extrémitée A du piston.
	 */
	btRigidBody* getBodyA();

	/**
	 * \fn void setBodyA(btRigidBody* body);
	 * \brief setter
	* \param [body] : nouvel objet rigide pour définir l'extrémitée A du piston.
	* \deprecated L'objet rigide se crée dans le constructeur.
	 */
	void setBodyA(btRigidBody* body);

	/**
	 * \fn btRigidBody* getBodyB();
	 * \brief getter
	* \return Objet rigide représentant l'extrémitée B du piston.
	 */
	btRigidBody* getBodyB();

	/**
	 * \fn void setBodyB(btRigidBody* body);
	 * \brief setter
	* \param [body] :  nouvel objet rigide pour définir l'extrémitée B du piston.
	* \deprecated L'objet rigide se crée dans le constructeur.
	 */
	void setBodyB(btRigidBody* body);

	/**
	 * \fn btBoxShape* getShapeA();
	 * \brief getter
	* \return Forme de l'extrémitée A du piston.
	 */
	btBoxShape* getShapeA();

	/**
	 * \fn void setShapeA(btBoxShape* newShape);
	 * \brief setter
	* \param [newShape] : nouvelle forme de l'objet représentant l'extrémitée A du piston.
	* \deprecated La forme de l'extrémitée A du piston est créée dans le constructeur.
	 */
	void setShapeA(btBoxShape* newShape);

	/**
	 * \fn btBoxShape* getShapeB();
	 * \brief getter
	* \return Forme de l'extrémitée A du piston.
	 */
	btBoxShape* getShapeB();

	/**
	 * \fn void setShapeB(btBoxShape* newShape);
	 * \brief setter
	* \param [newShape] : nouvelle forme de l'objet représentant l'extrémitée B du piston.
	* \deprecated La forme de l'extrémitée B du piston est créée dans le constructeur.
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
	* \return contrainte conique liant l'extrémitée A du piston à un sommet (classe Vertex) ou NULL si la liaison n'a pas encore été effectuée.
	 */
	btConeTwistConstraint* getConeA();

	/**
	 * \fn btConeTwistConstraint* getConeB();
	 * \brief getter
	* \return contrainte conique liant l'extrémitée B du piston à un sommet (classe Vertex) ou NULL si la liaison n'a pas encore été effectuée.
	 */
	btConeTwistConstraint* getConeB();

	/**
	 * \fn void setConeA(btConeTwistConstraint* contrainteConique);
	 * \brief setter
	* \param [contrainteConique] : contrainte conique liant l'extrémitée A du piston à un sommet (classe Vertex). 
	 */
	void setConeA(btConeTwistConstraint* contrainteConique);

	/**
	 * \fn void setConeB(btConeTwistConstraint* contrainteConique);
	 * \brief setter
	* \param [contrainteConique] : contrainte conique liant l'extrémitée B du piston à un sommet (classe Vertex). 
	 */
	void setConeB(btConeTwistConstraint* contrainteConique);

	// methode permettant de connaitre la taille du piston
	/**
	 * \fn btScalar getLength();
	 * \brief Méthode calculant la taille courante du piston.
	* \return taille courante du piston.
	 */
	btScalar getLength();

	// methode permettant de faire bouger un piston à la taille voulu
	/**
	 * \fn int actionnerEdge(btScalar tailleVoulu);
	 * \brief Méthode permettant de changer la taille du piston.
	 * \param [tailleVoulu] :  taille souhaitée.
	 * \return Une valeur différente de zéro signifie un disfonctionnement du piston.
	 */
	int actionnerEdge(btScalar tailleVoulu);

	// methode permettant de bloquer le piston
	/**
	* \fn void lock();
	* \brief Méthode  blocquant le piston à sa taille courante.
	*/
	void lock();

	// methode permettant de debloquer le piston
	/**
	* \fn void unlock();
	* \brief Méthode  déblocquant le piston.
	*/
	void unlock();

	// methode permettant connaitre le statut du piston (bloqué ou non)
	/**
	 * \fn btScalar getLength();
	 * \brief Méthode retournant le statut du piston
	* \return True si le piston est bloqué, False dans le cas contraire.
	 */
	bool getEstBloque();

	/**
	* \fn void translate(const btVector3& to);
	* \brief Méthode effectuant une translation du piston (translation effectuée sur chacune des deux extrémitées). 
	* \param [to] : point représentant la destination du centre de masse du piston.
		Une fois la méthode exécutée, le centre de masse du piston sera situé au point [to].
	*/
	void translate(const btVector3 &to);
};
#endif /* PISTON_H */
