#ifndef PISTON_RENDERING
#define PISTON_RENDERING

/**
 * \file PistonRendering.h
 * \brief Gère l'affichage des pistons
 * \author Frozen Brains
 * \version 0.1
 */

#include "Ogre.h"
#include "characteristics.h"

/**
 * \class PistonRendering
 * \brief Classe gérant l'affichage d'un piston entre deux nœuds
 */
class PistonRendering {

private :
	//ATTRIBUTS
	int nbC; 	/**< Nombre de cylindres */

	Ogre::Real lC; 	/**< Longueur d'un cylindre */

	Ogre::Real lMax; 	/**< Longueur maximale du piston */

	Ogre::Real lMin; 	/**< Longueur minimale du piston */

	Ogre::SceneManager *scene; /**< La scène dans laquelle on affiche le piston */

	int num; /**< Le numéro du piston */

public :
	//METHODES

	/**
	 * \fn PistonRendering(Ogre::Real lMin, Ogre::Real lMax, Ogre::SceneManager *scene, int numPis)
	 * \brief Constructeur
	 * \param lMin Longueur minimum du piston
	 * \param lMax Longueur maximale du piston
	 * \param scene  Le scenemanager de Ogre
	 * \param numPis Le numéro du piston
	 */
	PistonRendering(Ogre::Real lMin, Ogre::Real lMax, Ogre::SceneManager *scene, int numPis) ;


	virtual ~PistonRendering();

	/**
	 * \fn void afficherPiston(Ogre::SceneNode *b1, Ogre::SceneNode *b2) ;
	 * \brief Fonction permettant d'afficher le piston entre deux nœuds
	 * \param b1 Le nœud à une extrémité du piston, à partir duquel on calcule la position des cylindres
	 * \param b2 Le nœud à l'autre extrémité du piston
	 */
	void afficherPiston(Ogre::SceneNode *b1, Ogre::SceneNode *b2) ;

};

#endif
