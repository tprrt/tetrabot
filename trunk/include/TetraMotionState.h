#ifndef TETRAMOTIONSTATE_H
#define TETRAMOTIONSTATE_H

#include "LinearMath/btMotionState.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "Ogre.h"
#else
#include <OGRE/Ogre.h>
#endif

class TetraMotionState : public btMotionState 
{

protected:
	Ogre::SceneNode *mVisibleobj;
	btTransform mPos1;

public:
	TetraMotionState(const btTransform &initialpos, Ogre::SceneNode *node);
	//virtual ~TetraMotionState();

	void setNode(Ogre::SceneNode *node);

	virtual void getWorldTransform(btTransform &worldTrans) const;

	virtual void setWorldTransform(const btTransform &worldTrans);

};
#endif /* TETRAMOTIONSTATE_H */
