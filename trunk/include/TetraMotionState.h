#ifndef TETRAMOTIONSTATE_H
#define TETRAMOTIONSTATE_H

#include <LinearMath/btMotionState.h>
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include <Ogre.h>
#else
#include <OGRE/Ogre.h>
#endif

class TetraMotionState : public btMotionState 
{
public:
	TetraMotionState(const btTransform &initialpos, Ogre::SceneNode *node) 
	{
		mVisibleobj = node;
		mPos1 = initialpos;
	}
	virtual ~TetraMotionState()
	{ 
	}
	void setNode(Ogre::SceneNode *node) 
	{
		mVisibleobj = node;
	}
	virtual void getWorldTransform(btTransform &worldTrans) const 
	{
		worldTrans = mPos1;
	}
	virtual void setWorldTransform(const btTransform &worldTrans) 
	{
		if(NULL == mVisibleobj) return; // silently return before we set a node
		btQuaternion rot = worldTrans.getRotation();
		mVisibleobj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
		btVector3 pos = worldTrans.getOrigin();
		mVisibleobj->setPosition(pos.x(), pos.y(), pos.z());
	}
protected:
	Ogre::SceneNode *mVisibleobj;
	btTransform mPos1;
};
#endif
