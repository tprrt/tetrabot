//  @ Project : Tetrabot
//  @ File Name : LinkInfo.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef LINKINFO_H
#define LINKINFO_H

#include <stdexcept>

#include "NodeInfo.h"
#include "EdgeInfo.h"

class LinkInfo {

protected:
	// node : noeud
	NodeInfo *node;
	//
	EdgeInfo *edge;

public:
	//Controleur de la classe LinkInfo
	LinkInfo(NodeInfo *node, EdgeInfo *egde);

	//virtual ~Link();
	// Retourne le noeud courant
	const NodeInfo getNode() const;
	// Retourne le edge courant
	const EdgeInfo getEdge() const;

	bool operator < (LinkInfo const & link) const;
};

#endif /* LINKINFO_H */
