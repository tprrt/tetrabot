//  @ Project : Tetrabot
//  @ File Name : ControleurRobot.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "ControleurRobot.h"

// Constructeur de la classe ControleurRobot avec les parametres d une sinusoide
ControleurRobot::ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax)
:robot(robot),
etape(0),
posInitial(robot->getCenterOfMassPosition())
{
	// robot ne doit pas etre un pointeur NULL
	assert(robot != NULL);

	btScalar periodeTMP;
	btScalar amplitudeTMP;
	btScalar dephasageTMP;

	Sinusoide* sinusTMP;
	
	// initialiser l'identifiant
	this->setID();

	// initialiser la fonction rand si ce n'est pas deja fait!
	static bool initialisationRand = false;
	if(!initialisationRand)
	{
		srand(time(NULL));
		initialisationRand = true;
	}

	// Creation des sinusoides (une par Arc)
	int nbArcs = robot->Arcs.size();
	for(int i=0;i<nbArcs;i++)
	{
		// Creation d'une nouvelle sinusoide
		periodeTMP   = periodeMax * (btScalar(rand()) / btScalar(RAND_MAX));
		amplitudeTMP = amplitudeMax * (btScalar(rand()) / btScalar(RAND_MAX));
		dephasageTMP = dephasageMax * (btScalar(rand()) / btScalar(RAND_MAX));
		sinusTMP = new Sinusoide(periodeTMP,amplitudeTMP,dephasageTMP);

		// Ajout de la nouvelle Sinusoide
		this->tabSin.expand(sinusTMP);

	}

	// initialiser le tableau des Actions
	for(int i=0;i<nbArcs;i++)
	{
		tabAction.expand(new ActionPiston(NULL,NULL));
	}

	// initialiser un resultat
	this->resultat = new Resultat(this->id,btScalar(0.));
}

// Constructeur de la classe ControleurRobot avec un vecteur de sinusoide
ControleurRobot::ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus)
:robot(robot),
etape(0),
posInitial(robot->getCenterOfMassPosition())
{
	// robot ne doit pas etre un pointeur NULL
	assert(robot != NULL);
	// initialiser l'identifiant
	this->setID();
	// On copie le tableau tab_Sinus dans this->tabSin
	for(int i=0;i<tab_Sinus.size();i++)
	{
		this->tabSin.expand(new Sinusoide(*(tab_Sinus[i])));
	}
	// initialiser le tableau des Actions
	for(int i=0;i<robot->Arcs.size();i++)
	{
		tabAction.expand(new ActionPiston(NULL,NULL));
	}
	// initialiser un resultat
	this->resultat = new Resultat(this->id,btScalar(0.));
}


// Destructeur de l objet
ControleurRobot::~ControleurRobot(){
	for(int i=0;i<this->tabSin.size();i++){
		delete this->tabSin[i];
	}
	for(int i=0;i<this->tabAction.size();i++){
		delete this->tabAction[i];
	}
	//delete (void *)posInitial;
	delete this->resultat;
}
// Retourne le robot traitait par ce controleur
PhysicRobot* ControleurRobot::getRobot()
{
	return this->robot;
}

// Retourne un vecteur de sinusoide
btAlignedObjectArray<Sinusoide*> ControleurRobot::getTabSin()
{
	return this->tabSin;
}

// Retourne l etape courante du controleur
int ControleurRobot::getEtape()
{
	return this->etape;
}


// Methode permettant d executer une etape en particulier
void ControleurRobot::execute(int numEtape)
{
	btScalar longueurTMP;
	PhysicPiston* pistonTMP;
	int nbSin = this->tabSin.size();
	this->etape = numEtape;
	if(numEtape==0)
	{
		// etape 0: (r�)initialisation des stats
		this->posInitial = this->robot->getCenterOfMassPosition();
	}
	for(int i=0;i<nbSin;i++)
	{
		// Calcul de la longueur de l'Arc i
		pistonTMP = (PhysicPiston*) robot->Arcs[i];
		longueurTMP = (pistonTMP->getTailleMax()+ pistonTMP->getTailleMin())/btScalar(2.F);
		longueurTMP+= this->tabSin[i]->sinus(etape);

		// On controle que la longueur calcul�e soit correcte
		if(longueurTMP < pistonTMP->getTailleMin())
		{
			longueurTMP = pistonTMP->getTailleMin();
		}
		else if(longueurTMP > pistonTMP->getTailleMax())
		{
			longueurTMP = pistonTMP->getTailleMax();
		}
		// Creation de l'action
		this->tabAction[i]->setPiston(pistonTMP);
		this->tabAction[i]->setTailleVoulue(longueurTMP);
		// Creation d'un Thread
		Thread((void*)tabAction[i],actionThread);

	}
}

// Methode permettant la mise a jour du resultat
void ControleurRobot::updateResultat()
{
	btScalar distance;
	// Calcul de la distance parcouru
	distance = this->posInitial.distance(this->robot->getCenterOfMassPosition());

	// creation du resultat
	this->resultat->setDistance(distance);
}

// Retourne le resultat du controleur
Resultat* ControleurRobot::getResultat()
{
	return this->resultat;
}

//Retourne l identifieur du controleur
int ControleurRobot::getID()
{
	return this->id;
}

//Parametre l identifieur du controleur
void ControleurRobot::setID()
{
	static int ID=0;
	this->id = ID;
	ID++;
}
