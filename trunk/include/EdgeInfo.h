/**
 * \file EdgeInfo.h
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef EDGEINFO_H
#define EDGEINFO_H

#include "ComponentInfo.h"

/**
 * \class EdgeInfo
 */
class EdgeInfo : public ComponentInfo {

protected:
	// minSize :  minimum du edge
	float minSize; /**< longueur minimale de l'arc */
	// maxSize :  maximum du edge
	float maxSize; /**< longueur maximale de l'arc */

public:
	//Constructeur de la classe EdgeInfo
	/**
	 * \fn EdgeInfo(const float weight, const float minSize, const float maxSize)
	 * \brief Constructeur de la classe EdgeInfo
	 * \param weight Poids de l'objet
	 * \param minSize longueur minimale de l'arc
	 * \param maxSize longueur maximale de l'arc
	 */
	EdgeInfo(const float weight, const float minSize, const float maxSize);

	//virtual ~Edge();
	// Retourne le minimum d un edge
	/**
	 * \fn const float getMinSize() const
	 * \brief getter
	 * \return longueur minimale de l'arc
	 */
	const float getMinSize() const;
	// Retourne le maximum d un edge
	/**
	 * \fn const float getMaxSize() const
	 * \brief getter
	 * \return longueur maximale de l'arc
	 */
	const float getMaxSize() const;

};

#endif /* EDGEINFO_H */
