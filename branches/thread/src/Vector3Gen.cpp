#include "Vector3Gen.h"

Vector3Gen::Vector3Gen(const float x, const float y, const float z) {

	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3Gen::Vector3Gen(Ogre::Vector3 vector) {

	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
}

Vector3Gen::Vector3Gen(btVector3 vector) {

	this->x = vector.x();
	this->y = vector.y();
	this->z = vector.z();
}

const btVector3 Vector3Gen::toBtVector3() const {

	btVector3 vector = btVector3(btScalar(this->x), btScalar(this->y), btScalar(this->z));
	return(vector);
}

const Ogre::Vector3 Vector3Gen::toVector3() const {

	Ogre::Vector3 vector = Ogre::Vector3(this->x, this->y, this->z);
	return(vector);
}
