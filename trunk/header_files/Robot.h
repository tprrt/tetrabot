/*
	Définition de la classe abstraite Robot.
Cette classe contiendra tout les éléments du robot ainsi que les actions associes au robot.
Comme les robots peuvent etre differents, les actions sont des methodes VIRTUELLES PURES
*/
#ifndef ROBOT_H
#define ROBOT_H

#include "LinearMath/btAlignedObjectArray.h"
#include "btBulletDynamicsCommon.h"
#include "Composant.h"
#include "Piston.h"
#include "Noeud.h"

class Robot{
public:
	// Attribut decrivant le robot
	btAlignedObjectArray<Noeud*> Sommets;
	btAlignedObjectArray<Piston*> Arcs;
protected:
	// identificateur du robot
	int id;
public:	
	// Le constructeur
	Robot()
	{
		// affectation d'un identificateur unique
		static int ID=0;
		this->id = ID;
		ID++;
	}
	// Le destructeur
	~Robot()
	{
		Sommets.clear();
		Arcs.clear();
	}

	// Les methodes
public:
	//Les methodes implementees
	int getID()
	{
		return this->id;
	}

	// Methodes à implementer 
	virtual btVector3 getCenterOfMassPosition()=0;
};
#endif