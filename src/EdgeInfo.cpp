//  @ Project : Tetrabot
//  @ File Name : EdgeInfo.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "EdgeInfo.h"

//Constructeur de la classe EdgeInfo
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

// Retourne le minimum d un edge
const float EdgeInfo::getMinSize() const {
	return this->minSize;
}

// Retourne le maximum d un edge
const float EdgeInfo::getMaxSize() const {
	return this->maxSize;
}

