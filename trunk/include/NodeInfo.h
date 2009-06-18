/**
 * \file LinkInfo.h
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef NODEINFO_H
#define NODEINFO_H

#include "ComponentInfo.h"

/**
 * \class NodeInfo
 */
class NodeInfo : public ComponentInfo {

protected:
	// radius : rayon d une sphere
	float radius; /**< Rayon d'une sphère */

public:
	//Constructeur de la classe NodeInfo
	/**
	 * \fn NodeInfo(const float weight, const float radius)
	 * \brief Constructeur de la classe NodeInfo
	 * \param weight Le poids de l'objet
	 * \param radius Le rayon de la sphere
	 */
	NodeInfo(const float weight, const float radius);

	//virtual ~Node();
	// Retourne le radius
	/**
	 * \fn const float getRadius() const
	 * \brief getter
	 * \return Le rayon de la sphere
	 */
	const float getRadius() const;

};

#endif /* NODE_H */
