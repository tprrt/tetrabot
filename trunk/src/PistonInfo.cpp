#include "PistonInfo.h"

PistonInfo::PistonInfo(const float weight, const float minSize, const float maxSize, const float velocity, const float strength) : EdgeInfo(weight, minSize, maxSize) {

	if(velocity < 0) {
		throw std::invalid_argument("Piston velocity something less 0");
	}
	this->velocity = velocity;

	if(strength < 0) {
		throw std::invalid_argument("Piston strength something less 0");
	}
	this->strength = strength;
}


const float PistonInfo::getVelocity() const {
	return this->velocity;
}

const float PistonInfo::getStrenght() const {
	return this->strength;
}

