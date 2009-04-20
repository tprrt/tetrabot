
#include "WorldPhysic.h"
//----------------------------------------------------------------------------------
#include "cd_wavefront.h"
#include "ConvexBuilder.h"
#include "ConvexDecomposition.h"

#include "btBulletDynamicsCommon.h"

#include "LinearMath/btQuickprof.h"
#include "LinearMath/btIDebugDraw.h"
#include "LinearMath/btGeometryUtil.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"
//----------------------------------------------------------------------------------



WorldPhysic::WorldPhysic(btVector3& worldMin,btVector3& worldMax,btVector3& gravite)
{
	static int nbInstance = 0;
	if(nbInstance==0)
	{
		m_collisionConfiguration = new btDefaultCollisionConfiguration();
		m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	
		m_overlappingPairCache = new btAxisSweep3(worldMin,worldMax);

	#if SLIDER_DEMO_USE_ODE_SOLVER
		m_constraintSolver = new btOdeQuickstepConstraintSolver();
	#else
		m_constraintSolver = new btSequentialImpulseConstraintSolver();
	#endif
		m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_overlappingPairCache,m_constraintSolver,m_collisionConfiguration);
		//	wp->getSolverInfo().m_numIterations = 20; // default is 10
		this->m_gravite = gravite;
		m_dynamicsWorld->setGravity(gravite);
		
		nbInstance++;
	}
}

/*void WorldPhysic::initGround(const char* filename)
{
	
	// Création d'un sol
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(1.F),btScalar(50.)));
	m_collisionShapes.push_back(groundShape);
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-6,0));
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);	
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0,myMotionState,groundShape,btVector3(0,0,0));
	m_ground = new btRigidBody(rbInfo);
	this->m_dynamicsWorld->addRigidBody(m_ground);
	

}*/

void WorldPhysic::setGravite(btVector3& newGravite)
{
	this->m_dynamicsWorld->setGravity(newGravite);
	this->m_gravite = newGravite;
}

btVector3 WorldPhysic::getGravite(){ return this->m_gravite;}





























