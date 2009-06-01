#include "GLTetraRendering.h"

GLTetraRendering::GLTetraRendering()
{
	for(int i=0;i<6;i++)
	{
		action[i] = new ActionPiston(NULL,NULL);
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

void GLTetraRendering::initPhysics()
{
	setTexturing(true);
	setShadows(true);

	setCameraDistance(26.f);

	// init world
	btVector3 worldMin(btScalar(-1000),btScalar(-1000),btScalar(-1000));
	btVector3 worldMax(btScalar(1000),btScalar(1000),btScalar(1000));
	btVector3 gravite = btVector3(btScalar(0.),btScalar(-9.8),btScalar(0.));

	PhysicWorld* monde = new PhysicWorld(worldMin,worldMax,gravite);
	monde->initGround("./data/terrains/Ground.obj");

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
	 */
	// Création d'un sol
	/*btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(60.),btScalar(1.),btScalar(60.)));
	m_collisionShapes.push_back(groundShape);
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(btScalar(0.),btScalar(-6),btScalar(0.)));
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);	
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0,myMotionState,groundShape,btVector3(btScalar(0.),btScalar(0.),btScalar(0.)));
	btRigidBody* m_ground = new btRigidBody(rbInfo);
	this->m_dynamicsWorld->addRigidBody(m_ground);*/
	

	// On modelise le point d'arrive par un carre
	btCylinderShape* shapeCube = new btCylinderShape(btVector3(btScalar(5.),btScalar(0.1),btScalar(5.)));
	btTransform transCube;
	transCube.setIdentity();
	transCube.setOrigin(btVector3(btScalar(40.),btScalar(0.),btScalar(0.)));
	btDefaultMotionState* myMotionStateCube = new btDefaultMotionState(transCube);		
	btRigidBody::btRigidBodyConstructionInfo rbInfoCube(btScalar(10.),myMotionStateCube,shapeCube);
	bodyCube = new btRigidBody(rbInfoCube);
	this->m_dynamicsWorld->addRigidBody(bodyCube);
	
	// On cree une indication pour les pistons avec un pave
	btBoxShape* shapePave = new btBoxShape(btVector3(btScalar(.2),btScalar(.1),btScalar(1.)));
	btTransform transPave;
	transPave.setIdentity();
	transPave.setOrigin(btVector3(btScalar(40.),btScalar(1.),btScalar(1.)));
	btDefaultMotionState* myMotionStatePave = new btDefaultMotionState(transPave);		
	btRigidBody::btRigidBodyConstructionInfo rbInfoPave(btScalar(10.),myMotionStatePave,shapePave);
	bodyPave = new btRigidBody(rbInfoPave);
	this->m_dynamicsWorld->addRigidBody(bodyPave);


	// Creation du robot
	this->robot = new RobotTetra(this->m_dynamicsWorld,btVector3(btScalar(0.),btScalar(10.),btScalar(0.)));

	// Creation d'un controleur
	//controleur = new ControleurRobot(this->robot,btScalar(M_PI),btScalar(8.F),btScalar(4.F));

}

//-----------------------------------------------------------------------------

GLTetraRendering::~GLTetraRendering()
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

void GLTetraRendering::clientMoveAndDisplay()
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
	PhysicPiston* pistonTMP;
	//	dessiner contraintes lienaires;
	for(int i=0;i<6;i++){
		pistonTMP = (PhysicPiston*) robot->Arcs[i];
		if(pistonTMP!=NULL)
			drawSlider(pistonTMP->getContrainte());
	}

	glFlush();
	glutSwapBuffers();
}

//-----------------------------------------------------------------------------

void GLTetraRendering::displayCallback(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	PhysicPiston* pistonTMP;
	if (m_dynamicsWorld)
		m_dynamicsWorld->debugDrawWorld();

		//	dessiner contraintes lienaires;
		for(int i=0;i<6;i++){
			pistonTMP = (PhysicPiston*) robot->Arcs[i];
			if(pistonTMP!=NULL)
				drawSlider(pistonTMP->getContrainte());
		}

		renderme();

		glFlush();
		glutSwapBuffers();
}

//-----------------------------------------------------------------------------

void GLTetraRendering::keyboardCallback(unsigned char key, int x, int y)
{
	(void)x;
	(void)y;
	btScalar taille, tailleTmp,Step;
	int Num_Piston = 99;
	taille=0.;
	tailleTmp=0.;
	Step = 1.F;
	PhysicNoeud* noeudTMP;
	
	// Calcul de la position du piston voulu
	noeudTMP = (PhysicNoeud*) robot->Sommets[0];
	const btVector3& b0 =  noeudTMP->getBody()->getCenterOfMassPosition();
	noeudTMP = (PhysicNoeud*) robot->Sommets[1];
	const btVector3& b1 =  noeudTMP->getBody()->getCenterOfMassPosition();
	noeudTMP = (PhysicNoeud*) robot->Sommets[2];
	const btVector3& b2 =  noeudTMP->getBody()->getCenterOfMassPosition();
	noeudTMP = (PhysicNoeud*) robot->Sommets[3];
	const btVector3& b3 =  noeudTMP->getBody()->getCenterOfMassPosition();
	const btVector3& b4 =  this->bodyPave->getCenterOfMassPosition();
	btVector3 Gravity = btVector3(0.,0.,0.);
	switch (key) 
	{
		case 'z' :
			{	
				printf("Indication du piston 0\n"); 
				// test boule 0 et boule 2
				Gravity =  (b0+b2)*0.5 ;
				this->bodyPave->translate(-b4);
				this->bodyPave->translate(Gravity);
				break;	
			}
		case 'q' :
			{	
				printf("Indication du piston 1\n");
				// test boule 0 et boule 1
				Gravity =  (b0+b1)*0.5 ;
				this->bodyPave->translate(-b4);
				this->bodyPave->translate(Gravity);
				break;	
			}
		case 'w' :{
			printf("Indication du piston 2\n");
			// test boule 0 et boule 3
			Gravity =  (b0+b3)*0.5 ;
			this->bodyPave->translate(-b4);
			this->bodyPave->translate(Gravity);
			break;	
		}
		case 'e' :{
			printf("Indication du piston 3\n");
			// test boule 1 et boule 2
			Gravity =  (b1+b2)*0.5 ;
			this->bodyPave->translate(-b4);
			this->bodyPave->translate(Gravity);
			break;	
		}
		case 'd' :{
			printf("Indication du piston 4\n");
			// test boule 1 et boule 3
			Gravity =  (b1+b3)*0.5 ;
			this->bodyPave->translate(-b4);
			this->bodyPave->translate(Gravity);
			break;	
		}
		case 'x' :{
			printf("Indication du piston 5\n");
			// test boule 2 et boule 3
			Gravity =  (b2+b3)*0.5 ;
			this->bodyPave->translate(-b4);
			this->bodyPave->translate(Gravity);
			break;
		}

		case 'Z':
		{	robot->Deplacement((unsigned char) 'Z');
		break;
		}
		case 'Q':
		{	robot->Deplacement((unsigned char) 'Q');
		break;
		}
		case 'W':
		{	robot->Deplacement((unsigned char) 'W');
		break;
		}
		case 'E':
		{	robot->Deplacement((unsigned char) 'E');
		break;
		}
		case 'D':
		{	robot->Deplacement((unsigned char) 'D');
		break;
		}
		case 'X':
		{	robot->Deplacement((unsigned char) 'X');
		break;
		}
		case 'S':
		{
			
			// Je comprends pas ce que tu cherche a faire mais PAS D'ATTRIBUT incremente dans robotTetra
			// dans gl_piston peut-etre?
			printf("Inversion %f -> %f \n",robot->incremente, (-1)*robot->incremente);
			robot->incremente *=(btScalar) -1.;
			
		}

		default: break; 
	}// FIN SWITCH
	//        std::cout << "unused key : " << key << std::endl;
	glutPostRedisplay();
}


//-----------------------------------------------------------------------------
void GLTetraRendering::specialKeyboard(int key, int x, int y)	
{
	(void)x;
	(void)y;

	switch (key) 
	{
	case GLUT_KEY_F1:
	{
		printf("F1\n");
		// MODIF JAZZ : 31 / 05 /09 : 23h30
		printf("Recuperation du point d'arrivee ...\n");
		this->robot->bodyCube = this->bodyCube;
		Thread(this->robot,RobotTetra::marcherRobot);
		break;
	}

	case GLUT_KEY_F2:
	{
		printf("F2\n");
		// Tous les pistons a la taille maximale
		/*btScalar tailleTmp;
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
		}*/
		this->robot->maxiRobot();
		break;
	}
	case GLUT_KEY_F3:
	{
		printf("F3\n");
		// Tous les pistons a la taille minimale
		/*btScalar tailleTmp;
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
		*/
		this->robot->nanoRobot();
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
				robot->Arcs[i]->lock();
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
				robot->Arcs[i]->unlock();
			}
		}
		break;
	}
	case GLUT_KEY_F6:
	{
		printf("F6\n");
		/*// bloquer les 2 joints de chaque piston (ROTATION NULLE)
		for(int i=0;i<6;i++)
		{
			if(robot->Arcs[i]!=NULL)
			{
				robot->Arcs[i]->getConeA()->setLimit(0.F,0.F,0.F);
				robot->Arcs[i]->getConeB()->setLimit(0.F,0.F,0.F);
			}
		}
		*/
		printf("Plus utilisee\n");
		break;
	}
	case GLUT_KEY_F7:
	{
		printf("F7\n");
		/*// Débloquer les 2 joints de chaque piston (ROTATION 360°)
		for(int i=0;i<6;i++)
		{
			if(robot->Arcs[i]!=NULL)
			{
				robot->Arcs[i]->getConeA()->setLimit(ANGLES_CONE,ANGLES_CONE,0.F);
				robot->Arcs[i]->getConeB()->setLimit(ANGLES_CONE,ANGLES_CONE,0.F);
			}
		}
		*/
		printf("Plus utilisee\n");
		break;
	}
	case GLUT_KEY_F8:
	{
		printf("F8\n");
		// Tester l'algo GEN
		// Pos Initiale (25,25,25) , 5 pourcent de mutation
		// 2 Robots, 4 ActifsMax , 3 etapes et 2 Croisements
		AlgoGenTetra* algo = new AlgoGenTetra(this->m_dynamicsWorld,this->robot,btVector3(25,25,25),btScalar(0.05),2,1,2);
		algo->run();
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


void GLTetraRendering::renderme()
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

		/*		float xOffset = 10.f;
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
			sprintf(buf,"F1:Creer et executer l'AlgoGen.");
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

		 */
	}

	updateCamera();

}
bool GLTetraRendering::IsNotInArea(const btVector3 &G,const btVector3 &end2){
	return (
		 end2.distance(G) > btScalar(5.)
	);
}

