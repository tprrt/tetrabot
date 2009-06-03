//  @ Project : Tetrabot
//  @ File Name : EdgeInfo.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains


#ifndef EDGEINFO_H
#define EDGEINFO_H

#include "ComponentInfo.h"

class EdgeInfo : public ComponentInfo {

protected:
	// minSize :  minimum du edge
	float minSize;
	// maxSize :  maximum du edge
	float maxSize;

public:
	//Constructeur de la classe EdgeInfo
	EdgeInfo(const float weight, const float minSize, const float maxSize);

	//virtual ~Edge();
	// Retourne le minimum d un edge
	const float getMinSize() const;
	// Retourne le maximum d un edge
	const float getMaxSize() const;

};

#endif /* EDGEINFO_H */
