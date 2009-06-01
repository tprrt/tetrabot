#include "ComponentInfo.h"

ComponentInfo::ComponentInfo(const float weight) {

	static int num = 0;

	if(weight < 0) {
		throw std::invalid_argument("Component weight something less 0");
	}
	this->weight = weight;

	this->id = num;
	num ++;
}

const int ComponentInfo::getId() const {
	return this->id;
}

const float ComponentInfo::getWeight() const {
	return this->weight;
}


