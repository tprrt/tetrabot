#include "Robot_Tetra.h"
#include "Caracteristiques.h"

Robot_Tetra::Robot_Tetra(btDynamicsWorld* world,Ogre::SceneManager * scene,const btVector3& posInit)
{
	Piston* pistonTMP;
	Noeud* bouleTMP;
	// le vecteur decalage sert à espacer les objets
	// pour eviter d'eventuelles erreurs de collisions
	btVector3 decalage;
	
	// Création des boules
	for(int i=0;i<4;i++)
	{
		decalage = btVector3(RAYON_BOULE*i*2,0,0);
		char nom[20] ;
		sprintf(nom,"NodeNoeud%d",(i+1));
		bouleTMP = new Noeud(world,scene->getSceneNode(nom),new btSphereShape(RAYON_BOULE),posInit+decalage,POIDS_BOULE);
		this->Sommets.expand(bouleTMP);
	}
	// Création des pistons
	for(int i=0;i<6;i++)
	{
		decalage = btVector3(0,0,5*i+15);
		pistonTMP = new Piston(world,NULL,posInit+decalage,PISTON_TAILLE_MIN,PISTON_TAILLE_MAX,VELOCITE_PISTON);
		pistonTMP->bloquerPiston();
		this->Arcs.expand(pistonTMP);
	}
	// On lie les pistons aux boules
	btScalar angle1 = btScalar(M_PI_4*(4.F/3.F));
	for(int i=0;i<3;i++)
	{
		this->Sommets[0]->lierPiston(Arcs[i],'A',angle1,(i*2*M_PI)/3);
	}
	this->Sommets[1]->lierPiston(Arcs[1],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[1]->lierPiston(Arcs[3],'A',angle1,(1*2*M_PI)/3);
	this->Sommets[1]->lierPiston(Arcs[4],'A',angle1,(2*2*M_PI)/3);

	this->Sommets[2]->lierPiston(Arcs[0],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[2]->lierPiston(Arcs[5],'B',angle1,(1*2*M_PI)/3);
	this->Sommets[2]->lierPiston(Arcs[3],'B',angle1,(2*2*M_PI)/3);

	this->Sommets[3]->lierPiston(Arcs[2],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[3]->lierPiston(Arcs[4],'B',angle1,(1*2*M_PI)/3);
	this->Sommets[3]->lierPiston(Arcs[5],'A',angle1,(2*2*M_PI)/3);

}

Robot_Tetra::Robot_Tetra(btDynamicsWorld* world,const btVector3& posInit)
{
	Noeud* bouleTMP;
	Piston* pistonTMP;
	// le vecteur decalage sert à espacer les objets
	// pour eviter d'eventuelles erreurs de collisions
	btVector3 decalage; 
	// Création des boules
	for(int i=0;i<4;i++)
	{
		decalage = btVector3(RAYON_BOULE*i*2,0,0);
		bouleTMP = new Noeud(world,new btSphereShape(RAYON_BOULE),posInit+decalage,POIDS_BOULE);
		this->Sommets.expand(bouleTMP);
	}
	// Création des pistons
	for(int i=0;i<6;i++)
	{
		decalage = btVector3(0,0,5*i+15);
		pistonTMP = new Piston(world,posInit+decalage,PISTON_TAILLE_MIN,PISTON_TAILLE_MAX,VELOCITE_PISTON);
		//pistonTMP->bloquerPiston();
		this->Arcs.expand(pistonTMP);
	}
	// On lie les pistons aux boules
	btScalar angle1 = btScalar(M_PI_4*(4.F/3.F));
	for(int i=0;i<3;i++)
	{
		this->Sommets[0]->lierPiston(Arcs[i],'A',angle1,(i*2*M_PI)/3);
	}
	this->Sommets[1]->lierPiston(Arcs[1],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[1]->lierPiston(Arcs[3],'A',angle1,(1*2*M_PI)/3);
	this->Sommets[1]->lierPiston(Arcs[4],'A',angle1,(2*2*M_PI)/3);

	this->Sommets[2]->lierPiston(Arcs[0],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[2]->lierPiston(Arcs[5],'B',angle1,(1*2*M_PI)/3);
	this->Sommets[2]->lierPiston(Arcs[3],'B',angle1,(2*2*M_PI)/3);

	this->Sommets[3]->lierPiston(Arcs[2],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[3]->lierPiston(Arcs[4],'B',angle1,(1*2*M_PI)/3);
	this->Sommets[3]->lierPiston(Arcs[5],'A',angle1,(2*2*M_PI)/3);
}


btVector3 Robot_Tetra::getCenterOfMassPosition()
{
	btVector3 centre = btVector3(0,0,0);
	int nbNoeuds = this->Sommets.size();
	for(int i=0;i<nbNoeuds;i++)
	{
		centre+= this->Sommets[i]->getBody()->getCenterOfMassPosition();
	}
	if(nbNoeuds>0) return (centre/btScalar(nbNoeuds));
	else return btVector3(0,0,0);

}