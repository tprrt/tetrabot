/*
 * Application.cpp
 *
 *  Created on: 17 févr. 2009
 *      Author: pantoufle
 */

#include "Rendering.h"

Rendering::Rendering(const std::string &name, const Ogre::SceneTypeMask typeMask) {

	this->finish = false;
	this->initRendering(name, typeMask);
	this->initInputOutput();
}

void Rendering::run(void) {
	this->pRoot->startRendering();
}

void Rendering::initWorld(const std::string& filename, const bool enable, const std::string& materialName) {

	this->pSceneManager->setWorldGeometry(filename);
	this->pSceneManager->setSkyBox(enable, materialName);
}

bool Rendering::frameStarted(const Ogre::FrameEvent& evt)  {

	if(this->pMouse) {
		this->pMouse->capture();
	}
	if(this->pKeyboard) {
		this->pKeyboard->capture();
	}
	return (!this->finish);
}

Rendering::~Rendering(void) {

	if(this->pRoot) {
		delete this->pRoot;
	}
	if(this->pRenderWindow) {
		delete this->pRenderWindow;
	}
	if(this->pSceneManager) {
		delete this->pSceneManager;
	}
	if(this->pViewport) {
		delete this->pViewport;
	}
	if(this->pCamera) {
		delete this->pCamera;
	}
	/*if(this->pInputManager) {
		delete this->pInputManager;
	}*/
	if(this->pMouse) {
		delete this->pMouse;
	}
	if(this->pKeyboard) {
		delete this->pKeyboard;
	}
}

void Rendering::initRendering(const std::string &name, const Ogre::SceneTypeMask typeMask) {

	std::string nameConfigFile = name + ".cfg";
	std::string nameLogFile = name + ".log";

	this->pRoot = new Ogre::Root("plugins.cfg",nameConfigFile,nameLogFile);
	if(!this->pRoot->restoreConfig())
	{
		if(!this->pRoot->showConfigDialog())
		{
			this->~Rendering();
		}
	}
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing Rendering ***");
	this->pRenderWindow = this->pRoot->initialise(true, name);

	this->pSceneManager = this->pRoot->createSceneManager(typeMask, name);
	this->pSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	this->pSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	this->pCamera = this->pSceneManager->createCamera("Camera");
	this->pCamera->setPosition(Ogre::Vector3(0, 0, 0));
	this->pCamera->lookAt(Ogre::Vector3(0,0,0));
	this->pCamera->setNearClipDistance(5);
	//this->pCamera->setFarClipDistance(1000);

	this->pViewport = this->pRenderWindow->addViewport(pCamera);
	this->pViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	this->pCamera->setAspectRatio(Ogre::Real(this->pViewport->getActualWidth())/Ogre::Real(this->pViewport->getActualHeight()));

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./data/models","FileSystem","General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./data/terrains","FileSystem","General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./data/skybox","FileSystem","General");

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	this->pRoot->addFrameListener(this);
	Ogre::WindowEventUtilities::addWindowEventListener(this->pRenderWindow, this);
}

void Rendering::initInputOutput() {

	OIS::ParamList paramList;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	unsigned int width, height, depth;
	int top, left;

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing InputOutput ***");
	this->pRenderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	paramList.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	#if defined OIS_WIN32_PLATFORM
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	#elif defined OIS_LINUX_PLATFORM
	paramList.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
	paramList.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
	paramList.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	paramList.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
	#endif

	this->pInputManager = OIS::InputManager::createInputSystem(paramList);

	//creation de l'objet clavier.
	this->pKeyboard = static_cast<OIS::Keyboard*>(this->pInputManager->createInputObject(OIS::OISKeyboard, true));
	this->pKeyboard->setEventCallback(this);

	//creation de l'objet souris.
	this->pMouse = static_cast<OIS::Mouse*>(this->pInputManager->createInputObject(OIS::OISMouse, true));
	const OIS::MouseState &ms = this->pMouse->getMouseState();
	this->pMouse->setEventCallback(this);

	//taille de la fenetre de l'application pour la gestion de la souris.
	this->pRenderWindow->getMetrics(width, height, depth, left, top);
	ms.width = width;
	ms.height = height;
}

