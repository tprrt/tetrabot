#include "AlgoGenTetra.h"

// type de la fonction de tri
typedef bool (*fct_tri)(ControleurRobot* c1,ControleurRobot* c2);
// Fonction interne  pour classer les resultats
bool triResultat(ControleurRobot* c1,ControleurRobot* c2)
{
	return ((c1->getResultat()->getDistance()) > (c2->getResultat()->getDistance()));
}

// Le Constructeur
AlgoGenTetra::AlgoGenTetra(btDynamicsWorld *monde,PhysicRobot* robot,const btVector3& startPoint,btScalar mutation, int nbRobotsActifs, int nbEtapes, int nbCroisements)
:AlgoGen(monde,robot,startPoint,mutation,nbRobotsActifs,nbEtapes,nbCroisements)
{
	// Creation des Controleurs et des Robots
	this->creerControleurs(monde,nbRobotsActifs);
}

// Methode creant les Controleurs
void AlgoGenTetra::creerControleurs(btDynamicsWorld* monde,int nbRobotsActifs)
{	
	//initialiser la fonction pseudo-aleatoire rand
	srand(time(NULL));
	
	for(int i=0;i<nbRobotsActifs;i++)
	{
		// Creation du ControleurRobot
		this->tabCtrl.expand(new ControleurRobot(this->robot,SIGNAL_PERIOD_MAX,SIGNAL_SCALE_MAX,SIGNAL_PHASE_SHIFT_MAX));

	}
}

void AlgoGenTetra::run()
{
	Thread(this,AlgoGenTetra::execute);
}


