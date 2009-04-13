#include "Robot_Tetra.h"
#include "Caracteristiques.h"

Robot_Tetra::Robot_Tetra(btDynamicsWorld* world,Ogre::SceneManager * scene)
{
	// Création des boules
	for(int i=0;i<4;i++)
	{
		char nom[20] ;
		sprintf(nom,"NodeBoule%d",(i+1));
		this->Sommets.expand(new Boule(world,scene->getSceneNode(nom),btVector3(750.F, 250.F, 750.F),RAYON_BOULE,POIDS_BOULE));
	}
	// Création des pistons
	for(int i=0;i<6;i++)
	{
		this->Arcs.expand(new Piston(world,NULL,btVector3(750.F, 250.F, 750.F),PISTON_TAILLE_MIN,PISTON_TAILLE_MAX,VELOCITE_PISTON));
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

void Robot_Tetra::deplacer()
{
	printf("deplacement\n");
}