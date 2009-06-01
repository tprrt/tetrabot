/*
 * Test.cpp
 *
 *  Created on: 24 févr. 2009
 *      Author: thomas
 */

#include "TetraRendering.h"

TetraRendering::TetraRendering() : Rendering("tetrabot", Ogre::ST_EXTERIOR_CLOSE) {

	this->leftMousePressed = false;
	this->rightMousePressed = false;
}

bool TetraRendering::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {


	return(true);
}

bool TetraRendering::mouseMoved (const OIS::MouseEvent &evt) {

	/*if(this->shiftLeftPressed) {
		//this->pSceneManager->getSceneNode("Scene1")->yaw(Ogre::Radian(evt.state.X.rel*(-0.005)));
		//this->pSceneManager->getSceneNode("Scene1")->pitch(Ogre::Radian(evt.state.Y.rel*(-0.005)));
		//this->pCamera->yaw(Ogre::Radian(evt.state.X.rel*(-0.005)));
		//this->pCamera->pitch(Ogre::Radian(evt.state.Y.rel*(-0.005)));
	}*/
	return(true);
}

bool TetraRendering::keyPressed(const OIS::KeyEvent &evt) {

	if(evt.key == OIS::KC_ESCAPE) {
		std::cout << "ESC pressed" << std::endl;
		this->finish = true;

	} else if(evt.key == OIS::KC_UP) {
		std::cout << "UP pressed" << std::endl;
		//this->pSceneManager->getSceneNode("NodeCamera")->;

	} else if(evt.key == OIS::KC_DOWN) {
		std::cout << "DOWN pressed" << std::endl;

	} else if(evt.key == OIS::KC_LEFT) {
		std::cout << "LEFT pressed" << std::endl;

	} else if(evt.key == OIS::KC_RIGHT) {
		std::cout << "RIGHT pressed" << std::endl;

	} else if(evt.key == OIS::KC_F1) {
		std::cout << "F1 pressed" << std::endl;
		//this->robot->StartThread(Vector3Gen(100, 100, 100));

	} else if(evt.key == OIS::KC_F2) {
		std::cout << "F2 pressed" << std::endl;
		this->robot->maxiRobot();

	} else if(evt.key == OIS::KC_F3) {
		std::cout << "F3 pressed" << std::endl;
		this->robot->nanoRobot();

	} else if(evt.key == OIS::KC_F4) {
		std::cout << "F4 pressed" << std::endl;
	} else if(evt.key == OIS::KC_F5) {
		std::cout << "F5 pressed" << std::endl;
		//

	} else if(evt.key == OIS::KC_F6) {
		std::cout << "F6 pressed" << std::endl;
		//

	} else if(evt.key == OIS::KC_F7) {
		std::cout << "F7 pressed" << std::endl;
		//

	} else if(evt.key == OIS::KC_F8) {
		std::cout << "F8 pressed" << std::endl;
		//

	} else if(evt.key == OIS::KC_A) {
		std::cout << "A pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'A');

	} else if(evt.key == OIS::KC_Z) {
		std::cout << "Z pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'Z');

	} else if(evt.key == OIS::KC_E) {
		std::cout << "E pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'E');

	} else if(evt.key == OIS::KC_R) {
		std::cout << "R pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'R');

	} else if(evt.key == OIS::KC_T) {
		std::cout << "T pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'T');

	} else if(evt.key == OIS::KC_Y) {
		std::cout << "Y pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'Y');

	} else if(evt.key == OIS::KC_Q) {
		std::cout << "Q pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'Q');

	} else if(evt.key == OIS::KC_S){
		std::cout << "S pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'S');

	} else if(evt.key == OIS::KC_D) {
		std::cout << "D pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'D');

	}  else if(evt.key == OIS::KC_F) {
		std::cout << "F pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'F');

	} else if(evt.key == OIS::KC_G) {
		std::cout << "G pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'G');

	} else if(evt.key == OIS::KC_H) {
		std::cout << "H pressed" << std::endl;
		//this->robot->Deplacement((unsigned char) 'H');
	}

	return(true);
}

TetraRendering::~TetraRendering() {

	delete this->robot;
	delete this->physicWorld;
}

