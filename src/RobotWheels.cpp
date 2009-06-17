#include "RobotWheels.h"

RobotWheels::RobotWheels(btDynamicsWorld* world,const btVector3& posInit)
{
	PhysicNoeud* bouleTMP;
	PhysicPiston* pistonTMP;
	// le vecteur decalage sert à espacer les objets
	// pour eviter d'eventuelles erreurs de collisions
	btVector3 decalage; 
	// Création des 6 boules
	for(int i=0;i<8;i++)
	{
		decalage = btVector3(NODE_RADIUS*i*2,0,0);
		bouleTMP = new PhysicNoeud(world,new btSphereShape(NODE_RADIUS)/*new btConeShapeX(NODE_RADIUS,btScalar(3.F))*/,posInit+decalage,NODE_WEIGHT);
		this->Sommets.expand(bouleTMP);
	}

	for(int i=8;i<10;i++)
	{
		decalage = btVector3(NODE_RADIUS*i*2,0,0);
		bouleTMP = new PhysicNoeud(world,new btCylinderShapeZ(btVector3(3.F,5.F,3.F)),posInit+decalage,NODE_WEIGHT*0.5);
		this->Sommets.expand(bouleTMP);
	}
	// Création des pistons liant les boules
	for(int i=0;i<8;i++)
	{
		decalage = btVector3(0,0,5*i+15);
		pistonTMP = new PhysicPiston(world,posInit+decalage,3,10,EDGE_VELOCITY);
		pistonTMP->lock();
		this->Arcs.expand(pistonTMP);
	}

	for(int i=8;i<16;i++)
	{
		decalage = btVector3(0,0,5*i+15);
		pistonTMP = new PhysicPiston(world,posInit+decalage,3,8,EDGE_VELOCITY);
		pistonTMP->lock();
		this->Arcs.expand(pistonTMP);
	}
	
	pistonTMP = new PhysicPiston(world,posInit+decalage,3,7,EDGE_VELOCITY);
	pistonTMP->lock();
	this->Arcs.expand(pistonTMP);

	btScalar angle1 = btScalar(0);
	btScalar angle2 = btScalar(M_PI_2);
	btScalar angle3 = btScalar(M_PI/3.F);
	btScalar angle4 = btScalar(M_PI_4);
	// Roue n°1
	for(int i=0;i<4;i++)
	{
		this->Sommets[i]->linkEdge(Arcs[i],'B',0,angle1);
		this->Sommets[i]->linkEdge(Arcs[(i+1)%4],'A',0,angle2);
		this->Sommets[i]->linkEdge(Arcs[(i+8)],'A',angle4,angle2);
		this->Sommets[8]->linkEdge(Arcs[(i+8)],'B',2*angle3,angle2*i);
	}
	// Roue n°2
	for(int i=4;i<8;i++)
	{
		this->Sommets[i]->linkEdge(Arcs[i],'B',0,angle1);
		this->Sommets[i]->linkEdge(Arcs[(i-3)%4+4],'A',0,angle2);
		this->Sommets[i]->linkEdge(Arcs[(i+8)],'A',angle4,angle4);
		this->Sommets[9]->linkEdge(Arcs[(i+8)],'B',2*angle3,angle2*i);
	}
	
	//liaison des roues
	this->Sommets[8]->linkEdge(Arcs[16],'A',-M_PI_2,0);
	this->Sommets[9]->linkEdge(Arcs[16],'B',-M_PI_2,0);
	
	
	for(int i=0;i<this->Arcs.size()-1;i++)
	{
		pistonTMP = (PhysicPiston*) Arcs[i];
		pistonTMP->getConeA()->setLimit(0,0,0);
		pistonTMP->getConeB()->setLimit(0,0,0);
	}
	// Permettre rotation des roues
	pistonTMP = (PhysicPiston*) Arcs[this->Arcs.size()-1];
	pistonTMP->getConeA()->setLimit(0,0,M_PI);
	pistonTMP->getConeB()->setLimit(0,0,0);

	// Translation
	this->translate(posInit);

}

btVector3 RobotWheels::getCenterOfMassPosition()
{
	btVector3 centre = btVector3(0,0,0);
	int nbNoeuds = this->Sommets.size();
	for(int i=0;i<nbNoeuds;i++)
	{
		centre+= this->Sommets[i]->getCenterOfMassPosition();
	}
	if(nbNoeuds>0) return (centre/btScalar(nbNoeuds));
	else return btVector3(0,0,0);

}

void RobotWheels::translate(const btVector3& to) {

	btVector3 translation = (to - this->getCenterOfMassPosition());
	int nbSommets = this->Sommets.size();
	for(int i=0;i<nbSommets;i++) {
		this->Sommets[i]->translate(translation);
	}
}