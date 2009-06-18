/**
 * \file ComponentInfo.h
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef COMPONENTINFO_H
#define COMPONENTINFO_H

#include <stdexcept>

/**
 * \class ComponentInfo
 */
class ComponentInfo {

protected:
	// id : identifieur de l'objet
	int id; /**< Identifiant de l'objet */
	// weight : poids de l'objet
	float weight; /**< Poids de l'objet */

public:
	// Constructeur de la classe ComponentInfo
	/**
	 * \fn ComponentInfo(const float weight)
	 * \brief Constructeur de la classe ComponentInfo
	 * \param weight Poids de l'objet
	 */
	ComponentInfo(const float weight);

	//virtual ~ComponentInfo();

	// Retourne l' attribut id ( identifieur )
	/**
	 * \fn const int getId() const
	 * \brief getter
	 * \return Identifiant de l'objet
	 */
	const int getId() const;
	// Retourne l' attibut weight ( son poids )
	/**
	 * \fn const float getWeight() const
	 * \brief getter
	 * \return Poids de l'objet
	 */
	const float getWeight() const;

};

#endif /* COMPONENTINFO_H */
