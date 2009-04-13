/*
 * Test.cpp
 *
 *  Created on: 24 févr. 2009
 *      Author: pantoufle
 */

#include "TetraRendering.h"

TetraRendering::TetraRendering() : Rendering("tetra", Ogre::ST_EXTERIOR_CLOSE) {

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
		//this->pSceneManager->getSceneNode("Scene1")->
	} else if(evt.key == OIS::KC_DOWN) {
		//this->pSceneManager->getSceneNode("Scene1")->
	} else if(evt.key == OIS::KC_LEFT) {
		//this->pSceneManager->getSceneNode("Scene1")->
	} else if(evt.key == OIS::KC_RIGHT) {
		//this->pSceneManager->getSceneNode("Scene1")->
	}
    return(true);
}

TetraRendering::~TetraRendering() {

}

void TetraRendering::createScene() {

	Ogre::Entity *pEntity;

	pEntity = this->pSceneManager->createEntity("Sphere1", "Sphere.mesh");
	pEntity->setCastShadows(true);

	//creation du terrain.
	this->initWorld("terrain.cfg", true, "Etoiles");

	//spheres
	this->pSceneManager->getRootSceneNode()->createChild("NodeBoule1");
	this->pSceneManager->getSceneNode("NodeBoule1")->attachObject(pEntity);
	this->pSceneManager->getSceneNode("NodeBoule1")->scale(3.5, 3.5, 3.5);
	this->pSceneManager->getSceneNode("NodeBoule1")->setPosition(Ogre::Vector3(750, 250, 750));


	this->pSceneManager->getRootSceneNode()->createChild("NodeBoule2");
	this->pSceneManager->getSceneNode("NodeBoule2")->attachObject(pEntity->clone("Sphere2"));
	this->pSceneManager->getSceneNode("NodeBoule2")->scale(3.5, 3.5, 3.5);

	this->pSceneManager->getRootSceneNode()->createChild("NodeBoule3");
	this->pSceneManager->getSceneNode("NodeBoule3")->attachObject(pEntity->clone("Sphere3"));
	this->pSceneManager->getSceneNode("NodeBoule3")->scale(3.5, 3.5, 3.5);

	this->pSceneManager->getRootSceneNode()->createChild("NodeBoule4");
	this->pSceneManager->getSceneNode("NodeBoule4")->attachObject(pEntity->clone("Sphere4"));
	this->pSceneManager->getSceneNode("NodeBoule4")->scale(3.5, 3.5, 3.5);
	
	// TEST ROBOT PHYSIQUE
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	btVector3 gravite = btVector3(0.,-9.8,0.);
	class btDefaultCollisionConfiguration* m_collisionConfiguration = new btDefaultCollisionConfiguration();
	class btCollisionDispatcher* m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	class btBroadphaseInterface* m_overlappingPairCache = new btAxisSweep3(worldMin,worldMax);

#if SLIDER_DEMO_USE_ODE_SOLVER
	m_constraintSolver = new btOdeQuickstepConstraintSolver();
#else
	class btConstraintSolver* m_constraintSolver = new btSequentialImpulseConstraintSolver();
#endif
	this->Monde = new btDiscreteDynamicsWorld(m_dispatcher,m_overlappingPairCache,m_constraintSolver,m_collisionConfiguration);
	//	wp->getSolverInfo().m_numIterations = 20; // default is 10
	Monde->setGravity(gravite);
	this->robotPhysic = new Robot_Tetra(Monde,this->pSceneManager);
	// FIN TEST ROBOT PHYSIQUE



	//Pistons.
	/*for(i=0;i<6;i++) {

	}*/

	//Positionne la camera.
	this->pCamera->setPosition(Ogre::Vector3(750, 300, 600));
	this->pCamera->lookAt(Ogre::Vector3(750, 250, 750));
}

Ogre::SceneManager * TetraRendering::getSceneManager(void) {
	return(this->pSceneManager);
}

/*void TetraRendering::createScene1() {

	Ogre::Light *pLight1;
	Ogre::Light *pLight2;
	Ogre::Entity *pEntity1;

	//creation du terrain.
	this->pSceneManager->setWorldGeometry("terrain.cfg");

	//creation de la skybox.
	this->pSceneManager->setSkyBox(true, "Etoiles");

	//creation d un brouillard.
	//this->pSceneManager->setFog( Ogre::FOG_EXP2, Ogre::ColourValue(0.1,0.1,0.1), 0.001 );

	//creation de la lumiere ambiente.
	//this->pSceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	//creation du noeud de scene 1.
	//this->pSceneManager->getRootSceneNode()->createChild("Scene1");

	//creation d un spot rouge.
    //pLight1 = this->pSceneManager->createLight("Light1");
    //pLight1->setType(Ogre::Light::LT_POINT);
    //pLight1->setPosition(Ogre::Vector3(900, 400, -850));
    //pLight1->setDiffuseColour(0.5, 0.0, 0.0);
    //pLight1->setSpecularColour(0.5, 0.0, 0.0);
    //this->pSceneManager->getSceneNode("Scene1")->attachObject(pLight1);

	//creation d un spot ambiente bleu.
    //pLight2 = this->pSceneManager->createLight("Light2");
    //pLight2->setType(Ogre::Light::LT_POINT);
    //pLight2->setPosition(Ogre::Vector3(600, 400, -850));
    //pLight2->setDiffuseColour(0.0, 0.0, 0.5);
    //pLight2->setSpecularColour(0.0, 0.0, 0.5);
    //this->pSceneManager->getSceneNode("Scene1")->attachObject(pLight2);

	//creation d une sphere.
	//pEntity1 = this->pSceneManager->createEntity("Scene1", "Sphere.mesh");
	//pEntity1->setCastShadows(true);
	//this->pSceneManager->getSceneNode("Scene1")->attachObject(pEntity1);
	//this->pSceneManager->getSceneNode("Scene1")->scale(3.5, 3.5, 3.5);
	//this->pSceneManager->getSceneNode("Scene1")->setPosition(Ogre::Vector3(750, 250, 750));


	//creation du noeud de scene 1.
	//this->pSceneManager->getSceneNode("Scene1")->createChild("Scene2");
	//this->pSceneManager->getSceneNode("Scene2")->setPosition(Ogre::Vector3(0, 10, -10));
	//placement de la camera.
	//this->pCamera->setPosition(Ogre::Vector3(750, 300, 600));
	//this->pSceneManager->getSceneNode("Scene2")->attachObject(this->pCamera);
	//this->pCamera->lookAt(Ogre::Vector3(750, 250, 750));

}*/


bool TetraRendering::frameStarted(const Ogre::FrameEvent & evt)
{
	// next step Bullet
	if(Monde!=NULL)
		Monde->stepSimulation(1.f/60.f,10);
	return Rendering::frameStarted(evt);
}