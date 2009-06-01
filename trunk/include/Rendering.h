/*
 * Rendering.h
 *
 *  Created on: 17 févr. 2009
 *      Author: pantoufle
 */

#ifndef RENDERING_H_
#define RENDERING_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUISchemeManager.h>
#include <OgreCEGUIRenderer.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	#include "Ogre.h"
	#include "OIS/OIS.h"
#else
	#include <OGRE/Ogre.h>
	#include <OIS/OIS.h>
#endif

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

	void initGround(const std::string& fileMesh, const bool shadows);

	void initSkyBox(const bool enable, const std::string& SkyName);

	bool frameStarted(const Ogre::FrameEvent& evt);

	void run(void);

	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }

	virtual bool keyPressed(const OIS::KeyEvent &e) { return true; }

	virtual bool keyReleased(const OIS::KeyEvent &e) {  return true; }

	virtual bool mouseMoved (const OIS::MouseEvent &arg) { return true; }

	virtual bool mousePressed (const OIS::MouseEvent &arg, OIS::MouseButtonID id) { return true; }

	virtual bool mouseReleased (const OIS::MouseEvent &arg, OIS::MouseButtonID id) { return true; }

	virtual ~Rendering();

protected:
	void initRendering(const std::string &name, const Ogre::SceneTypeMask typeMask);

	void initInputOutput();
};

#endif /* RENDERING_H_ */
