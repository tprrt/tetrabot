#ifndef LINKINFO_H
#define LINKINFO_H

#include <stdexcept>

#include "NodeInfo.h"
#include "EdgeInfo.h"

class LinkInfo {

protected:
	NodeInfo *node;
	EdgeInfo *edge;

public:
	LinkInfo(NodeInfo *node, EdgeInfo *egde);

	//virtual ~Link();

	const NodeInfo getNode() const;

	const EdgeInfo getEdge() const;

	bool operator < (LinkInfo const & link) const;
};

#endif /* LINKINFO_H */
