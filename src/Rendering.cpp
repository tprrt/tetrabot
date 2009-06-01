/*
 * Application.cpp
 *
 *  Created on: 17 févr. 2009
 *      Author: pantoufle
 */

#include "Rendering.h"

Rendering::Rendering(const std::string &name, const Ogre::SceneTypeMask typeMask) {

	this->deltaT = 0;
	this->finish = false;
	this->initRendering(name, typeMask);
	this->initInputOutput();
	this->initGUI();
}

void Rendering::run(void) {
	this->pRoot->startRendering();
}

void Rendering::initGround(const std::string& fileMesh, const bool shadows, const int scale) {

	Ogre::Entity *pEntity;

	//this->pSceneManager->setWorldGeometry(filename);
	pEntity = this->pSceneManager->createEntity("Ground", fileMesh);
	pEntity->setCastShadows(shadows);

	this->pSceneManager->getRootSceneNode()->createChild("NodeGround");
	this->pSceneManager->getSceneNode("NodeGround")->attachObject(pEntity);
	this->pSceneManager->getSceneNode("NodeGround")->scale(scale, scale, scale);
	//this->pSceneManager->getSceneNode("NodeGround")->setPosition(Ogre::Vector3(0, 0, 0));
}

void Rendering::initSkyBox(const bool enable, const std::string& SkyName) {

	this->pSceneManager->setSkyBox(enable, SkyName);
}

bool Rendering::keyPressed(const OIS::KeyEvent &evt) { 

	CEGUI::System::getSingleton().injectKeyDown(evt.key);

	return true;
}

bool Rendering::keyReleased(const OIS::KeyEvent &evt) {

	CEGUI::System::getSingleton().injectKeyUp(evt.key);

	return true;
}

bool Rendering::mousePressed(const OIS::MouseEvent &evt, const OIS::MouseButtonID id) {

	CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));

	return true;
}

bool Rendering::mouseReleased(const OIS::MouseEvent &evt, const OIS::MouseButtonID id) {

	CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));

	return true;
}

bool Rendering::mouseMoved(const OIS::MouseEvent &evt) {

	CEGUI::System::getSingleton().injectMouseMove(evt.state.X.rel, evt.state.Y.rel);

	return true;
}

bool Rendering::frameStarted(const Ogre::FrameEvent& evt)  {

	this->deltaT = evt.timeSinceLastFrame;

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
		Ogre::WindowEventUtilities::removeWindowEventListener(this->pRenderWindow, this);
		windowClosed(this->pRenderWindow);
		//delete this->pRenderWindow;
	}
	if(this->pSceneManager) {
		this->pSceneManager->destroyQuery(this->pRaySceneQuery);
		delete this->pSceneManager;
	}
	/*if(this->pViewport) {
		delete this->pViewport;
	}*/
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
	if(this->pRaySceneQuery) {
		delete this->pRaySceneQuery;
	}
	if(this->pGUIRenderer) {
		delete this->pGUIRenderer;
	}
	if(this->pGUISystem) {
		delete this->pGUISystem;
	}
}

void Rendering::initRendering(const std::string &name, const Ogre::SceneTypeMask typeMask) {

	std::string nameConfigFile = name + ".cfg";
	std::string nameLogFile = name + ".log";

	this->pRoot = new Ogre::Root("./plugins.cfg",nameConfigFile,nameLogFile);
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
	this->pSceneManager->setAmbientLight(Ogre::ColourValue(0.15, 0.15, 0.15));
	this->pSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	this->pCamera = this->pSceneManager->createCamera("Camera");
	this->pCamera->setPosition(Ogre::Vector3(0, 0, 0));
	this->pCamera->lookAt(Ogre::Vector3(0,0,0));
	this->pCamera->setNearClipDistance(5);
	//this->pCamera->setFarClipDistance(1000);

	this->pViewport = this->pRenderWindow->addViewport(pCamera);
	this->pViewport->setOverlaysEnabled(false);
	this->pViewport->setClearEveryFrame(true);
	this->pViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	this->pCamera->setAspectRatio(Ogre::Real(this->pViewport->getActualWidth())/Ogre::Real(this->pViewport->getActualHeight()));

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./data/models/","FileSystem","General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./data/terrains/","FileSystem","General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("./data/skybox/","FileSystem","General");

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	this->pRoot->addFrameListener(this);
	Ogre::WindowEventUtilities::addWindowEventListener(this->pRenderWindow, this);

	this->pRaySceneQuery = this->pSceneManager->createRayQuery(Ogre::Ray());

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
	this->pKeyboard = dynamic_cast<OIS::Keyboard*>(this->pInputManager->createInputObject(OIS::OISKeyboard, true));
	this->pKeyboard->setEventCallback(this);

	//creation de l'objet souris.
	this->pMouse = dynamic_cast<OIS::Mouse*>(this->pInputManager->createInputObject(OIS::OISMouse, true));
	const OIS::MouseState &ms = this->pMouse->getMouseState();
	this->pMouse->setEventCallback(this);

	//taille de la fenetre de l'application pour la gestion de la souris.
	this->pRenderWindow->getMetrics(width, height, depth, left, top);
	ms.width = width;
	ms.height = height;
}

void Rendering::initGUI() {

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing GUI ***");

	this->pGUIRenderer = new CEGUI::OgreCEGUIRenderer(this->pRenderWindow, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, this->pSceneManager);
	this->pGUISystem = new CEGUI::System(this->pGUIRenderer);

	CEGUI::MouseCursor::getSingleton().setImage(CEGUI::System::getSingleton().getDefaultMouseCursor());
	//CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"skin.scheme");
	//CEGUI::MouseCursor::getSingleton().setImage("skinMouse", "MouseArrow");
	//this->pGUISystem->setDefaultMouseCursor((CEGUI::utf8*)"skinMouse", (CEGUI::utf8*)"MouseArrow");
	//this->pGUISystem->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");
}

const CEGUI::MouseButton Rendering::convertButton(const OIS::MouseButtonID buttonID) const {

	switch (buttonID) {
	case OIS::MB_Left:
	return CEGUI::LeftButton;

	case OIS::MB_Right:
	return CEGUI::RightButton;

	case OIS::MB_Middle:
	return CEGUI::MiddleButton;

	default:
	return CEGUI::LeftButton;
	}
}

