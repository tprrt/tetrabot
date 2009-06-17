/**
 * \file WorldInfo.h
 * \brief Définition des caractéristiques du monde physique virtuel.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef WORLDINFO_H
#define WORLDINFO_H

#include "Vector3Gen.h"
/**
* \class WorldInfo
* \brief Classe décrivant les limites du monde dans lequel la physique s'applique ainsi que la gravité.
	La zone où la physique est présente est définie par deux points.
*/
class WorldInfo {

protected:
	Vector3Gen *min;/** < min : Point représentant la limite inférieur dans laquelle la physique doit s'appliquer.*/
	Vector3Gen *max;/** < max : Point représentant la limite supérieur dans laquelle la physique doit s'appliquer.*/
	Vector3Gen *gravity;/** < gravity : Vecteur définissant la gravité.*/

public:
	/**
	* \fn WorldInfo(Vector3Gen *min, Vector3Gen *max, Vector3Gen *gravity);
	* \brief Constructeur créant une définition du monde.
	* \param [min] : Point représentant la limite inférieur du monde dans lequel la physique doit s'appliquer.
	* \param [max] : Point représentant la limite supérieur du monde dans lequel la physique doit s'appliquer.
	* \param [gravity] : Vecteur définissant la gravité du monde.
	*/
	WorldInfo(Vector3Gen *min, Vector3Gen *max, Vector3Gen *gravity);

	//virtual ~WorldInfo();
	/**
	* \fn const Vector3Gen *getMin() const;
	* \brief getter
	* \return Borne inférieur du monde.
	*/
	const Vector3Gen *getMin() const;

	/**
	* \fn const Vector3Gen *getMax() const;
	* \brief getter
	* \return Borne supérieur du monde.
	*/
	const Vector3Gen *getMax() const;

	/**
	* \fn const Vector3Gen *getGravity() const;
	* \brief getter
	* \return Retourne la gravité sous la forme d'un vecteur.
	*/
	const Vector3Gen *getGravity() const;
};

#endif /* WORLDINFO_H */
