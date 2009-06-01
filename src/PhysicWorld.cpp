#include "WorldInfo.h"

WorldInfo::WorldInfo(Vector3Gen *min, Vector3Gen *max, Vector3Gen *gravity) {

	this->min = min;
	this->max = max;
	this->gravity = gravity;
}

const Vector3Gen *WorldInfo::getMin() const {
	return this->min;
}

const Vector3Gen *WorldInfo::getMax() const {
	return this->max;
}

const Vector3Gen *WorldInfo::getGravity() const {
	return this->gravity;
}
