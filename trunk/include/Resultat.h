/**
 * \file Resultat.h
 * \brief Classe répertoriant différents résultats d'un sujet d'étude.
	Dans notre cas, le sujet d'étude est un robot.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef RESULTAT_H
#define RESULTAT_H

#include "btBulletDynamicsCommon.h"
/**
* \class Resultat
* \brief Classe répertoriant différents résultats d'un robot. Pour l'instant, cette classe ne contient que la distance parcouru par un sujet d'étude.
*/
class Resultat {

protected:
	btScalar distance;/** < distance : distance parcouru par un sujet d'étude.*/

	int id;/** < id : Identificateur d'un résultat. La valeur de l'identificateur est laissé au choix de l'utilisateur pour faire correspondre ses sujets d'étude aux résultats.*/

public:
	/**
	* \fn Resultat(int id,btScalar distanceParcouru);
	* \brief  Constructeur
	* \param [id] : Identificateur du résultat. Laissé au choix de l'utilisateur pour faire correspondre le sujet d'étude à ce résultat.
	* \param [distanceParcouru] : distance déja parcouru par le sujet d'étude.
	*/
	Resultat(int id,btScalar distanceParcouru);

	//virtual ~Resultat();

	/**
	* \fn btScalar getDistance();
	* \brief getter
	* \return Distance parcouru par le sujet d'étude.
	*/
	btScalar getDistance();

	/**
	* \fn void setDistance(btScalar distance);
	* \brief setter
	* \param [distance] :  Distance parcouru par le sujet d'étude.
	*/
	void setDistance(btScalar distance);

	/**
	* \fn int getID();
	* \brief getter
	* \return Identificateur du résultat.
	*/
	int getID();
};

#endif
