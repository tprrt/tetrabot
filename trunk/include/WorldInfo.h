/**
 * \file WorldInfo.h
 * \brief D�finition des caract�ristiques du monde physique virtuel.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef WORLDINFO_H
#define WORLDINFO_H

#include "Vector3Gen.h"
/**
* \class WorldInfo
* \brief Classe d�crivant les limites du monde dans lequel la physique s'applique ainsi que la gravit�.
	La zone o� la physique est pr�sente est d�finie par deux points.
*/
class WorldInfo {

protected:
	Vector3Gen *min;/** < min : Point repr�sentant la limite inf�rieur dans laquelle la physique doit s'appliquer.*/
	Vector3Gen *max;/** < max : Point repr�sentant la limite sup�rieur dans laquelle la physique doit s'appliquer.*/
	Vector3Gen *gravity;/** < gravity : Vecteur d�finissant la gravit�.*/

public:
	/**
	* \fn WorldInfo(Vector3Gen *min, Vector3Gen *max, Vector3Gen *gravity);
	* \brief Constructeur cr�ant une d�finition du monde.
	* \param [min] : Point repr�sentant la limite inf�rieur du monde dans lequel la physique doit s'appliquer.
	* \param [max] : Point repr�sentant la limite sup�rieur du monde dans lequel la physique doit s'appliquer.
	* \param [gravity] : Vecteur d�finissant la gravit� du monde.
	*/
	WorldInfo(Vector3Gen *min, Vector3Gen *max, Vector3Gen *gravity);

	//virtual ~WorldInfo();
	/**
	* \fn const Vector3Gen *getMin() const;
	* \brief getter
	* \return Borne inf�rieur du monde.
	*/
	const Vector3Gen *getMin() const;

	/**
	* \fn const Vector3Gen *getMax() const;
	* \brief getter
	* \return Borne sup�rieur du monde.
	*/
	const Vector3Gen *getMax() const;

	/**
	* \fn const Vector3Gen *getGravity() const;
	* \brief getter
	* \return Retourne la gravit� sous la forme d'un vecteur.
	*/
	const Vector3Gen *getGravity() const;
};

#endif /* WORLDINFO_H */
