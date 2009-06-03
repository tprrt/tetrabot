//  @ Project : Tetrabot
//  @ File Name : AlgoGenTetra.cpp
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#include "AlgoGenTetra.h"

// type de la fonction de tri ( propre a l'algo Genetique )
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
// Methode permettant de lancer l' algoGen
void AlgoGenTetra::run()
{
	Thread(this,AlgoGenTetra::execute);
}

// Methode permettant de derouler l' algoGen
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
	printf("=================  PROCEDURE D' EVOLUTION =================\n");
	printf("\tParametre de l' Algorithme Genetique :\n");
	printf("  Population de robot participant : %6d\n",algo->nbRobotsActifs);
	printf("  Indice de mutation              : %6f\n",algo->mutation);
	printf("  Nombre de croisement		  : %6d\n",algo->nbCroisements);
	printf("  Nombre d' etape (par croisement): %6d\n",algo->nbEtapes);
	/*
		this->pointDepart = startPoint;
	*/
	
	printf("================= LANCEMENT =================\n");
	// on initialise le tableau des Actions des Controleurs de Robots
	for(int i=0;i<algo->nbRobotsActifs;i++)
	{
		algo->tabAction.expand(new ActionControleurRobot(NULL));
	}
	
	for(int nbCroisementEffectuees=0;nbCroisementEffectuees<= algo->nbCroisements;nbCroisementEffectuees++)
	{
		
		printf("\tGeneration de Robot %d / %d\n\t( etat d' avancement de l' algoGen : %5G )\n",nbCroisementEffectuees,algo->nbCroisements,((nbCroisementEffectuees/algo->nbCroisements)*100.));
		// Pour chaques controleurs actifs, on effectue les nbEtapes
		for(int i=0;i<algo->nbRobotsActifs;i++)
		{
			// Positionner le robot au point de depart
			algo->robot->translate(algo->pointDepart);
			// Mettre en position initiale les pistons du robot
			printf("\t\t Robot %d de la Generation %d\n\t\t( etat d' avancement de l' algoGen : %5G )\n",i,nbCroisementEffectuees,((i+(algo->nbRobotsActifs*nbCroisementEffectuees))/(algo->nbRobotsActifs*algo->nbCroisements)*100.));
			// Taille minimale du robot
			((RobotTetra*)algo->robot)->nanoRobot();
			sleep(EDGE_WAIT);
			// Affecter un Thread et une Action au Controleur de Robot
			for(int j = 0;j<algo->nbEtapes;j++)
			{
				printf("\t\t\tEtape %d-R(%d)G(%d)\n\t\t\t( etat d' avancement de l' algoGen : %5G )\n",j,i,nbCroisementEffectuees,( (j+(i*(nbCroisementEffectuees)*(algo->nbEtapes))) / ((algo->nbRobotsActifs)*(algo->nbCroisements)*(algo->nbEtapes)))*100.);
				
				algo->tabAction[i]->setControleurRobot(algo->tabCtrl[i]);
				algo->tabAction[i]->setEtape(j);
				Thread(algo->tabAction[i],actionThread);
				// Attendre que tous les threads du controleur courant soient finis
				sleep(EDGE_WAIT);		
			}
		}
		printf("\nArret de l'etude de la Generation %d\n",nbCroisementEffectuees);
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
					printf("Brassage genetique de la population courante ... \n");
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
				//printf("Fin des Mutation !\n");
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
		printf("\nCreation & etude de la Generation suivante\n");
	}
	printf("=================  PROCEDURE D' EVOLUTION TERMINEE =================\n");
	// Code de retours du thread: 666 (pour diferencier de ceux des controleurs)
	ExitThread((void *)666);
	return NULL;
}
