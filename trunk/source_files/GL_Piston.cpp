//-----------------------------------------------------------------------------
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btIDebugDraw.h"

#include "GLDebugDrawer.h"

#include "BMF_Api.h"
#include <stdio.h> //printf debugging

#include "GL_Piston.h"
#include "GL_ShapeDrawer.h"
#include "GlutStuff.h"

//Pour TEST
#include "AlgoGen_Tetra.h"


//-----------------------------------------------------------------------------

GL_Piston::GL_Piston()
{
	for(int i=0;i<6;i++)
	{
		action[i] = NULL;
	}
}
static void draw_axes(const btRigidBody& rb, const btTransform& frame)
{
	glBegin(GL_LINES);
	// draw world transform
	btVector3 from = rb.getWorldTransform().getOrigin();
	btVector3 to = from + rb.getWorldTransform().getBasis() * btVector3(5,0,0);
	// X in red
	glColor3f(255.0F, 0.0F, 0.0F);
	glVertex3d(from.getX(), from.getY(), from.getZ());
	glVertex3d(to.getX(), to.getY(), to.getZ());
	to = from + rb.getWorldTransform().getBasis() * btVector3(0,5,0);
	// Y in green
	glColor3f(0.0F, 255.0F, 0.0F);
	glVertex3d(from.getX(), from.getY(), from.getZ());
	glVertex3d(to.getX(), to.getY(), to.getZ());
	to = from + rb.getWorldTransform().getBasis() * btVector3(0,0,5);
	// Z in blue
	glColor3f(0.0F, 0.0F, 255.0F);
	glVertex3d(from.getX(), from.getY(), from.getZ());
	glVertex3d(to.getX(), to.getY(), to.getZ());
	// draw slider frame
	btTransform calc_frame = rb.getWorldTransform() * frame;
	from = calc_frame.getOrigin();
	to = from + calc_frame.getBasis() * btVector3(5,0,0);
	// X in red
	glColor3f(255.0F, 0.0F, 0.0F); 
	glVertex3d(from.getX(), from.getY(), from.getZ());
	glVertex3d(to.getX(), to.getY(), to.getZ());
	to = from + calc_frame.getBasis() * btVector3(0,5,0);
	// Y in green
	glColor3f(0.0F, 255.0F, 0.0F);
	glVertex3d(from.getX(), from.getY(), from.getZ());
	glVertex3d(to.getX(), to.getY(), to.getZ());
	to = from + calc_frame.getBasis() * btVector3(0,0,5);
	// Z in blue
	glColor3f(0.0F, 0.0F, 255.0F);
	glVertex3d(from.getX(), from.getY(), from.getZ());
	glVertex3d(to.getX(), to.getY(), to.getZ());
	glEnd();
} // draw_axes()

//-----------------------------------------------------------------------------

static void	drawSlider(btSliderConstraint* pSlider)
{
	//draw_axes(pSlider->getRigidBodyA(), pSlider->getFrameOffsetA());
	//draw_axes(pSlider->getRigidBodyB(), pSlider->getFrameOffsetB());

	// draw limits in white
	btVector3 from(pSlider->getLowerLinLimit(), 0, 0);
	btVector3 to(pSlider->getUpperLinLimit(), 0, 0);
	btTransform trans;
	if(pSlider->getUseLinearReferenceFrameA())
	{
		trans = pSlider->getRigidBodyA().getWorldTransform() * pSlider->getFrameOffsetA();
	}
	else
	{
		trans = pSlider->getRigidBodyB().getWorldTransform() * pSlider->getFrameOffsetB();
	}
	from = trans * from;
	to = trans * to;
	glBegin(GL_LINES);
	glColor3f(255.0F, 255.0F, 255.0F);
	glVertex3d(from.getX(), from.getY(), from.getZ());
	glVertex3d(to.getX(), to.getY(), to.getZ());
	glEnd();
} // drawSlider()


//-----------------------------------------------------------------------------

