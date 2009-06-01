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

class TetraRendering : public Rendering {

protected:

<<<<<<< .mine
	RobotTetra* robot;
	PhysicWorld* physicWorld;
=======
	RobotTetra *robot;
	WorldPhysic *physicWorld;

>>>>>>> .r67
	std::vector<PistonRendering *> pistons;

	bool leftMousePressed;
	bool rightMousePressed;

public:
	TetraRendering();

	bool keyPressed(const OIS::KeyEvent &e);

	bool mouseMoved (const OIS::MouseEvent &arg);

	bool mousePressed (const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	virtual ~TetraRendering();

	void createScene();

	Ogre::SceneManager *getSceneManager(void);

	bool frameStarted(const Ogre::FrameEvent & evt);


};

#endif /* TETRA_RENDERING_H_ */

