/*
	Définition de la classe abstraite Robot.
Cette classe contiendra tout les éléments du robot ainsi que les actions associes au robot.
Comme les robots peuvent etre differents, les actions sont des methodes VIRTUELLES PURES
*/
#ifndef ROBOT_H
#define ROBOT_H

#include "LinearMath/btAlignedObjectArray.h"

template<class S,class A>
class Robot{
public:
	// Attribut decrivant le robot
	btAlignedObjectArray<S> Sommets;
	btAlignedObjectArray<A> Arcs;
	
	// Le constructeur
	Robot()
	{
	}
	// Le destructeur
	~Robot()
	{
		Sommets.clear();
		Arcs.clear();
	};
	// Methodes
	virtual void deplacer()=0;
};
#endif