void GL_Piston::initPhysics()
{
	setTexturing(true);
	setShadows(true);

	setCameraDistance(26.f);

	// init world
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	btVector3 gravite = btVector3(0.,-9.8,0.);

	WorldPhysic* monde = new WorldPhysic(worldMin,worldMax,gravite);
	monde->initGround("./data/terrains/Sol.obj");
	
	m_collisionConfiguration = monde->m_collisionConfiguration;
	m_dispatcher = monde->m_dispatcher;
	m_overlappingPairCache = monde->m_overlappingPairCache;
	m_constraintSolver = monde->m_constraintSolver;
	m_dynamicsWorld = monde->m_dynamicsWorld;

	
/*	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_overlappingPairCache = new btAxisSweep3(worldMin,worldMax);

	#if SLIDER_DEMO_USE_ODE_SOLVER
		m_constraintSolver = new btOdeQuickstepConstraintSolver();
	#else
		m_constraintSolver = new btSequentialImpulseConstraintSolver();
	#endif
		m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_overlappingPairCache,m_constraintSolver,m_collisionConfiguration);
		//	wp->getSolverInfo().m_numIterations = 20; // default is 10
		m_dynamicsWorld->setGravity(gravite);

	// Création d'un sol
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.),btScalar(1.F),btScalar(50.)));
	m_collisionShapes.push_back(groundShape);
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-6,0));
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);	
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0,myMotionState,groundShape,btVector3(0,0,0));
	btRigidBody* m_ground = new btRigidBody(rbInfo);
	this->m_dynamicsWorld->addRigidBody(m_ground);
*/
	// Creation du robot
	this->robot = new Robot_Tetra(this->m_dynamicsWorld,btVector3(0,10,0));

	// Creation d'un controleur
	controleur = new ControleurRobot(this->robot,btScalar(M_PI),btScalar(8.F),btScalar(4.F));
	
	// Creation de AlgoGen_Tetra
	AlgoGen_Tetra* algo = new AlgoGen_Tetra(this->m_dynamicsWorld,6,10,10,1,1);
	algo->run();	

}

//-----------------------------------------------------------------------------

GL_Piston::~GL_Piston()
{
	//cleanup in the reverse order of creation/initialization
	int i;
	//removed/delete constraints
	for (i=m_dynamicsWorld->getNumConstraints()-1; i>=0 ;i--)
	{
		btTypedConstraint* constraint = m_dynamicsWorld->getConstraint(i);
		m_dynamicsWorld->removeConstraint(constraint);
		delete constraint;
	}
	//remove the rigidbodies from the dynamics world and delete them
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}
	//delete collision shapes
	for (int j=0;j<m_collisionShapes.size();j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		delete shape;
	}
	//delete dynamics world
	delete m_dynamicsWorld;
	//delete solver
	delete m_constraintSolver;
	//delete broadphase
	delete m_overlappingPairCache;
	//delete dispatcher
	delete m_dispatcher;
	delete m_collisionConfiguration;
}

//-----------------------------------------------------------------------------

void GL_Piston::clientMoveAndDisplay()
{
	
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

 	float dt = float(getDeltaTimeMicroseconds()) * 0.000001f;
	//printf("dt = %f: ",dt);
	
	{
	 	//during idle mode, just run 1 simulation step maximum
		int maxSimSubSteps = m_idle ? 1 : 1;
		if (m_idle)
			dt = 1.0/420.f;

		int numSimSteps = m_dynamicsWorld->stepSimulation(dt,maxSimSubSteps);

		//optional but useful: debug drawing
		m_dynamicsWorld->debugDrawWorld();
	
		bool verbose = false;
		if (verbose)
		{
			if (!numSimSteps)
				printf("Interpolated transforms\n");
			else
			{
				if (numSimSteps > maxSimSubSteps)
				{
					//detect dropping frames
					printf("Dropped (%i) simulation steps out of %i\n",numSimSteps - maxSimSubSteps,numSimSteps);
				} else
				{
					printf("Simulated (%i) steps\n",numSimSteps);
				}
			}
		}
	}
	renderme();

//	dessiner contraintes lienaires;
	for(int i=0;i<6;i++){
		if(robot->Arcs[i]!=NULL)
			drawSlider(robot->Arcs[i]->getContrainte());
	}

    glFlush();
    glutSwapBuffers();
}

//-----------------------------------------------------------------------------

