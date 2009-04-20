#include "AlgoGen_Tetra.h"
// pour la fonction rand
#include "stdlib.h"

// type de la fonction de tri
typedef bool (*fct_tri)(Resultat* r1,Resultat* r2);
// Fonction interne  pour classer les resultats
bool triResultat(Resultat* res1,Resultat* res2)
{
	return (res1 > res2);
}

// Le Constructeur
AlgoGen_Tetra::AlgoGen_Tetra(btDynamicsWorld *monde, int nbRobots, int nbRobotsActifs,int nbRobotMax, int nbEtapes, int nbCroisements)
:AlgoGen(monde,nbRobots,nbRobotsActifs,nbRobotMax,nbEtapes,nbCroisements)
{
	// Creation des Controleurs et des Robots
	this->creerControleurs(monde,nbRobots);
}

// Methode creant les Controleurs et les Robots
void AlgoGen_Tetra::creerControleurs(btDynamicsWorld* monde,int nbRobots)
{
	
	Robot* robotTMP;
	
	//initialiser la fonction pseudo-aleatoire rand
	srand(time(NULL));
	
	for(int i=0;i<nbRobots;i++)
	{
		// Creation d'un nouveau robot
		robotTMP = new Robot_Tetra(monde,btVector3(0,100,0));
		// Creation du ControleurRobot
		this->tabCtrl.expand(new ControleurRobot(robotTMP,PERIODE_MAX,AMPLITUDE_MAX,DEPHASAGE_MAX));

	}
}

void AlgoGen_Tetra::run()
{
	Thread(this,AlgoGen_Tetra::execute);
}


void* AlgoGen_Tetra::execute(void *algoGen_Tetra)
{
	AlgoGen_Tetra* algo = (AlgoGen_Tetra*) algoGen_Tetra;
	int nbRobots = algo->tabCtrl.size();
	printf("nbRobots: %d\n",nbRobots);
	// Allouer nbRobotsActifs Actions
	for(int i=0;i<algo->nbRobotsActifs;i++)
	{
		algo->tabAction.expand(new ActionControleurRobot(NULL));
	}
	for(int j = 0;j<algo->nbEtapes;j++)
	{
		// Affecter un Thread et une Action a chaque Controleur de Robot
		for(int i=0;i<nbRobots;i++)
		{
			algo->tabAction[i]->setControleurRobot(algo->tabCtrl[i]);
			Thread(algo->tabAction[i],actionThread);
			
		}
		// Attendre que tous les threads soient fini
		sleep(10);
	}
	// Maintenant on cree les rapports
	// Effacer les resultats existants
	algo->tabResultat.clear();
	for(int i=0;i<nbRobots;i++)
	{
		algo->tabResultat.expand(algo->tabCtrl[i]->creerResultat());
	}
	// On trie le tableau des resultats pour le classement
	algo->tabResultat.quickSort<fct_tri>(triResultat);
	
	
	printf("\n\n");
	for(int i=0;i<nbRobots;i++)
	{
		printf("%d) res [%d]: distance = %f\n",i,algo->tabResultat[i]->getID(),algo->tabResultat[i]->getDistance());
	}


	ExitThread(666);
	return NULL;
}
