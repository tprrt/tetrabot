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
	this->idRobot = this->robot->getID();

	// initialiser la fonction rand
	srand(time(NULL));

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
}


ControleurRobot::ControleurRobot(Robot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus)
:robot(robot),
tabSin(tab_Sinus),
etape(0),
posInitial(robot->getCenterOfMassPosition())
{
	// robot ne doit pas etre un pointeur NULL
	assert(robot != NULL);
	// initialiser l'identifiant
	this->idRobot = this->robot->getID();
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



void ControleurRobot::etapeSuivante()
{
	btScalar longueurTMP;
	int nbSin = this->tabSin.size();
	if(this->etape==0)
	{
		// etape 0: (ré)initialisation des stats
		this->posInitial = this->robot->getCenterOfMassPosition();
	}
	this->etape++;
	for(int i=0;i<nbSin;i++)
	{
		// Calcul de la longueur de l'Arc i
		longueurTMP = (robot->Arcs[i]->getTailleMax()+ robot->Arcs[i]->getTailleMin())/btScalar(2.F);
		longueurTMP+= this->tabSin[i]->sinus(etape);

		// Creation de l'action
		this->tabAction[i]->setPiston(robot->Arcs[i]);
		this->tabAction[i]->setTailleVoulu(longueurTMP);
		// Creation d'un Thread
		Thread((void*)tabAction[i],actionThread);

	}
}

Resultat* ControleurRobot::creerResultat()
{
	btScalar distance;
	// Calcul de la distance parcouru
	distance = this->posInitial.distance(this->robot->getCenterOfMassPosition());

	// creation du resultat
	return new Resultat(this->idRobot,distance);
}