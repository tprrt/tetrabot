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
	PhysicWorld(const WorldInfo info);

	void initGround(const char* filename);

	void setGravite(const btVector3& newGravite);

	btVector3 getGravite();
};


#endif /* PHYSIC_WORLD_H */
