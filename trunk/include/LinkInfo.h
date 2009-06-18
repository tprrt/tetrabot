/**
 * \file LinkInfo.h
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef LINKINFO_H
#define LINKINFO_H

#include <stdexcept>

#include "NodeInfo.h"
#include "EdgeInfo.h"

/**
 * \class LinkInfo
 */
class LinkInfo {

protected:
	// node : noeud
	NodeInfo *node; /**< nœud */
	//
	EdgeInfo *edge; /**< arc */

public:
	//Controleur de la classe LinkInfo
	/**
	 * \fn LinkInfo(NodeInfo *node, EdgeInfo *egde)
	 * \brief Constructeur de la classe LinkInfo
	 * \param node Le nœud
	 * \param edge L'arc
	 */
	LinkInfo(NodeInfo *node, EdgeInfo *egde);

	//virtual ~Link();
	// Retourne le noeud courant
	/**
	 * \fn const NodeInfo getNode() const
	 * \brief getter
	 * \return Le nœud courant
	 */
	const NodeInfo getNode() const;
	// Retourne le edge courant
	/**
	 * \fn const EdgeInfo getEdge() const
	 * \brief getter
	 * \return l'arc courant
	 */
	const EdgeInfo getEdge() const;

	bool operator < (LinkInfo const & link) const;
};

#endif /* LINKINFO_H */
