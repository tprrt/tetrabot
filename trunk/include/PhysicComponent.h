//  @ Project : Tetrabot
//  @ File Name : PhysicComponent.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file PhysicComponent.h
 * \brief D�finition d'un composant de robot.
 * \author Frozen Brains
 * \version 0.1
 */
 
#ifndef PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H

#include "btBulletDynamicsCommon.h"

#include "TetraMotionState.h"
/**
 * \class PhysicComponent
 * \brief Repr�sentation abstraite d'un composant de robot.
 */
class PhysicComponent {

protected:
	// id : identifieur de l objet
	int id;/**< id : identifiant du composant */
	// World : le monde 
	btDynamicsWorld *World;/**< monde : monde virtuel d�crivant la physique selon le moteur bullet  auquel le composant est soumis. */

public:
	// Constructeur de la classe PhysicComponent
	/**
	 * \fn PhysicComponent(btDynamicsWorld *world);
	 * \brief Constructeur de la classe PhysicComponent
	 * \param [world] :  description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 */
	PhysicComponent(btDynamicsWorld *world):World(world)
	{
	};
	
	// Destructeur de la classe PhysicComponent
	/** 
	* \fn virtual ~PhysicComponent();
	* \brief Destructeur
	*/
	virtual ~PhysicComponent()
	{
	};
	
	// Retourne l identifieur de l objet
	/**
	 * \fn int getID();
	 * \brief getter
	* \return Identifiant du composant.
	 */
	int getID();
	
	// Retourne le monde 
	/**
	 * \fn btDynamicsWorld* getWorld();
	 * \brief getter
	* \return Description du monde physique selon le moteur Bullet auquel le composant est soumis.
	 */
	btDynamicsWorld* getWorld();
	
	// Parametre le monde
	/**
	 * \fn void setWorld(btDynamicsWorld* newWorld);
	 * \brief setter
	* \param[newWorld] : nouvele description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 */
	void setWorld(btDynamicsWorld* newWorld);
	
	// Cr�ation d'un corps pour Ogre
	/**
	 * \fn btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre);
	 * \brief M�thode permettant de cr�er un objet rigide selon le moteur physique Bullet, et en relation avec le moteur graphique Ogre.
	* \param [mass] : masse de l'abjet.
	* \param [startTransform] : transformation ( rotation + translation) initiale de l'objet.
	* \param [shape] : forme de l'objet rigide selon Bullet.
	* \param [nodeOgre] : noeud de sc�ne du moteur graphique Ogre correspondant � l'objet.
	* \return L'objet rigide cr�� avec les param�tres.
	 */
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre);

	// Cr�ation d'un corps pour GL
	/**
	 * \fn btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);
	 * \brief M�thode permettant de cr�er un objet rigide selon le moteur physique Bullet.
	* \param [mass] : masse de l'abjet.
	* \param [startTransform] : transformation ( rotation + translation) initiale de l'objet.
	* \param [shape] : forme de l'objet rigide selon Bullet.
	* \return L'objet rigide cr�� avec les param�tres.
	 */
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);

	// methode a implementer: retourne le centre de gravite
	/**
	* \fn virtual btVector3 getCenterOfMassPosition() = 0;
	* \brief M�thode virtuelle pure calculant le centre de masse du composant.
	* \return Centre de masse du composant.
	*/
	virtual btVector3 getCenterOfMassPosition() = 0;

	// methode a implanter: translation du composant
	/**
	* \fn virtual void translate(const btVector3& to) = 0;
	* \brief M�thode virtuelle pure effectuant une translation du composant.
	* \param [to] : point repr�sentant la destination du composant. Une fois la m�thode ex�cut�e, le centre de masse du composant sera situ� au point [to].
	*/
	virtual void translate(const btVector3& to) = 0;
};

#endif /* PHYSIC_COMPONENT_H */
