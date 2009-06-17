//  @ Project : Tetrabot
//  @ File Name : ComponentInfo.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains


#include "ComponentInfo.h"

// Constructeur de la classe ComponentInfo
ComponentInfo::ComponentInfo(const float weight) {

	static int num = 0;

	if(weight < 0) {
		throw std::invalid_argument("Component weight something less 0");
	}
	this->weight = weight;

	this->id = num;
	num ++;
}

// Retourne l' attribut id ( identifieur )
const int ComponentInfo::getId() const {
	return this->id;
}

// Retourne l' attibut weight ( son poids )
const float ComponentInfo::getWeight() const {
	return this->weight;
}


