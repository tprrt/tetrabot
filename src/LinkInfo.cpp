#include "LinkInfo.h"

LinkInfo::LinkInfo(NodeInfo *node, EdgeInfo *egde) {

	if(node == NULL) {
		throw std::invalid_argument("Link node is null");
	}
	if(edge == NULL) {
		throw std::invalid_argument("Link edge is null");
	}
	this->node = node;
	this->edge = edge;
}

const NodeInfo LinkInfo::getNode() const {
	return *this->node;
}

const EdgeInfo LinkInfo::getEdge() const {
	return *this->edge;
}

bool LinkInfo::operator < (LinkInfo const & link) const {
	return this->node->getId() < link.getNode().getId();
}