/*
void* GL_Piston::marcherRobot(void *demo)
{
	GL_Piston* This = (GL_Piston*) demo;
	int NHaut=0,N1=-1,N2=-1,NRestant=-1;
	int PBas = -1,PHaut = -1,P1=-1,P2=-1;
	int i,j;
	btVector3 vectTMP[3];
	Noeud* noeuds[4];
	// On va deplacer le robot
	// On choisi un point d'arrive du robot sur le cercle de centre ( G : center of masse et de rayon R = 5.)
	btVector3 end = This->bodyCube->getCenterOfMassPosition();
	end.setY(btScalar(This->robot->getCenterOfMassPosition().getY()));


	// Pour faire simple, on va creer la matrice de liaison des noeuds (matrice d'identificateurs)
	int matLiaison[4][4];
	// initialisation de matLiaison à -1
	for( i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			matLiaison[i][j] = -1;
		}
	}
	matLiaison[0][2] = 0;
	matLiaison[2][0] = 0;
	matLiaison[0][1] = 1;
	matLiaison[1][0] = 1;
	matLiaison[0][3] = 2;
	matLiaison[3][0] = 2;
	matLiaison[1][2] = 3;
	matLiaison[2][1] = 3;
	matLiaison[1][3] = 4;
	matLiaison[3][1] = 4;
	matLiaison[2][3] = 5;
	matLiaison[3][2] = 5;
	// Tant que le robot n'est pas assez proche du point end, on fait avancer le robot (de maniere simple)
	// Le point end est assez proche si la distance entre ce dernier et le centre de gravite du robot
	// est inferieure à 6.
	while(This->IsNotInArea(This->robot->getCenterOfMassPosition(),end))
	{
		// Mettre le robot à l'etat initial (pistons au minimum de leur taille)
		for(i=0;i<6;i++)
		{
			This->action[i]->setPiston(This->robot->Arcs[i]);
			This->action[i]->setTailleVoulu(This->robot->Arcs[i]->getTailleMin());
			Thread((void*)This->action[i],actionThread);
		}
		// On attends 8 secondes que l'initialisation ce termine
		sleep(8);
		NHaut = 0;
		// On cherche le noeud NHaut le plus haut.
		for(i=1;i<4;i++)
		{
			vectTMP[0] = (This->robot->Sommets[NHaut]->getCenterOfMassPosition());
			vectTMP[1] = (This->robot->Sommets[i]->getCenterOfMassPosition());
			if((vectTMP[0].y()) < (vectTMP[1].y()))
				NHaut = i;
		}
		// On cherche maintenant les 2 noeuds de la base les plus proches du point d'arrivé end.
		j=0;
		for(i=0;i<4;i++)
		{
			if(i!= NHaut && j<3){
				noeuds[j] = This->robot->Sommets[i];
				vectTMP[j] = noeuds[j]->getCenterOfMassPosition();
				j++;
			}
		}
		if( (vectTMP[0].distance(end)) < (vectTMP[1].distance(end)) )
		{
			N1 = noeuds[0]->getID();
			if( (vectTMP[1].distance(end)) < (vectTMP[2].distance(end)) )
			{
				N2 = noeuds[1]->getID();
				NRestant = noeuds[2]->getID();
			}
			else
			{
				N2 = noeuds[2]->getID();
				NRestant = noeuds[1]->getID();
			}
		}
		else
		{
			if( (vectTMP[0].distance(end)) < (vectTMP[2].distance(end)) )
			{
				N1 = noeuds[0]->getID();
				N2 = noeuds[1]->getID();
				NRestant = noeuds[2]->getID();
			}
			else
			{
				N1 = noeuds[2]->getID();
				N2 = noeuds[1]->getID();
				NRestant = noeuds[0]->getID();
			}
		}
		// On cherche les pistons liant N1 et N2 (PBas), et celui liant NRestant à NHaut(PHaut).
		PBas = matLiaison[N1][N2];
		PHaut = matLiaison[NRestant][NHaut];

		// On mets le piston d'identificateur PBas à 8
		printf("NHaut: %d, N1: %d,N2: %d,NRestant: %d\n",NHaut,N1,N2,NRestant);
		printf("PHaut: %d, PBas: %d\n",PHaut,PBas);
		This->action[PBas]->setPiston(This->robot->Arcs[PBas]);
		This->action[PBas]->setTailleVoulu(btScalar(8.));
		Thread((void*)This->action[PBas],actionThread);

		// On debloque les pistons liant le noeuds NHaut (P1 et P2)
		//printf("P1: %d, P2: %d\n",matLiaison[NHaut][N1],matLiaison[NHaut][N2]);
		P1 = matLiaison[NHaut][N1];
		P2 = matLiaison[NHaut][N2];
		//printf("P1: %d, P2: %d\n",P1,P2);
		This->robot->Arcs[P1]->unlock();
		This->robot->Arcs[P2]->unlock();


		// On mets le piston d'identificateur PHaut à sa taille maximale
		This->action[PHaut]->setPiston(This->robot->Arcs[PHaut]);
		This->action[PHaut]->setTailleVoulu(This->robot->Arcs[PHaut]->getTailleMax());
		Thread((void*)This->action[PHaut],actionThread);
		// On attends 10 secondes
		sleep(10);
		// On bloque les pistons liant le noeuds NHaut precedement debloques
		This->robot->Arcs[P1]->lock();
		This->robot->Arcs[P2]->lock();
		// On debloque les contraintes coniques des deux precedents pistons


	}// Fin WHILE
	// La marche du robot est terminée.
	// Mettre le robot à l'etat final (pistons au minimum de leur taille)
	for(i=0;i<6;i++)
	{
		This->action[i]->setPiston(This->robot->Arcs[i]);
		This->action[i]->setTailleVoulu(This->robot->Arcs[i]->getTailleMin());
		Thread((void*)This->action[i],actionThread);
	}
	// Attendre que les pistons soient arretes
	sleep(8);

	printf("Arret du robot!\n");


	return NULL;
}
*/