void WorldPhysic::initGround(const char* filename)
{
	ConvexDecomposition::WavefrontObj wo;

	btVector3	centroid=btVector3(0,0,0);
	btVector3   convexDecompositionObjectOffset(10,0,0);
	unsigned int tcount = wo.loadObj(filename);


#ifdef USE_PARALLEL_DISPATCHER
	m_dynamicsWorld->getDispatchInfo().m_enableSPU = true;
#endif //USE_PARALLEL_DISPATCHER

	class MyConvexDecomposition : public ConvexDecomposition::ConvexDecompInterface
	{
		WorldPhysic*	world;
		btVector3 centroid;
		
		public:

		btAlignedObjectArray<btConvexHullShape*> m_convexShapes;
		btAlignedObjectArray<btVector3> m_convexCentroids;

		MyConvexDecomposition (FILE* outputFile,WorldPhysic* worldPhysic,btVector3& centre)
			:world(worldPhysic),
				mBaseCount(0),
			mHullCount(0),
			mOutputFile(outputFile),
			centroid(centre)

		{
		}
		
			virtual void ConvexDecompResult(ConvexDecomposition::ConvexResult &result)
			{

				btTriangleMesh* trimesh = new btTriangleMesh();
				world->m_trimeshes.push_back(trimesh);

				btVector3 localScaling(6.f,6.f,6.f);

				//export data to .obj
				printf("ConvexResult. ");
				if (mOutputFile)
				{
					fprintf(mOutputFile,"## Hull Piece %d with %d vertices and %d triangles.\r\n", mHullCount, result.mHullVcount, result.mHullTcount );

					fprintf(mOutputFile,"usemtl Material%i\r\n",mBaseCount);
					fprintf(mOutputFile,"o Object%i\r\n",mBaseCount);

					for (unsigned int i=0; i<result.mHullVcount; i++)
					{
						const float *p = &result.mHullVertices[i*3];
						fprintf(mOutputFile,"v %0.9f %0.9f %0.9f\r\n", p[0], p[1], p[2] );
					}

					//calc centroid, to shift vertices around center of mass
					centroid.setValue(0,0,0);

					btAlignedObjectArray<btVector3> vertices;
					if ( 1 )
					{
						//const unsigned int *src = result.mHullIndices;
						for (unsigned int i=0; i<result.mHullVcount; i++)
						{
							btVector3 vertex(result.mHullVertices[i*3],result.mHullVertices[i*3+1],result.mHullVertices[i*3+2]);
							vertex *= localScaling;
							centroid += vertex;
							
						}
					}

					centroid *= 1.f/(float(result.mHullVcount) );

					if ( 1 )
					{
						//const unsigned int *src = result.mHullIndices;
						for (unsigned int i=0; i<result.mHullVcount; i++)
						{
							btVector3 vertex(result.mHullVertices[i*3],result.mHullVertices[i*3+1],result.mHullVertices[i*3+2]);
							vertex *= localScaling;
							vertex -= centroid ;
							vertices.push_back(vertex);
						}
					}
					
			

					if ( 1 )
					{
						const unsigned int *src = result.mHullIndices;
						for (unsigned int i=0; i<result.mHullTcount; i++)
						{
							unsigned int index0 = *src++;
							unsigned int index1 = *src++;
							unsigned int index2 = *src++;


							btVector3 vertex0(result.mHullVertices[index0*3], result.mHullVertices[index0*3+1],result.mHullVertices[index0*3+2]);
							btVector3 vertex1(result.mHullVertices[index1*3], result.mHullVertices[index1*3+1],result.mHullVertices[index1*3+2]);
							btVector3 vertex2(result.mHullVertices[index2*3], result.mHullVertices[index2*3+1],result.mHullVertices[index2*3+2]);
							vertex0 *= localScaling;
							vertex1 *= localScaling;
							vertex2 *= localScaling;
							
							vertex0 -= centroid;
							vertex1 -= centroid;
							vertex2 -= centroid;


							trimesh->addTriangle(vertex0,vertex1,vertex2);

							index0+=mBaseCount;
							index1+=mBaseCount;
							index2+=mBaseCount;
							
							fprintf(mOutputFile,"f %d %d %d\r\n", index0+1, index1+1, index2+1 );
						}
					}

					float mass = 1.f;
					//float collisionMargin = 0.01f;

//this is a tools issue: due to collision margin, convex objects overlap, compensate for it here:
//#define SHRINK_OBJECT_INWARDS 1
#ifdef SHRINK_OBJECT_INWARDS

					
					std::vector<btVector3> planeEquations;
					btGeometryUtil::getPlaneEquationsFromVertices(vertices,planeEquations);

					std::vector<btVector3> shiftedPlaneEquations;
					for (int p=0;p<planeEquations.size();p++)
					{
						btVector3 plane = planeEquations[p];
						plane[3] += 5*collisionMargin;
						shiftedPlaneEquations.push_back(plane);
					}
					std::vector<btVector3> shiftedVertices;
					btGeometryUtil::getVerticesFromPlaneEquations(shiftedPlaneEquations,shiftedVertices);

					
					btConvexHullShape* convexShape = new btConvexHullShape(&(shiftedVertices[0].getX()),shiftedVertices.size());
					
#else //SHRINK_OBJECT_INWARDS
					
					btConvexHullShape* convexShape = new btConvexHullShape(&(vertices[0].getX()),vertices.size());
#endif 

					convexShape->setMargin(btScalar(0.01));
					m_convexShapes.push_back(convexShape);
					m_convexCentroids.push_back(centroid);
					world->m_collisionShapes.push_back(convexShape);
					mBaseCount+=result.mHullVcount; // advance the 'base index' counter.


				}
			}

			int   	mBaseCount;
  			int		mHullCount;
			FILE*	mOutputFile;

	};

	if (tcount)
	{
		btTriangleMesh* trimesh = new btTriangleMesh();
		m_trimeshes.push_back(trimesh);

		btVector3 localScaling(1.f,1.f,1.f);
		
		int i;
		for ( i=0;i<wo.mTriCount;i++)
		{
			int index0 = wo.mIndices[i*3];
			int index1 = wo.mIndices[i*3+1];
			int index2 = wo.mIndices[i*3+2];

			btVector3 vertex0(wo.mVertices[index0*3], wo.mVertices[index0*3+1],wo.mVertices[index0*3+2]);
			btVector3 vertex1(wo.mVertices[index1*3], wo.mVertices[index1*3+1],wo.mVertices[index1*3+2]);
			btVector3 vertex2(wo.mVertices[index2*3], wo.mVertices[index2*3+1],wo.mVertices[index2*3+2]);
			
			vertex0 *= localScaling;
			vertex1 *= localScaling;
			vertex2 *= localScaling;

			trimesh->addTriangle(vertex0,vertex1,vertex2);
		}

		
		btConvexShape* tmpConvexShape = new btConvexTriangleMeshShape(trimesh);
	
		printf("old numTriangles= %d\n",wo.mTriCount);
		printf("old numIndices = %d\n",wo.mTriCount*3);
		printf("old numVertices = %d\n",wo.mVertexCount);
		
		printf("reducing vertices by creating a convex hull\n");

		//create a hull approximation
		btShapeHull* hull = new btShapeHull(tmpConvexShape);
		btScalar margin = tmpConvexShape->getMargin();
		hull->buildHull(margin);
		tmpConvexShape->setUserPointer(hull);
		
		
		printf("new numTriangles = %d\n", hull->numTriangles ());
		printf("new numIndices = %d\n", hull->numIndices ());
		printf("new numVertices = %d\n", hull->numVertices ());
		
		btConvexHullShape* convexShape = new btConvexHullShape();
		for (i=0;i<hull->numVertices();i++)
		{
			convexShape->addPoint(hull->getVertexPointer()[i]);	
		}

		delete tmpConvexShape;
		delete hull;



		m_collisionShapes.push_back(convexShape);

		float mass = 1.f;
		
/*		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(0,2,0));

		localCreateRigidBody(mass, startTransform,convexShape);
		
		bool useQuantization = true;
		btCollisionShape* concaveShape = new btBvhTriangleMeshShape(trimesh,useQuantization);
		startTransform.setOrigin(convexDecompositionObjectOffset);
		localCreateRigidBody(0.f,startTransform,concaveShape);

		m_collisionShapes.push_back (concaveShape);
*/
	}
			

	if (tcount)
	{

		char outputFileName[512];
  		strcpy(outputFileName,filename);
  		char *dot = strstr(outputFileName,".");
  		if ( dot ) 
			*dot = 0;
		strcat(outputFileName,"_convex.obj");
  		FILE* outputFile = fopen(outputFileName,"wb");
				
		unsigned int depth = 5;
		float cpercent     = 5;
		float ppercent     = 15;
		unsigned int maxv  = 16;
		float skinWidth    = 0.0;

		printf("WavefrontObj num triangles read %i\n",tcount);
		ConvexDecomposition::DecompDesc desc;
		desc.mVcount       =	wo.mVertexCount;
		desc.mVertices     = wo.mVertices;
		desc.mTcount       = wo.mTriCount;
		desc.mIndices      = (unsigned int *)wo.mIndices;
		desc.mDepth        = depth;
		desc.mCpercent     = cpercent;
		desc.mPpercent     = ppercent;
		desc.mMaxVertices  = maxv;
		desc.mSkinWidth    = skinWidth;

		MyConvexDecomposition	convexDecomposition(outputFile,this,centroid);
		desc.mCallback = &convexDecomposition;
		
		

		//convexDecomposition.performConvexDecomposition(desc);

		ConvexBuilder cb(desc.mCallback);
		cb.process(desc);
		
		
		
		// creation d'un SOL
		
		{
			btCompoundShape* compound = new btCompoundShape();
			m_collisionShapes.push_back (compound);

			btTransform trans;
			trans.setIdentity();
			for (int i=0;i<convexDecomposition.m_convexShapes.size();i++)
			{
				
				btVector3 centroid2 = convexDecomposition.m_convexCentroids[i];
				trans.setOrigin(centroid2);
				btConvexHullShape* convexShape = convexDecomposition.m_convexShapes[i];
				compound->addChildShape(trans,convexShape);
			}
			trans.setOrigin(-convexDecompositionObjectOffset);


			btDefaultMotionState* myMotionState = new btDefaultMotionState(trans);	
			btRigidBody::btRigidBodyConstructionInfo rbInfo(0,myMotionState,compound,btVector3(0,0,0));
			m_ground = new btRigidBody(rbInfo);
			this->m_dynamicsWorld->addRigidBody(m_ground);


//			localCreateRigidBody( btScalar(0.F), trans,compound);
		}

		
		if (outputFile)
			fclose(outputFile);


	}


	
}