void GL_Piston::displayCallback(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	if (m_dynamicsWorld)
		m_dynamicsWorld->debugDrawWorld();

//	dessiner contraintes lienaires;
	for(int i=0;i<6;i++){
		if(robot->Arcs[i]!=NULL)
			drawSlider(robot->Arcs[i]->getContrainte());
	}

	renderme();

    glFlush();
    glutSwapBuffers();
}

//-----------------------------------------------------------------------------
void GL_Piston::specialKeyboard(int key, int x, int y)	
{
	(void)x;
	(void)y;

	switch (key) 
	{
	case GLUT_KEY_F1:
		{
			printf("F1\n");
/*			// On va essayer de faire chuter le tetra:
			// piston 0 et 2 -> 6.2497F
			// piston 1 -> 8.F
			// piston 3 et 4 -> 3.F
			// piston 5 -> 4.2426F
			
			this->action[0] = new ActionPiston(robot->Arcs[1],btScalar(10.F)); 
			this->action[1] = new ActionPiston(robot->Arcs[3],btScalar(3.F));
			this->action[2] = new ActionPiston(robot->Arcs[4],btScalar(3.F));
			// piston 5 -> 8.F (normalement cela donne un echec!)
			this->action[3] = new ActionPiston(robot->Arcs[5],btScalar(8.F));
			// Optionnelles?
			this->action[4] = new ActionPiston(this->robot->Arcs[0],btScalar(6.2497F));
			this->action[5] = new ActionPiston(this->robot->Arcs[2],btScalar(6.2497F));

			for(int i=0;i<4;i++)
			{
				//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) actionThread,action[i], 0, &threadID);
				Thread((void*)action[i],actionThread);
			}
			robot->Arcs[4]->debloquerPiston();
			robot->Arcs[5]->debloquerPiston();
*/
			controleur->etapeSuivante();
			break;
		}

	case GLUT_KEY_F2:
		{
			printf("F2\n");
			// Tous les pistons a la taille maximale
			btScalar tailleTmp;
			for(int i=0;i<6;i++)
			{
				if(robot->Arcs[i]!=NULL)
				{
					tailleTmp = robot->Arcs[i]->getTailleMax()- robot->Arcs[i]->getLength();
					if(tailleTmp< 0)tailleTmp= -tailleTmp;
					if(tailleTmp> btScalar(0.1))
					{
						this->action[i] = new ActionPiston(robot->Arcs[i],robot->Arcs[i]->getTailleMax());
						//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) actionThread,action[i], 0, &threadID);
						Thread((void*)action[i],actionThread);
					}
				}
			}
			break;
		}
	case GLUT_KEY_F3:
		{
			printf("F3\n");
			// Tous les pistons a la taille maximale
			btScalar tailleTmp;
			for(int i=0;i<6;i++)
			{
				if(robot->Arcs[i]!=NULL)
				{
					tailleTmp = robot->Arcs[i]->getTailleMin()- robot->Arcs[i]->getLength();
					if(tailleTmp< 0)tailleTmp= -tailleTmp;
					if(tailleTmp> btScalar(0.1))
					{
						this->action[i] = new ActionPiston(robot->Arcs[i],robot->Arcs[i]->getTailleMin());
						//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)actionThread,action[i], 0, &threadID);
						Thread((void*)action[i],actionThread);
					}
				}
			}
			break;
		}
	case GLUT_KEY_F4:
		{
			printf("F4\n");
			// bloquer tous les pistons
			for(int i=0;i<6;i++)
			{
				if(robot->Arcs[i]!=NULL)
				{
					robot->Arcs[i]->bloquerPiston();
				}
			}
			break;
		}
	case GLUT_KEY_F5:
		{
			printf("F5\n");
			// bloquer tous les pistons
			for(int i=0;i<6;i++)
			{
				if(robot->Arcs[i]!=NULL)
				{
					robot->Arcs[i]->debloquerPiston();
				}
			}
			break;
		}
	case GLUT_KEY_F6:
		{
			printf("F6\n");
			// bloquer les 2 joints de chaque piston (ROTATION NULLE)
			for(int i=0;i<6;i++)
			{
				if(robot->Arcs[i]!=NULL)
				{
					robot->Arcs[i]->getConeA()->setLimit(0.F,0.F,0.F);
					robot->Arcs[i]->getConeB()->setLimit(0.F,0.F,0.F);
				}
			}
			break;
		}
		case GLUT_KEY_F7:
		{
			printf("F7\n");
			// Débloquer les 2 joints de chaque piston (ROTATION 360°)
			for(int i=0;i<6;i++)
			{
				if(robot->Arcs[i]!=NULL)
				{
					robot->Arcs[i]->getConeA()->setLimit(ANGLES_CONE,ANGLES_CONE,0.F);
					robot->Arcs[i]->getConeB()->setLimit(ANGLES_CONE,ANGLES_CONE,0.F);
				}
			}
			break;
		}
	case GLUT_KEY_END:
		{
			int numObj = getDynamicsWorld()->getNumCollisionObjects();
			if (numObj)
			{
				btCollisionObject* obj = getDynamicsWorld()->getCollisionObjectArray()[numObj-1];

				getDynamicsWorld()->removeCollisionObject(obj);
				btRigidBody* body = btRigidBody::upcast(obj);
				if (body && body->getMotionState())
				{
					delete body->getMotionState();					
				}
				delete obj;


			}
			break;
		}
	case GLUT_KEY_LEFT : stepLeft(); break;
	case GLUT_KEY_RIGHT : stepRight(); break;
	case GLUT_KEY_UP : stepFront(); break;
	case GLUT_KEY_DOWN : stepBack(); break;
	case GLUT_KEY_PAGE_UP : zoomIn(); break;
	case GLUT_KEY_PAGE_DOWN : zoomOut(); break;
	case GLUT_KEY_HOME : toggleIdle(); break;
	default:
		//        std::cout << "unused (special) key : " << key << std::endl;
		break;
	}

	glutPostRedisplay();

}