void TetraRendering::createScene() {

	Ogre::Entity *pEntity;
	Ogre::Light *pLight;

	pEntity = this->pSceneManager->createEntity("Sphere1", "Sphere.mesh");
	pEntity->setCastShadows(true);

	//create environement
	this->initGround("Ground.mesh", false, GROUND_SCALE);
	this->initSkyBox(true, "Etoiles");

	//light
	pLight = this->pSceneManager->createLight("Light");
	pLight->setType(Ogre::Light::LT_POINT);
	pLight->setPosition(Ogre::Vector3(0, 400, 0));
	pLight->setDiffuseColour(1.0, 1.0, 1.0);
	pLight->setSpecularColour(1.0, 1.0, 1.0);


	//sceneNode for nodes of robot.
	this->pSceneManager->getRootSceneNode()->createChild("NodeNoeud1");
	this->pSceneManager->getSceneNode("NodeNoeud1")->attachObject(pEntity);
	this->pSceneManager->getSceneNode("NodeNoeud1")->scale(NODE_RADIUS, NODE_RADIUS, NODE_RADIUS);
	this->pSceneManager->getSceneNode("NodeNoeud1")->setPosition(Ogre::Vector3(0, 100, 0));

	this->pSceneManager->getRootSceneNode()->createChild("NodeNoeud2");
	this->pSceneManager->getSceneNode("NodeNoeud2")->attachObject(pEntity->clone("Sphere2"));
	this->pSceneManager->getSceneNode("NodeNoeud2")->scale(NODE_RADIUS, NODE_RADIUS, NODE_RADIUS);
	this->pSceneManager->getSceneNode("NodeNoeud2")->setPosition(Ogre::Vector3(50, 100, 0));

	this->pSceneManager->getRootSceneNode()->createChild("NodeNoeud3");
	this->pSceneManager->getSceneNode("NodeNoeud3")->attachObject(pEntity->clone("Sphere3"));
	this->pSceneManager->getSceneNode("NodeNoeud3")->scale(NODE_RADIUS, NODE_RADIUS, NODE_RADIUS);
	this->pSceneManager->getSceneNode("NodeNoeud3")->setPosition(Ogre::Vector3(0, 100, 50));

	this->pSceneManager->getRootSceneNode()->createChild("NodeNoeud4");
	this->pSceneManager->getSceneNode("NodeNoeud4")->attachObject(pEntity->clone("Sphere4"));
	this->pSceneManager->getSceneNode("NodeNoeud4")->scale(NODE_RADIUS, NODE_RADIUS, NODE_RADIUS);
	this->pSceneManager->getSceneNode("NodeNoeud4")->setPosition(Ogre::Vector3(50, 100, 50));

	//init physic
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	btVector3 gravity(0,-9.8,0);

	this->physicWorld = new PhysicWorld(worldMin,worldMax,gravity);
	this->physicWorld->initGround("./data/terrains/Ground.obj");

	this->robot = new RobotTetra(this->physicWorld->m_dynamicsWorld,this->pSceneManager,btVector3(0,30,0));

	//init pistonRendering.
	for (int i=0 ; i<EDGE_NUMBER ; i++ ) {
		this->pistons.push_back(new PistonRendering(EDGE_MIN_SIZE, EDGE_MAX_SIZE, this->pSceneManager, i));
	}

	//init sceneNode for CenterOfMass of robot.
	this->pSceneManager->getRootSceneNode()->createChild("NodeCenterOfMass");
	this->pSceneManager->getSceneNode("NodeCenterOfMass")->setPosition(Vector3Gen(this->robot->getCenterOfMassPosition()).toVector3());
	this->pSceneManager->getSceneNode("NodeCenterOfMass")->setVisible(false,true);

	//init sceneNode for camera 3rd.
	this->pSceneManager->getSceneNode("NodeCenterOfMass")->createChild("NodeCamera");
	this->pSceneManager->getSceneNode("NodeCamera")->attachObject(this->pCamera);
	this->pSceneManager->getSceneNode("NodeCamera")->setPosition(50, 50, 50);
	this->pCamera->lookAt(this->pSceneManager->getSceneNode("NodeCenterOfMass")->getPosition());
}

Ogre::SceneManager * TetraRendering::getSceneManager(void) {
	return(this->pSceneManager);
}

bool TetraRendering::frameStarted(const Ogre::FrameEvent & evt)
{

	

	//update physic calcul.
	if(this->physicWorld != NULL) {
		this->physicWorld->m_dynamicsWorld->stepSimulation(this->deltaT, 10);
	}

	//update position center of Mass.
	this->pSceneManager->getSceneNode("NodeCenterOfMass")->setPosition(Vector3Gen(this->robot->getCenterOfMassPosition()).toVector3());

	//update piston.
	this->pistons[0]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud1"),this->pSceneManager->getSceneNode("NodeNoeud2"));
	this->pistons[1]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud1"),this->pSceneManager->getSceneNode("NodeNoeud3"));
	this->pistons[2]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud1"),this->pSceneManager->getSceneNode("NodeNoeud4"));
	this->pistons[3]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud2"),this->pSceneManager->getSceneNode("NodeNoeud3"));
	this->pistons[4]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud2"),this->pSceneManager->getSceneNode("NodeNoeud4"));
	this->pistons[5]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud3"),this->pSceneManager->getSceneNode("NodeNoeud4"));

	return Rendering::frameStarted(evt);
}
