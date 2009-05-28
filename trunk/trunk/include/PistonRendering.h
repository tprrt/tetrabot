#ifndef PISTON_RENDERING
#define PISTON_RENDERING

#include "Ogre.h"


class PistonRendering {

private :
	int nbC; 	// nombre de cylindres
	//std::vector<Ogre::Entity *> c;	// tableau des cylindres
	Ogre::Real lC; 	// longueur d'un cylindre
	Ogre::Real lMax; 	// longueur maximale du piston
	Ogre::Real lMin; 	// longueur minimale du piston
	Ogre::SceneManager *scene;
	int num; // le numero du piston

public :
	// Constructeur
	/**
	 * @param lMin : longueur minimum du piston
	 * @param lMax : longueur maximale du piston
	 * @param scene : le scenemanager de Ogre
	 * @param numPis : le numero du piston
	 **/
	PistonRendering(Ogre::Real lMin, Ogre::Real lMax, Ogre::SceneManager *scene, int numPis) ;

	/**
	 * @param b1 : la boule à une extrémité du piston, à partir de laquelle on calcule la position des cylindre
	 * @param b2 : la boule à l'autre extrémité du piston
	**/
	void afficherPiston(Ogre::SceneNode *b1, Ogre::SceneNode *b2) ;

};

#endif
