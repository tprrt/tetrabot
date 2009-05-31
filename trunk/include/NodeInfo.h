#ifndef NODEINFO_H
#define NODEINFO_H

#include "ComponentInfo.h"

class NodeInfo : public ComponentInfo {

protected:
	float radius;

public:
	NodeInfo(const float weight, const float radius);

	//virtual ~Node();

	const float getRadius() const;

};

#endif /* NODE_H */
