/**
 * \file PhysicWorld.h
 * \brief D�finition du monde englobant la d�finition du monde dynamique selon le moteur physique Bullet ainsi que la d�finition du terrain.
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
 * \brief Repr�sentation du monde et du terrain.
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
	* \brief Constructeur d�finissant le monde selon le moteur physique Bullet sans terrain.
		Pour ajouter un terrain dans le monde, utiliser la m�thode initGround.
	* \param [info] : classe contenant les informations necessaires � la cr�ation du monde � savoir la gravit� et les limites du monde physique virtuel.
	*/
	PhysicWorld(const WorldInfo info);

	/**
	* \fn void initGround(const char* filename);
	* \brief M�thode permettant de cr�er un terrain ( objet rigide de masse nulle selon le moteur physique Bullet ) � partir d'une meshe WaveFrontObject ( .obj )
	* \param [filename] : Chemin absolu de la meshe.
	* \bug Le moteur physique Bullet impose des objets rigides de moins de 50 faces. 
		Le probl�me est au niveau de l'approximation de la meshe qui n'est pas satisfaisant.
	*/
	void initGround(const char* filename);

	/**
	* \fn void setGravite(const btVector3& newGravite);
	* \brief setter permettant d'affecter au monde une nouvelle gravit�e, remplacant l'ancienne.
	* \param [newGravite] : vecteur d�finissant la nouvelle gravit�e � appliquer.
	*/
	void setGravite(const btVector3& newGravite);

	/**
	* \fn btVector3 getGravite();
	* \brief getter
	* \return Gravit� du monde.
	*/
	btVector3 getGravite();
};


#endif /* PHYSIC_WORLD_H */
