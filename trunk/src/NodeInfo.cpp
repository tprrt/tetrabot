//  @ Project : Tetrabot
//  @ File Name : NodeInfo.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
#include "NodeInfo.h"

//Constructeur de la classe NodeInfo
NodeInfo::NodeInfo(const float weight, const float radius) : ComponentInfo(weight) {

	if(radius < 0) {
		throw std::invalid_argument("Node radius something less 0");
	}
	this->radius = radius;
}

// Retourne le radius
const float NodeInfo::getRadius() const {
	return this->radius;
}

