#ifndef WORLD_PHYSIC_H
#define WORLD_PHYSIC_H

#include "cd_wavefront.h"
#include "ConvexBuilder.h"
#include "ConvexDecomposition.h"

#include "btBulletDynamicsCommon.h"

#include "LinearMath/btQuickprof.h"
#include "LinearMath/btIDebugDraw.h"
#include "LinearMath/btGeometryUtil.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

class WorldPhysic
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
	WorldPhysic(const btVector3& worldMin,const btVector3& worldMax,const btVector3& gravite);

	virtual ~WorldPhysic();

	void initGround(const char* filename);

	void setGravite(const btVector3& newGravite);

	btVector3 getGravite();
};


#endif /* WORLD_PHYSIC_H */
