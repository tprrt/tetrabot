/**
 * \file Resultat.h
 * \brief Classe r�pertoriant diff�rents r�sultats d'un sujet d'�tude.
	Dans notre cas, le sujet d'�tude est un robot.
 * \author Frozen Brains
 * \version 0.1
 */
#ifndef RESULTAT_H
#define RESULTAT_H

#include "btBulletDynamicsCommon.h"
/**
* \class Resultat
* \brief Classe r�pertoriant diff�rents r�sultats d'un robot. Pour l'instant, cette classe ne contient que la distance parcouru par un sujet d'�tude.
*/
class Resultat {

protected:
	btScalar distance;/** < distance : distance parcouru par un sujet d'�tude.*/

	int id;/** < id : Identificateur d'un r�sultat. La valeur de l'identificateur est laiss� au choix de l'utilisateur pour faire correspondre ses sujets d'�tude aux r�sultats.*/

public:
	/**
	* \fn Resultat(int id,btScalar distanceParcouru);
	* \brief  Constructeur
	* \param [id] : Identificateur du r�sultat. Laiss� au choix de l'utilisateur pour faire correspondre le sujet d'�tude � ce r�sultat.
	* \param [distanceParcouru] : distance d�ja parcouru par le sujet d'�tude.
	*/
	Resultat(int id,btScalar distanceParcouru);

	//virtual ~Resultat();

	/**
	* \fn btScalar getDistance();
	* \brief getter
	* \return Distance parcouru par le sujet d'�tude.
	*/
	btScalar getDistance();

	/**
	* \fn void setDistance(btScalar distance);
	* \brief setter
	* \param [distance] :  Distance parcouru par le sujet d'�tude.
	*/
	void setDistance(btScalar distance);

	/**
	* \fn int getID();
	* \brief getter
	* \return Identificateur du r�sultat.
	*/
	int getID();
};

#endif
