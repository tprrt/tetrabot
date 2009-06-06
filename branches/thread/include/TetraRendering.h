/*
 * Test.h
 *
 *  Created on: 24 févr. 2009
 *      Author: Thomas Perrot
 */

#ifndef TETRA_RENDERING_H_
#define TETRA_RENDERING_H_

#include "characteristics.h"
#include "Vector3Gen.h"

#include "Rendering.h"
#include "PistonRendering.h"

#include "RobotTetra.h"
#include "PhysicWorld.h"
#include "WorldInfo.h"

class TetraRendering : public Rendering {

protected:

	RobotTetra* robot;
	PhysicWorld* physicWorld;

	std::vector<PistonRendering *> pistons;

	bool leftMousePressed;
	bool rightMousePressed;

public:
	TetraRendering();

	bool keyPressed(const OIS::KeyEvent &e);

	//bool keyReleased(const OIS::KeyEvent &evt);

	bool mouseMoved (const OIS::MouseEvent &evt);

	bool mousePressed (const OIS::MouseEvent &evt, const OIS::MouseButtonID id);

	bool mouseReleased (const OIS::MouseEvent &evt, const OIS::MouseButtonID id);

	virtual ~TetraRendering();

	void createScene();

	const Ogre::SceneManager *getSceneManager(void) const;

	bool frameStarted(const Ogre::FrameEvent & evt);


};

#endif /* TETRA_RENDERING_H_ */

