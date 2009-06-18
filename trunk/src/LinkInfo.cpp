//  @ Project : Tetrabot
//  @ File Name : LinkInfo.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "LinkInfo.h"

//Controleur de la classe LinkInfo
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

// Retourne le noeud courant
const NodeInfo LinkInfo::getNode() const {
	return *this->node;
}

// Retourne le edge courant
const EdgeInfo LinkInfo::getEdge() const {
	return *this->edge;
}


bool LinkInfo::operator < (LinkInfo const & link) const {
	return this->node->getId() < link.getNode().getId();
}

