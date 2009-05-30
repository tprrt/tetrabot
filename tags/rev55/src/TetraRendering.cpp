/*
 * Test.cpp
 *
 *  Created on: 24 févr. 2009
 *      Author: thomas
 */

#include "TetraRendering.h"

TetraRendering::TetraRendering() : Rendering("tetrabot", Ogre::ST_EXTERIOR_CLOSE) {

	this->shiftLeftPressed = false;
}

bool TetraRendering::mouseMoved (const OIS::MouseEvent &evt) {

	if(this->shiftLeftPressed) {
		//this->pSceneManager->getSceneNode("Scene1")->yaw(Ogre::Radian(evt.state.X.rel*(-0.005)));
		//this->pSceneManager->getSceneNode("Scene1")->pitch(Ogre::Radian(evt.state.Y.rel*(-0.005)));
		//this->pCamera->yaw(Ogre::Radian(evt.state.X.rel*(-0.005)));
		//this->pCamera->pitch(Ogre::Radian(evt.state.Y.rel*(-0.005)));
	}
	return(true);
}

bool TetraRendering::keyPressed(const OIS::KeyEvent &evt) {

	if(evt.key == OIS::KC_ESCAPE) {
		this->finish = true;
	} else if(evt.key == OIS::KC_LSHIFT) {
		if(this->shiftLeftPressed) {
			this->shiftLeftPressed = false;
		} else {
			this->shiftLeftPressed = true;
		}
	} else if(evt.key == OIS::KC_UP) {
		std::cout << "UP pressed" << std::endl;
		//this->pSceneManager->getSceneNode("Scene1")->

	} else if(evt.key == OIS::KC_DOWN) {
		std::cout << "DOWN pressed" << std::endl;
		//this->pSceneManager->getSceneNode("Scene1")->

	} else if(evt.key == OIS::KC_LEFT) {
		std::cout << "LEFT pressed" << std::endl;
		//this->pSceneManager->getSceneNode("Scene1")->

	} else if(evt.key == OIS::KC_RIGHT) {
		std::cout << "RIGHT pressed" << std::endl;
		//this->pSceneManager->getSceneNode("Scene1")->

	} else if(evt.key == OIS::KC_F1) {
		std::cout << "F1 pressed" << std::endl;
		this->robot->move(100,100,100);

	} else if(evt.key == OIS::KC_F2) {
		std::cout << "F2 pressed" << std::endl;
		this->robot->stretch();

	} else if(evt.key == OIS::KC_F3) {
		std::cout << "F3 pressed" << std::endl;
		this->robot->reduce();

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
	}
	return(true);
}

//TetraRendering::~TetraRendering() {
	//Rendering::~Rendering();
//}

void TetraRendering::createScene() {

	Ogre::Entity *pEntity;
	Ogre::Light *pLight;

	pEntity = this->pSceneManager->createEntity("Sphere1", "Sphere.mesh");
	pEntity->setCastShadows(true);

	//create environement

	this->initGround("Ground.mesh", false);
	this->initSkyBox(true, "Etoiles");

	//light
	pLight = this->pSceneManager->createLight("Light");
	pLight->setType(Ogre::Light::LT_POINT);
	pLight->setPosition(Ogre::Vector3(0, 400, 0));
	pLight->setDiffuseColour(1.0, 1.0, 1.0);
	pLight->setSpecularColour(1.0, 1.0, 1.0);


	//spheres
	this->pSceneManager->getRootSceneNode()->createChild("NodeNoeud1");
	this->pSceneManager->getSceneNode("NodeNoeud1")->attachObject(pEntity);
	this->pSceneManager->getSceneNode("NodeNoeud1")->scale(BOULE_RAYON, BOULE_RAYON, BOULE_RAYON);
	this->pSceneManager->getSceneNode("NodeNoeud1")->setPosition(Ogre::Vector3(0, 100, 0));


	this->pSceneManager->getRootSceneNode()->createChild("NodeNoeud2");
	this->pSceneManager->getSceneNode("NodeNoeud2")->attachObject(pEntity->clone("Sphere2"));
	this->pSceneManager->getSceneNode("NodeNoeud2")->scale(BOULE_RAYON, BOULE_RAYON, BOULE_RAYON);
	this->pSceneManager->getSceneNode("NodeNoeud2")->setPosition(Ogre::Vector3(50, 100, 0));

	this->pSceneManager->getRootSceneNode()->createChild("NodeNoeud3");
	this->pSceneManager->getSceneNode("NodeNoeud3")->attachObject(pEntity->clone("Sphere3"));
	this->pSceneManager->getSceneNode("NodeNoeud3")->scale(BOULE_RAYON, BOULE_RAYON, BOULE_RAYON);
	this->pSceneManager->getSceneNode("NodeNoeud3")->setPosition(Ogre::Vector3(0, 100, 50));

	this->pSceneManager->getRootSceneNode()->createChild("NodeNoeud4");
	this->pSceneManager->getSceneNode("NodeNoeud4")->attachObject(pEntity->clone("Sphere4"));
	this->pSceneManager->getSceneNode("NodeNoeud4")->scale(BOULE_RAYON, BOULE_RAYON, BOULE_RAYON);
	this->pSceneManager->getSceneNode("NodeNoeud4")->setPosition(Ogre::Vector3(50, 100, 50));

	//physic
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	btVector3 gravity(0,-9.8,0);

	this->physicWorld = new WorldPhysic(worldMin,worldMax,gravity);
	this->physicWorld->initGround("./data/terrains/Ground.obj");

	this->robot = new RobotTetra(this->physicWorld->m_dynamicsWorld,this->pSceneManager,btVector3(0,30,0));

	for (int i=0 ; i<NB_PISTON ; i++ ) {
		this->pistons.push_back(new PistonRendering(TAILLE_PISTON_MIN, TAILLE_PISTON_MAX, this->pSceneManager, i));
	}
}

Ogre::SceneManager * TetraRendering::getSceneManager(void) {
	return(this->pSceneManager);
}

bool TetraRendering::frameStarted(const Ogre::FrameEvent & evt)
{
	btVector3 btCenter;

	if(this->physicWorld != NULL) {
		this->physicWorld->m_dynamicsWorld->stepSimulation(1.f/60.f,10);
	}

	//NodePosition = this->pSceneManager->getSceneNode("NodeNoeud1")->getPosition();
	btCenter = this->robot->getCenterOfMassPosition();

	this->pCamera->setPosition(btCenter.x()+50, btCenter.y()+50, btCenter.z()+50);
	this->pCamera->lookAt(btCenter.x(), btCenter.y(), btCenter.z());

	this->pistons[0]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud1"),this->pSceneManager->getSceneNode("NodeNoeud2"));
	this->pistons[1]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud1"),this->pSceneManager->getSceneNode("NodeNoeud3"));
	this->pistons[2]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud1"),this->pSceneManager->getSceneNode("NodeNoeud4"));
	this->pistons[3]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud2"),this->pSceneManager->getSceneNode("NodeNoeud3"));
	this->pistons[4]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud2"),this->pSceneManager->getSceneNode("NodeNoeud4"));
	this->pistons[5]->afficherPiston(this->pSceneManager->getSceneNode("NodeNoeud3"),this->pSceneManager->getSceneNode("NodeNoeud4"));

	return Rendering::frameStarted(evt);
}