void GL_Piston::renderme()
{
	myinit();

	updateCamera();

	if (m_dynamicsWorld)
	{			
		if(m_enableshadows)
		{
			glClear(GL_STENCIL_BUFFER_BIT);
			glEnable(GL_CULL_FACE);
			renderscene(0);

			glDisable(GL_LIGHTING);
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_STENCIL_TEST);
			glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
			glStencilFunc(GL_ALWAYS,1,0xFFFFFFFFL);
			glFrontFace(GL_CCW);
			glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);
			renderscene(1);
			glFrontFace(GL_CW);
			glStencilOp(GL_KEEP,GL_KEEP,GL_DECR);
			renderscene(1);
			glFrontFace(GL_CCW);

			glPolygonMode(GL_FRONT,GL_FILL);
			glPolygonMode(GL_BACK,GL_FILL);
			glShadeModel(GL_SMOOTH);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_LIGHTING);
			glDepthMask(GL_TRUE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			glEnable(GL_CULL_FACE);
			glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

			glDepthFunc(GL_LEQUAL);
			glStencilFunc( GL_NOTEQUAL, 0, 0xFFFFFFFFL );
			glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
			glDisable(GL_LIGHTING);
			renderscene(2);
			glEnable(GL_LIGHTING);
			glDepthFunc(GL_LESS);
			glDisable(GL_STENCIL_TEST);
			glDisable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
			renderscene(0);
		}

		float xOffset = 10.f;
		float yStart = 20.f;
		float yIncr = 20.f;
		char buf[124];

		glDisable(GL_LIGHTING);
		glColor3f(0, 0, 0);

		if ((m_debugMode & btIDebugDraw::DBG_NoHelpText)==0)
		{
			setOrthographicProjection();

			showProfileInfo(xOffset,yStart,yIncr);

#ifdef USE_QUICKPROF


			if ( getDebugMode() & btIDebugDraw::DBG_ProfileTimings)
			{
				static int counter = 0;
				counter++;
				std::map<std::string, hidden::ProfileBlock*>::iterator iter;
				for (iter = btProfiler::mProfileBlocks.begin(); iter != btProfiler::mProfileBlocks.end(); ++iter)
				{
					char blockTime[128];
					sprintf(blockTime, "%s: %lf",&((*iter).first[0]),btProfiler::getBlockTime((*iter).first, btProfiler::BLOCK_CYCLE_SECONDS));//BLOCK_TOTAL_PERCENT));
					glRasterPos3f(xOffset,yStart,0);
					BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),blockTime);
					yStart += yIncr;

				}

			}
