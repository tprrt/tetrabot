/*
 * Test.h
 *
 *  Created on: 24 févr. 2009
 *      Author: pantoufle
 */

#ifndef TETRA_RENDERING_H_
#define TETRA_RENDERING_H_

#include "Rendering.h"
#include "Robot_Tetra.h"

class TetraRendering : public Rendering {

public:
	bool shiftLeftPressed;
	Robot_Tetra * robotPhysic;
	btDiscreteDynamicsWorld * Monde;


public:
	TetraRendering();

	bool keyPressed(const OIS::KeyEvent &e);

	bool mouseMoved (const OIS::MouseEvent &arg);

	virtual ~TetraRendering();

	void createScene();

	Ogre::SceneManager *getSceneManager(void);

	bool frameStarted(const Ogre::FrameEvent & evt);


};

#endif /* TETRA_RENDERING_H_ */

