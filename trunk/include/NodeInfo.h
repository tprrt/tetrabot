//  @ Project : Tetrabot
//  @ File Name : NodeInfo.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains


#ifndef NODEINFO_H
#define NODEINFO_H

#include "ComponentInfo.h"

class NodeInfo : public ComponentInfo {

protected:
	// radius : rayon d une sphere
	float radius;

public:
	//Constructeur de la classe NodeInfo
	NodeInfo(const float weight, const float radius);

	//virtual ~Node();
	// Retourne le radius 
	const float getRadius() const;

};

#endif /* NODE_H */
