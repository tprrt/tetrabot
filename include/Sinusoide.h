/**
 * \file Sinusoide.h
 * \brief Définition d'une sinusoide.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef SINUSOIDE_H
#define SINUSOIDE_H

#include "characteristics.h"
#include "btBulletDynamicsCommon.h"
/**
* \class Sinusoide
* \brief Permet de définir une sinusoide de par sa période, son amplitude et son déphasage.
*/
class Sinusoide
{
protected:
	btScalar periode;/** < periode : Période de la sinusoide. */
	btScalar amplitude;/** < amplitude : Amplitude de la sinusoide. */
	btScalar dephasage;/** < dephasage : Déphasage de la sinusoide. */
public:

	/**
	* \fn Sinusoide(btScalar periode, btScalar amplitude, btScalar dephasage);
	* \brief Constructeur.
	* \param [periode] : Période de la sinusoide. 
	* \param [amplitude] : Amplitude de la sinusoide.
	* \param [dephasage] : Déphasage de la sinusoide. 
	*/
	Sinusoide(btScalar periode, btScalar amplitude, btScalar dephasage);

	/**
	* \fn Sinusoide(const Sinusoide& s);
	* \brief Constructeur par copie d'une sinusoide existante.
	* \param [s] : Sinusoide à copier.
	*/
	Sinusoide(const Sinusoide& s);

	/**
	* \fn virtual ~Sinusoide();
	* \brief Destructeur.
	*/
	virtual ~Sinusoide();

	/**
	* \fn btScalar getPeriode();
	* \brief getter
	* \return Période de la sinusoide.
	*/
	btScalar getPeriode();

	/** 
	* \fn btScalar getAmplitude();
	* \brief getter
	* \return Amplitude de la sinusoide.
	*/
	btScalar getAmplitude();

	/**
	* \fn btScalar getDephasage();
	* \brief getter
	* \return Déphasage de la sinusoide.
	*/
	btScalar getDephasage();

	/**
	* \fn void setPeriode(btScalar p);
	* \brief setter
	* \param [p] : Nouvelle période de la sinusoide.
	*/
	void setPeriode(btScalar p);

	/**
	* \fn void setAmplitude(btScalar a);
	* \brief setter
	* \param [a] : Nouvelle amplitude de la sinusoide.
	*/
	void setAmplitude(btScalar a);

	/**
	* \fn void setDephasage(btScalar d);
	* \brief setter
	* \param [d] : Nouveau déphasage de la sinusoide.
	*/
	void setDephasage(btScalar d);

	/**
	* \fn btScalar sinus(btScalar angle);
	* \brief Méthode permettant de calculer le sinus de la sinusoide à partir d'un angle.
	* \param [angle] : angle en radian.
	* \return Sinus de l'angle passé en paramètre.
	*/
	btScalar sinus(btScalar angle);

};
#endif
