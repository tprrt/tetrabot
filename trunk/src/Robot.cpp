#include "Robot.h"

Robot::Robot() {
		static int ID = 0;
		this->id = ID;
		ID++;
}

Robot::~Robot() {
		Sommets.clear();
		Arcs.clear();
}

int Robot::getID() {
	return this->id;
}


btAlignedObjectArray<Noeud*> Robot::getSommets() {
	return this->Sommets;
}

Noeud * Robot::getSommet(int i) {
		return this->Sommets[i];
}

btAlignedObjectArray<Piston*> Robot::getArcs() {
	return this->Arcs;
}

Piston * Robot::getArc(int i) {
		return this->Arcs[i];
}

btScalar Robot::getIncremente() {
	return this->incremente;
}

void Robot::translate(const btVector3& to) {

	btVector3 translation = (to - this->getCenterOfMassPosition());
	int nbSommets = this->Sommets.size();

	for(int i=0;i<nbSommets;i++) {
		this->Sommets[i]->getBody()->translate(translation);
	}
}


bool Robot::IsNotInArea(const btVector3 &G,const btVector3 &end2){

return (end2.distance(G) > btScalar(5.));
}

