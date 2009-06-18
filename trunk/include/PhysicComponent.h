/**
 * \file PhysicComponent.h
 * \brief Définition d'un composant de robot.
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H

#include "btBulletDynamicsCommon.h"

#include "TetraMotionState.h"
/**
 * \class PhysicComponent
 * \brief Représentation abstraite d'un composant de robot.
 */
class PhysicComponent {

protected:
	// id : identifieur de l objet
	int id;/**< identifiant du composant */
	// World : le monde
	btDynamicsWorld *World;/**< monde virtuel décrivant la physique selon le moteur bullet auquel le composant est soumis. */

public:
	// Constructeur de la classe PhysicComponent
	/**
	 * \fn PhysicComponent(btDynamicsWorld *world)
	 * \brief Constructeur de la classe PhysicComponent
	 * \param world Description du monde physique selon le moteur Bullet auquel le composant sera soumis.
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
	 * \param newWorld nouvelle description du monde physique selon le moteur Bullet auquel le composant sera soumis.
	 */
	void setWorld(btDynamicsWorld* newWorld);

	// Création d'un corps pour Ogre
	/**
	 * \fn btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre)
	 * \brief Méthode permettant de créer un objet rigide selon le moteur physique Bullet, et en relation avec le moteur graphique Ogre.
	 * \param mass masse de l'abjet.
	 * \param startTransform transformation (rotation + translation) initiale de l'objet.
	 * \param shape forme de l'objet rigide selon Bullet.
	 * \param nodeOgre noeud de scène du moteur graphique Ogre correspondant à l'objet.
	 * \return L'objet rigide créé avec les paramètres.
	 */
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape,Ogre::SceneNode* nodeOgre);

	// Création d'un corps pour GL
	/**
	 * \fn btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
	 * \brief Méthode permettant de créer un objet rigide selon le moteur physique Bullet.
	 * \param mass masse de l'abjet.
	 * \param startTransform transformation (rotation + translation) initiale de l'objet.
	 * \param shape forme de l'objet rigide selon Bullet.
	 * \return L'objet rigide créé avec les paramètres.
	 */
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape);

	// methode a implementer: retourne le centre de gravite
	/**
	 * \fn virtual btVector3 getCenterOfMassPosition() = 0
	 * \brief Méthode virtuelle pure calculant le centre de masse du composant.
	 * \return Centre de masse du composant.
	 */
	virtual btVector3 getCenterOfMassPosition() = 0;

	// methode a implanter: translation du composant
	/**
	 * \fn virtual void translate(const btVector3& to) = 0
	 * \brief Méthode virtuelle pure effectuant une translation du composant.
	 * \param to point représentant la destination du composant. Une fois la méthode exécutée, le centre de masse du composant sera situé au point [to].
	 */
	virtual void translate(const btVector3& to) = 0;
};

#endif /* PHYSIC_COMPONENT_H */
