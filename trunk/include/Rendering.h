#ifndef RENDERING_H_
#define RENDERING_H_

/**
 * \file Rendering.h
 * \author Frozen Brains
 * \brief Gestion de l'affichage générique sous Ogre
 * \version 0.1
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUILogger.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <OgreCEGUIRenderer.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	#include "Ogre.h"
	#include "OIS/OIS.h"
#else
	#include <OGRE/Ogre.h>
	#include <OIS/OIS.h>
#endif

/**
 * \class Rendering
 * \brief Classe gérant l'affichage sous ogre
 */
class Rendering : public Ogre::FrameListener, public Ogre::WindowEventListener,
	public OIS::MouseListener, public OIS::KeyListener {

protected:
	Ogre::Root *pRoot;
	Ogre::RenderWindow *pRenderWindow;
	Ogre::SceneManager *pSceneManager;
	Ogre::Viewport *pViewport;
	Ogre::Camera *pCamera;
	Ogre::RaySceneQuery *pRaySceneQuery;
	//Ogre::String ResourcePath;

	OIS::InputManager *pInputManager;
	OIS::Mouse *pMouse;
	OIS::Keyboard *pKeyboard;

	CEGUI::OgreCEGUIRenderer *pGUIRenderer;
	CEGUI::System *pGUISystem;

	float deltaT;
	bool finish;

public:
	Rendering(const std::string &name = "Rendering", const Ogre::SceneTypeMask typeMask = Ogre::ST_GENERIC);

	void initGround(const std::string& fileMesh, const bool shadows, const int scale);

	void initSkyBox(const bool enable, const std::string& SkyName);

	bool frameStarted(const Ogre::FrameEvent& evt);

	void run(void);

	//void windowResized(Ogre::RenderWindow* rw);

	//void windowClosed(Ogre::RenderWindow* rw)

	bool keyPressed(const OIS::KeyEvent &evt);

	bool keyReleased(const OIS::KeyEvent &evt);

	bool mouseMoved (const OIS::MouseEvent &evt);

	bool mousePressed (const OIS::MouseEvent &evt, const OIS::MouseButtonID id);

	bool mouseReleased (const OIS::MouseEvent &evt, const OIS::MouseButtonID id);

	const CEGUI::MouseButton convertButton(const OIS::MouseButtonID buttonID) const;

	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }

	virtual ~Rendering();

protected:
	void initRendering(const std::string &name, const Ogre::SceneTypeMask typeMask);

	void initInputOutput();

	void initGUI();
};

#endif /* RENDERING_H_ */
