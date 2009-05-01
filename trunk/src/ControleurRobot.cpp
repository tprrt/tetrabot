#include "ControleurRobot.h"


// pour les fonctions rand() et srand(...)
#include "stdlib.h"
// redefinition de la constante RAND_MAX
#define RAND_MAX 0xffff 

ControleurRobot::ControleurRobot(Robot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax)
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


ControleurRobot::ControleurRobot(Robot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus)
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


Robot* ControleurRobot::getRobot()
{
	return this->robot;
}


btAlignedObjectArray<Sinusoide*> ControleurRobot::getTabSin()
{
	return this->tabSin;
}


int ControleurRobot::getEtape()
{
	return this->etape;
}



void ControleurRobot::execute(int numEtape)
{
	btScalar longueurTMP;
	int nbSin = this->tabSin.size();
	this->etape = numEtape;
	if(numEtape==0)
	{
		// etape 0: (ré)initialisation des stats
		this->posInitial = this->robot->getCenterOfMassPosition();
	}
	for(int i=0;i<nbSin;i++)
	{
		// Calcul de la longueur de l'Arc i
		longueurTMP = (robot->Arcs[i]->getTailleMax()+ robot->Arcs[i]->getTailleMin())/btScalar(2.F);
		longueurTMP+= this->tabSin[i]->sinus(etape);

		// On controle que la longueur calculée soit correcte
		if(longueurTMP < robot->Arcs[i]->getTailleMin())
		{
			longueurTMP = robot->Arcs[i]->getTailleMin();
		}
		else if(longueurTMP > robot->Arcs[i]->getTailleMax())
		{
			longueurTMP = robot->Arcs[i]->getTailleMax();
		}
		// Creation de l'action
		this->tabAction[i]->setPiston(robot->Arcs[i]);
		this->tabAction[i]->setTailleVoulu(longueurTMP);
		// Creation d'un Thread
		Thread((void*)tabAction[i],actionThread);

	}
}

void ControleurRobot::updateResultat()
{
	btScalar distance;
	// Calcul de la distance parcouru
	distance = this->posInitial.distance(this->robot->getCenterOfMassPosition());

	// creation du resultat
	this->resultat->setDistance(distance);
}

Resultat* ControleurRobot::getResultat()
{
	return this->resultat;
}

int ControleurRobot::getID()
{
	return this->id;
}

void ControleurRobot::setID()
{
	static int ID=0;
	this->id = ID;
	ID++;
}