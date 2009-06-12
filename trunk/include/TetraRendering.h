#ifndef TETRA_RENDERING_H_
#define TETRA_RENDERING_H_

/**
 * \file TetraRendering.h
 * \author Frozen Brains
 * \brief Gestion de l'affichage d'un robot tétraédrique sous Ogre
 * \version 0.1
 */

#include "characteristics.h"
#include "Vector3Gen.h"

#include "Rendering.h"
#include "PistonRendering.h"

#include "RobotTetra.h"
#include "PhysicWorld.h"
#include "WorldInfo.h"

/**
 * \class TetraRendering
 * \brief Classe gérant l'affichage d'un robot tétraédrique sous ogre
 */
class TetraRendering : public Rendering {

protected:

	RobotTetra* robot;
	PhysicWorld* physicWorld;

	std::vector<PistonRendering *> pistons;

	Ogre::Real pitchValue;
	Ogre::Real yawValue;

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

