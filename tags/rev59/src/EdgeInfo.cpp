#include "EdgeInfo.h"

EdgeInfo::EdgeInfo(const float weight, const float minSize, const float maxSize) : ComponentInfo(weight) {

	if(minSize < 0) {
		throw std::invalid_argument("Edge min size something less 0");
	}
	this->minSize = minSize;

	if(maxSize < minSize) {
		throw std::invalid_argument("Edge max size something less Edge min size");
	}
	this->maxSize = maxSize;
}

const float EdgeInfo::getMinSize() const {
	return this->minSize;
}

const float EdgeInfo::getMaxSize() const {
	return this->maxSize;
}

