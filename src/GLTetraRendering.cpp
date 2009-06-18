//  @ Project : Tetrabot
//  @ File Name : GLTetraRendering.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains


#include "GLTetraRendering.h"

// Constructeur de la classe GLTetraRendering pour initialiser les Actions des pistons d un robot 
GLTetraRendering::GLTetraRendering()
{
	for(int i=0;i<6;i++)
	{
		action[i] = new ActionPiston(NULL,NULL);
	}
}
// Configuration des axes dans le monde bullet
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

// Methode pour initialiser le monde bullet et pour creer un robot
void GLTetraRendering::initPhysics()
{
	setTexturing(true);
	setShadows(true);

	setCameraDistance(26.f);

	// init world
	Vector3Gen *worldMin = new Vector3Gen(-1000,-1000,-1000);
	Vector3Gen* worldMax= new Vector3Gen(1000,1000,1000);
	Vector3Gen *gravite = new Vector3Gen(0,-9.8,0.);
	WorldInfo infos = WorldInfo(worldMin,worldMax,gravite);
	PhysicWorld* monde = new PhysicWorld(infos);
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
}

//-----------------------------------------------------------------------------
// Destructeur de la classe GLTetraRendering
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
// Methode pour dessiner les contraintes lienaires des pistons du robot
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
// Methode pour interagir avec bullet ( touches clavier )
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

		case 'A':
		{	robot->Deplacement((unsigned char) 'A');
		break;
		}
		case 'Z':
		{	robot->Deplacement((unsigned char) 'Z');
		break;
		}
		case 'E':
		{	robot->Deplacement((unsigned char) 'E');
		break;
		}
		case 'R':
		{	robot->Deplacement((unsigned char) 'R');
		break;
		}
		case 'T':
		{	robot->Deplacement((unsigned char) 'T');
		break;
		}
		case 'Y':
		{	robot->Deplacement((unsigned char) 'Y');
		break;
		}
		case 'Q':
		{	robot->Deplacement((unsigned char) 'Q');
		break;
		}
		case 'S':
		{	robot->Deplacement((unsigned char) 'S');
		break;
		}
		case 'D':
		{	robot->Deplacement((unsigned char) 'D');
		break;
		}
		case 'F':
		{	robot->Deplacement((unsigned char) 'F');
		break;
		}
		case 'G':
		{	robot->Deplacement((unsigned char) 'G');
		break;
		}
		case 'H':
		{	robot->Deplacement((unsigned char) 'H');
		break;
		}
		default: break; 
	}// FIN SWITCH
	//        std::cout << "unused key : " << key << std::endl;
	glutPostRedisplay();
}


//-----------------------------------------------------------------------------
// Methode pour interagir avec bullet ( touches clavier Fn )
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
		this->robot->maxiRobot();
		break;
	}
	case GLUT_KEY_F3:
	{
		printf("F3\n");
		// Tous les pistons a la taille minimale
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

//Methode pour configuer l affichage de ecran 
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