void* AlgoGenTetra::execute(void *algoGenTetra)
{
	int random1,random2,random3,random4;
	ControleurRobot* controleurTMP;
	btAlignedObjectArray<ControleurRobot*> tabTMP;
	AlgoGenTetra* algo = (AlgoGenTetra*) algoGenTetra;
	int tailleTabTMP;
	//initialiser la fonction pseudo-aleatoire rand
	srand(time(NULL));
	// Allouer nbRobotsActifs Actions
	printf("Debut Algo_gen\n");
	printf("nbRobotsActifs = %d\n",algo->nbRobotsActifs);
	for(int i=0;i<algo->nbRobotsActifs;i++)
	{
		algo->tabAction.expand(new ActionControleurRobot(NULL));
	}
	for(int nbCroisementEffectuees=0;nbCroisementEffectuees<= algo->nbCroisements;nbCroisementEffectuees++)
	{
		
		printf("========== Croisement %d ==========\n",nbCroisementEffectuees);
		// Pour chaques controleurs actifs, on effectue les nbEtapes
		for(int i=0;i<algo->nbRobotsActifs;i++)
		{
			// Positionner le robot au point de depart
			algo->robot->translate(algo->pointDepart);
			// Mettre en position initiale les pistons du robot
			printf("----------nbCroisementEffectuees %d Robot Initialisation %d----------\n",nbCroisementEffectuees,i);
			// Taille minimale du robot
			((RobotTetra*)algo->robot)->nanoRobot();
			sleep(EDGE_WAIT);
			// Affecter un Thread et une Action au Controleur de Robot
			for(int j = 0;j<algo->nbEtapes;j++)
			{
				printf("----------nbCroisementEffectuees %d Robot %d - Etape %d ----------\n",nbCroisementEffectuees,i,j);
				algo->tabAction[i]->setControleurRobot(algo->tabCtrl[i]);
				algo->tabAction[i]->setEtape(j);
				Thread(algo->tabAction[i],actionThread);
				// Attendre que tous les threads du controleur courant soient finis
				sleep(EDGE_WAIT);		
			}
		}
		printf("Fin des Threads\n");
		//Maintenant on mets a jour les resultats des Controleurs
		for(int i=0;i<algo->nbRobotsActifs;i++)
		{
			algo->tabCtrl[i]->updateResultat();
		}
		// On tri le tableau des controleurs grace a leur resulat pour le classement
		algo->tabCtrl.quickSort<fct_tri>(triResultat);
		
		// CROISEMENTS: uniquement si nbCroisementEffectuees < algo->nbCroisements
		if(nbCroisementEffectuees < algo->nbCroisements)
		{
			// On garde les 30% meilleurs
			tabTMP.resize(0);
			for(int i=0;i<(algo->nbRobotsActifs*0.3);i++)
			{
				tabTMP.expand(new ControleurRobot(algo->tabCtrl[i]->getRobot(),algo->tabCtrl[i]->getTabSin()));
			}
			// GENETIQUE: On garde 30% des nbRobotsActifs et on en crée 70%
			for(int i=(algo->nbRobotsActifs*0.3);i<(algo->nbRobotsActifs);i++)
			{	
				random3 = rand()%algo->tabCtrl.size();
				random4 = rand()%algo->tabCtrl.size();
				
				// On copie le premier controleur
				controleurTMP = new ControleurRobot(algo->robot,algo->tabCtrl[random3]->getTabSin());
				tailleTabTMP = controleurTMP->getTabSin().size();
				// On rajoute au hazard des genes du second controleur
				for(int j=0;j<(int)((rand()/RAND_MAX)*3*tailleTabTMP);j++)
				{       
					random1 = rand()%tailleTabTMP;
					random2 = rand()%3;
					switch(random2)
					{//SWITCH MELANGE GENE
						case 0:
						{
							// On modifie la periode
							controleurTMP->getTabSin()[random1]->setPeriode((algo->tabCtrl[random4]->getTabSin())[random1]->getPeriode());
							break;
						}
						case 1:
						{
							// On modifie l'amplitude
							controleurTMP->getTabSin()[random1]->setAmplitude((algo->tabCtrl[random4]->getTabSin())[random1]->getAmplitude());
							break;
						}
						case 2:
						{
							// On modifie le dephasage
							controleurTMP->getTabSin()[random1]->setDephasage( (algo->tabCtrl[random4]->getTabSin())[random1]->getDephasage());
							break;
						}
						default:break;
					}// Fin SWITCH MELANGE GENE
				}// Fin des melanges des genes

				// On modifie maintenant un parametre d'une des sinusoide si mutation
				if(rand()%100 <= algo->mutation)
				{// MUTATION
					printf("Mutation!\n");
					random1 = rand()%tailleTabTMP;
					random2 = rand()%3;
					switch(random2)
					{//SWITCH MUTATION
						case 0:
						{
							// On modifie la periode
							controleurTMP->getTabSin()[random1]->setPeriode( btScalar(rand()/RAND_MAX) *SIGNAL_PERIOD_MAX);
							break;
						}
						case 1:
						{
							// On modifie l'amplitude
							controleurTMP->getTabSin()[random1]->setAmplitude( btScalar(rand()/RAND_MAX) *SIGNAL_SCALE_MAX);
							break;
						}
						case 2:
						{
							// On modifie le dephasage
							controleurTMP->getTabSin()[random1]->setDephasage( btScalar(rand()/RAND_MAX) *SIGNAL_PHASE_SHIFT_MAX);
							break;
						}
						default:break;
					}// Fin SWITCH MUTATION
				}// Fin MUTATION
				printf("Fin des Mutation !\n");
				// On ajoute ce nouveau controleur au tableau
				tabTMP.expand(controleurTMP);
			}// Fin GENETIQUE
			// Detruire les elments du tableau algo->tabCtrl

		//	ControleurRobot* Rdelete;
			for(int i=0;i<algo->tabCtrl.size();i++)
			{	
				ControleurRobot* Rdelete = algo->tabCtrl[i];
				delete Rdelete;
				
			}
			// Redéfinir la taille du tableau de controleur à 0
			algo->tabCtrl.resize(0);
			for( int sa=0;sa<tabTMP.size();sa++)
			{
				algo->tabCtrl.expand(new ControleurRobot(algo->robot,tabTMP[sa]->getTabSin()));
			}

		}
		printf("Fin CroisementEffectuees %d\n",nbCroisementEffectuees);
	}
	printf("Fin Algo\n");
	// Code de retours du thread: 666 (pour diferencier de ceux des controleurs)
	ExitThread((void *)666);
	return NULL;
}
