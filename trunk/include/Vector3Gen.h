#ifndef VECTOR3GEN_H
#define VECTOR3GEN_H

#include "btBulletDynamicsCommon.h"
#include <Ogre.h>

class Vector3Gen {

public:
	float x;
	float y;
	float z;

public:
	Vector3Gen(const float x, const float y, const float z);

	Vector3Gen(Ogre::Vector3 vector);

	Vector3Gen(btVector3 vector);

	const btVector3 toBtVector3()const;

	const Ogre::Vector3 toVector3() const;

};

#endif /* VECTOR3GEN_H */
