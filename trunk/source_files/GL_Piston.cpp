//-----------------------------------------------------------------------------
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btIDebugDraw.h"

#include "GLDebugDrawer.h"

#include "BMF_Api.h"
#include <stdio.h> //printf debugging

#include "GL_Piston.h"
#include "GL_ShapeDrawer.h"
#include "GlutStuff.h"



//-----------------------------------------------------------------------------

GL_Piston::GL_Piston()
{
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

	// Creation du robot
	this->robot = new Robot_Tetra(this->m_dynamicsWorld,NULL);

/*// ----- Creation des Objets:
	// Creation des boules
	for(int i=0;i<4;i++)
	{
		this->boules[i] = new Boule(this->m_dynamicsWorld,btVector3(5*i,12.F*i,-5.F),RAYON_BOULE,POIDS_BOULE);
		//printf("boule %d, id: %d\n",i,this->boules[i]->getID());
	}
	// Creation des Pistons
	for(int i=0;i<6;i++)
	{
		this->pistons[i] = new Piston(this->m_dynamicsWorld,btVector3(-5.F,15.F,-10.F),PISTON_TAILLE_MIN,PISTON_TAILLE_MAX,VELOCITE_PISTON);
		//this->pistons[i]->bloquerPiston();
	}
	// On lie les pistons aux boules

// TEST TETRAHEDRE (FONCTIONNE!!!)
	btScalar angle1 = btScalar(M_PI_4*(4.F/3.F));
	for(int i=0;i<3;i++)
	{
		boules[0]->lierPiston(pistons[i],'A',angle1,(i*2*M_PI)/3);
	}
	boules[1]->lierPiston(pistons[1],'B',angle1,(0*2*M_PI)/3);
	boules[1]->lierPiston(pistons[3],'A',angle1,(1*2*M_PI)/3);
	boules[1]->lierPiston(pistons[4],'A',angle1,(2*2*M_PI)/3);

	boules[2]->lierPiston(pistons[0],'B',angle1,(0*2*M_PI)/3);
	boules[2]->lierPiston(pistons[5],'B',angle1,(1*2*M_PI)/3);
	boules[2]->lierPiston(pistons[3],'B',angle1,(2*2*M_PI)/3);

	boules[3]->lierPiston(pistons[2],'B',angle1,(0*2*M_PI)/3);
	boules[3]->lierPiston(pistons[4],'B',angle1,(1*2*M_PI)/3);
	boules[3]->lierPiston(pistons[5],'A',angle1,(2*2*M_PI)/3);
*/	
	
/*	//TEST MISE EN PLACE DES PISTONS PAR ROTATION (FONCTIONNE!!!)
	char extremite = 'B';

	int i=0;
	boules[0]->lierPiston(pistons[1],extremite,3*M_PI_4,i*(2.F*M_PI/3.F));
	i++;
	boules[0]->lierPiston(pistons[0],extremite,3*M_PI_4,i*(2.F*M_PI/3.F));
	i++;
	boules[0]->lierPiston(pistons[2],extremite,3*M_PI_4,i*(2.F*M_PI/3.F));
	i++;
	
	i=0;
	boules[0]->lierPiston(pistons[3],extremite,3*M_PI_4+M_PI/2.F,i*(2.F*M_PI/3.F));
	i++;
	boules[0]->lierPiston(pistons[4],extremite,3*M_PI_4+M_PI/2.F,i*(2.F*M_PI/3.F));
	i++;
	boules[0]->lierPiston(pistons[5],extremite,3*M_PI_4+M_PI/2.F,i*(2.F*M_PI/3.F));
	i++;
*/	
/*  // TEST TRIANGLE (FONCTIONNE!!!)
	btScalar angle1 = btScalar(M_PI_2*0.8F);
	btScalar angle2 = btScalar(0);
	btScalar angle3 = btScalar(M_PI);

	boules[0]->lierPiston(pistons[1],'A',angle1,angle2);
	boules[0]->lierPiston(pistons[0],'B',angle1,angle3);

	boules[1]->lierPiston(pistons[1],'B',angle1,angle2);
	boules[1]->lierPiston(pistons[2],'A',angle1,angle3);

	boules[2]->lierPiston(pistons[2],'B',angle1,angle2);
	boules[2]->lierPiston(pistons[0],'A',angle1,angle3);
*/	

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
			// On va essayer de faire chuter le tetra:
			// piston 0 et 2 -> 6.2497F
			// piston 1 -> 8.F
			// piston 3 et 4 -> 3.F
			// piston 5 -> 4.2426F
			
			this->action[0] = new Action(robot->Arcs[1],btScalar(10.F)); 
			this->action[1] = new Action(robot->Arcs[3],btScalar(3.F));
			this->action[2] = new Action(robot->Arcs[4],btScalar(3.F));
			this->action[3] = new Action(robot->Arcs[5],btScalar(4.2426F));
			// Optionnelles?
			//this->action[4] = new Action(this->pistons[0],btScalar(6.2497F));
			//this->action[5] = new Action(this->pistons[2],btScalar(6.2497F));

			for(int i=0;i<4;i++)
			{
				//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) actionThread,action[i], 0, &threadID);
				Thread((void*)action[i],actionThread);
			}
			robot->Arcs[4]->debloquerPiston();
			robot->Arcs[5]->debloquerPiston();
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
						this->action[i] = new Action(robot->Arcs[i],robot->Arcs[i]->getTailleMax());
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
						this->action[i] = new Action(robot->Arcs[i],robot->Arcs[i]->getTailleMin());
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