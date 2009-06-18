#include "PhysicRobot.h"

PhysicRobot::PhysicRobot() {
		static int ID = 0;
		this->id = ID;
		ID++;
}

PhysicRobot::~PhysicRobot()
	{
		Sommets.clear();
		Arcs.clear();
}

int PhysicRobot::getID() {
	return this->id;
}


btAlignedObjectArray<PhysicVertex*> PhysicRobot::getSommets() {
	return this->Sommets;
}

PhysicVertex * PhysicRobot::getSommet(int i) {
		return this->Sommets[i];
}

btAlignedObjectArray<PhysicEdge*> PhysicRobot::getArcs() {
	return this->Arcs;
}

PhysicEdge * PhysicRobot::getArc(int i) {
		return this->Arcs[i];
}

/*
btScalar PhysicRobot::getIncremente() {
	return this->incremente;

}
*/