#endif //USE_QUICKPROF


			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"mouse to interact");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"space to reset");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"cursor keys and z,x to navigate");
			//sprintf(buf,"nombre de processus restant = [%d]",(nb_proc-nb_ProcDetruits));
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"h to toggle help text");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"q to quit");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"+- shooting speed = %10.2f",m_ShootBoxInitialSpeed);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
			
			// not yet hooked up again after refactoring...
			btVector3 Gravity = btVector3(0.,0.,0.);
			btVector3 b0 = btVector3(0.,0.,0.);
			btVector3 b1 = btVector3(0.,0.,0.);
			btVector3 b2 = btVector3(0.,0.,0.);
			btVector3 b3 = btVector3(0.,0.,0.);

			b0 =  robot->Sommets[0]->getCenterOfMassPosition();
			b1 =  robot->Sommets[1]->getCenterOfMassPosition();
			b2 =  robot->Sommets[2]->getCenterOfMassPosition();
			b3 =  robot->Sommets[3]->getCenterOfMassPosition();
			Gravity =  (b0+b1+b2+b3)*0.25;			
			
			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"Centre de Mass X:%f Y:%f Z:%f",Gravity.x(),Gravity.y(),Gravity.z());
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
			
			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"Centre de boule[0] X:%f Y:%f Z:%f",b0.x(),b0.y(),b0.z());
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
			
			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"Centre de boule[1] X:%f Y:%f Z:%f",b1.x(),b1.y(),b1.z());
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
			
			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"Centre de boule[2] X:%f Y:%f Z:%f",b2.x(),b2.y(),b2.z());
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
			
			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"Centre de boule[3] X:%f Y:%f Z:%f",b3.x(),b3.y(),b3.z());
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
			
			for(int j = 0; j<6;j++)
			{
				if( this->action[j] != NULL )
				{
					glRasterPos3f(xOffset,yStart,0);
					sprintf(buf,"Taille piston [%d] envisagee = %f courante = %f ",j,this->action[j]->getTailleVoulu(),robot->Arcs[j]->getLength());
					BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
					yStart += yIncr;
				}
			}
						
			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"F1: Creer un mouvement.");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"F2:longueur MAX pour tous les pistons.");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"F3:longueur MIN pour tous les pistons.");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"F4: bloquer tous les pistons.");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"F5: debloquer tous les pistons.");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"F6: rotation nulle de tous les contraintes Coniques.");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"F7: rotation totale de tous les contraintes Coniques.");
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
			
#ifdef SHOW_NUM_DEEP_PENETRATIONS


			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"gNumDeepPenetrationChecks = %d",gNumDeepPenetrationChecks);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"gNumGjkChecks= %d",gNumGjkChecks);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
			
			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"gNumClampedCcdMotions = %d",gNumClampedCcdMotions);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"gNumSplitImpulseRecoveries= %d",gNumSplitImpulseRecoveries);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"gNumAlignedAllocs = %d",gNumAlignedAllocs);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"gNumAlignedFree= %d",gNumAlignedFree);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"# alloc-free = %d",gNumAlignedAllocs-gNumAlignedFree);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;

			//enable BT_DEBUG_MEMORY_ALLOCATIONS define in Bullet/src/LinearMath/btAlignedAllocator.h for memory leak detection
#ifdef BT_DEBUG_MEMORY_ALLOCATIONS
			glRasterPos3f(xOffset,yStart,0);
			sprintf(buf,"gTotalBytesAlignedAllocs = %d",gTotalBytesAlignedAllocs);
			BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
			yStart += yIncr;
#endif //BT_DEBUG_MEMORY_ALLOCATIONS

			if (getDynamicsWorld())
			{
				glRasterPos3f(xOffset,yStart,0);
				sprintf(buf,"# objects = %d",getDynamicsWorld()->getNumCollisionObjects());
				BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
				yStart += yIncr;
				glRasterPos3f(xOffset,yStart,0);
				sprintf(buf,"# pairs = %d",getDynamicsWorld()->getBroadphase()->getOverlappingPairCache()->getNumOverlappingPairs());
				BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
				yStart += yIncr;

			}


#endif //SHOW_NUM_DEEP_PENETRATIONS

			resetPerspectiveProjection();
		}

		glEnable(GL_LIGHTING);


	}

	updateCamera();

}