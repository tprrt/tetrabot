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
	// Methode positionnant le robot (translation)
	void translate(const btVector3& to){
		btVector3 translation = (to - this->getCenterOfMassPosition());
		int nbSommets = this->Sommets.size();
		for(int i=0;i<nbSommets;i++)
		{
			this->Sommets[i]->getBody()->translate(translation);
		}
	}
	// Methodes à implementer 
	virtual btVector3 getCenterOfMassPosition()=0;
};
#endif