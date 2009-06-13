/**
 * \file PhysicWorld.h
 * \brief Définition du monde englobant la définition du monde dynamique selon le moteur physique Bullet ainsi que la définition du terrain.
 * \author Frozen Brains
 * \version 0.1
 */
 
#ifndef PHYSIC_WORLD_H
#define PHYSIC_WORLD_H

#include "cd_wavefront.h"
#include "ConvexBuilder.h"
#include "ConvexDecomposition.h"

#include "btBulletDynamicsCommon.h"

#include "LinearMath/btQuickprof.h"
#include "LinearMath/btIDebugDraw.h"
#include "LinearMath/btGeometryUtil.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

#include "WorldInfo.h"
/**
 * \class PhysicWorld
 * \brief Représentation du monde et du terrain.
 */
class PhysicWorld
{
public:
	// Attributs
	btRigidBody* bodyCube;

	btDiscreteDynamicsWorld * m_dynamicsWorld;

	btVector3 m_gravite;

	btRigidBody* m_ground;

	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	btAlignedObjectArray<btTriangleMesh*> m_trimeshes;

	class btBroadphaseInterface*	m_overlappingPairCache;

	class btCollisionDispatcher*	m_dispatcher;

	class btConstraintSolver*	m_constraintSolver;

	class btDefaultCollisionConfiguration* m_collisionConfiguration;

public:
	/**
	* \fn PhysicWorld(const WorldInfo info);
	* \brief Constructeur définissant le monde selon le moteur physique Bullet sans terrain.
		Pour ajouter un terrain dans le monde, utiliser la méthode initGround.
	* \param [info] : classe contenant les informations necessaires à la création du monde à savoir la gravité et les limites du monde physique virtuel.
	*/
	PhysicWorld(const WorldInfo info);

	/**
	* \fn void initGround(const char* filename);
	* \brief Méthode permettant de créer un terrain ( objet rigide de masse nulle selon le moteur physique Bullet ) à partir d'une meshe WaveFrontObject ( .obj )
	* \param [filename] : Chemin absolu de la meshe.
	* \bug Le moteur physique Bullet impose des objets rigides de moins de 50 faces. 
		Le problème est au niveau de l'approximation de la meshe qui n'est pas satisfaisant.
	*/
	void initGround(const char* filename);

	/**
	* \fn void setGravite(const btVector3& newGravite);
	* \brief setter permettant d'affecter au monde une nouvelle gravitée, remplacant l'ancienne.
	* \param [newGravite] : vecteur définissant la nouvelle gravitée à appliquer.
	*/
	void setGravite(const btVector3& newGravite);

	/**
	* \fn btVector3 getGravite();
	* \brief getter
	* \return Gravité du monde.
	*/
	btVector3 getGravite();
};


#endif /* PHYSIC_WORLD_H */
