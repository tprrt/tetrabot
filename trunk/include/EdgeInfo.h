//  @ Project : Tetrabot
//  @ File Name : EdgeInfo.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains


#ifndef EDGEINFO_H
#define EDGEINFO_H

#include "ComponentInfo.h"

class EdgeInfo : public ComponentInfo {

protected:
	float minSize;

	float maxSize;

public:
	EdgeInfo(const float weight, const float minSize, const float maxSize);

	//virtual ~Edge();

	const float getMinSize() const;

	const float getMaxSize() const;

};

#endif /* EDGEINFO_H */
