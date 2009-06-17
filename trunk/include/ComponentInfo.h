//  @ Project : Tetrabot
//  @ File Name : ComponentInfo.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <stdexcept>

class ComponentInfo {

protected:
	// id : identifieur de l'objet
	int id;
	// weight : poids de l'objet
	float weight;

public:
	// Constructeur de la classe ComponentInfo
	ComponentInfo(const float weight);

	//virtual ~ComponentInfo();

	// Retourne l' attribut id ( identifieur )
	const int getId() const;
	// Retourne l' attibut weight ( son poids )
	const float getWeight() const;

};

#endif /* COMPONENTINFO_H */
