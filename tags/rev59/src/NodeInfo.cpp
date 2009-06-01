#include "NodeInfo.h"

NodeInfo::NodeInfo(const float weight, const float radius) : ComponentInfo(weight) {

	if(radius < 0) {
		throw std::invalid_argument("Node radius something less 0");
	}
	this->radius = radius;
}

const float NodeInfo::getRadius() const {
	return this->radius;
}

