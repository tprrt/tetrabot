#include "AlgoGen_Tetra.h"
// pour la fonction rand
#include "stdlib.h"

// type de la fonction de tri
typedef bool (*fct_tri)(ControleurRobot* c1,ControleurRobot* c2);
// Fonction interne  pour classer les resultats
bool triResultat(ControleurRobot* c1,ControleurRobot* c2)
{
	return ((c1->getResultat()->getDistance()) > (c2->getResultat()->getDistance()));
}

// Le Constructeur
AlgoGen_Tetra::AlgoGen_Tetra(btDynamicsWorld *monde,Robot* robot,const btVector3& startPoint,btScalar mutation, int nbRobots, int nbRobotsActifs, int nbEtapes, int nbCroisements)
:AlgoGen(monde,robot,startPoint,mutation,nbRobotsActifs,nbEtapes,nbCroisements)
{
	// Creation des Controleurs et des Robots
	this->creerControleurs(monde,nbRobots);
}

// Methode creant les Controleurs
void AlgoGen_Tetra::creerControleurs(btDynamicsWorld* monde,int nbRobots)
{	
	//initialiser la fonction pseudo-aleatoire rand
	srand(time(NULL));
	
	for(int i=0;i<nbRobots;i++)
	{
		// Creation du ControleurRobot
		this->tabCtrl.expand(new ControleurRobot(this->robot,PERIODE_MAX,AMPLITUDE_MAX,DEPHASAGE_MAX));

	}
}

void AlgoGen_Tetra::run()
{
	Thread(this,AlgoGen_Tetra::execute);
}


void* AlgoGen_Tetra::execute(void *algoGen_Tetra)
{
	int random1,random2;
	btScalar pourcentage;
	ControleurRobot* controleurTMP;
	AlgoGen_Tetra* algo = (AlgoGen_Tetra*) algoGen_Tetra;
	int nbControleur;
	int nbControleurActif;
	int tailleTabTMP;
	//initialiser la fonction pseudo-aleatoire rand
	srand(time(NULL));
	// Allouer nbRobotsActifs Actions
	for(int i=0;i<algo->nbRobotsActifs;i++)
	{
		algo->tabAction.expand(new ActionControleurRobot(NULL));
	}
	for(int nbCroisementEffectuees=0;nbCroisementEffectuees<= algo->nbCroisements;nbCroisementEffectuees++)
	{
		// Actualisation du nombre de CONTROLEURS
		nbControleur = algo->tabCtrl.size();
		// Actualisation du nombre de controleur qui vont etre Activés
		nbControleurActif = (algo->nbRobotsActifs>nbControleur)?nbControleur:algo->nbRobotsActifs;

		printf("========== Croisement %d ==========\n",nbCroisementEffectuees);
		// Pour chaques controleurs actifs, on effectue les nbEtapes
		ActionPiston* tabActPiston[6];
		for(int a = 0;a<6;a++)
		{
			tabActPiston[a] = new ActionPiston(algo->robot->Arcs[a],algo->robot->Arcs[a]->getTailleMin());
		}
		for(int i=0;i<nbControleurActif;i++)
		{
			// Positionner le robot au point de depart
			algo->robot->translate(algo->pointDepart);
			// Mettre en position initiale les pistons du robot
			printf("---------- Initialisation ----------\n");
			for(int p=0;p<algo->robot->Arcs.size();p++)
			{
				Thread(tabActPiston[p],actionThread);
			}
			sleep(ATTENTE_PISTON);
			// Affecter un Thread et une Action au Controleur de Robot
			for(int j = 0;j<algo->nbEtapes;j++)
			{
				printf("---------- Etape %d ----------\n",j);
				algo->tabAction[i]->setControleurRobot(algo->tabCtrl[i]);
				algo->tabAction[i]->setEtape(j);
				Thread(algo->tabAction[i],actionThread);
				// Attendre que tous les threads du controleur courant soient finis
				sleep(ATTENTE_PISTON);		
			}
		}

		//Maintenant on mets a jour les resultats des Controleurs
		for(int i=0;i<nbControleurActif;i++)
		{
			algo->tabCtrl[i]->updateResultat();
		}
		// On tri le tableau des controleurs grace a leur resulat pour le classement
		algo->tabCtrl.quickSort<fct_tri>(triResultat);
		
		// CROISEMENTS: uniquement si nbCroisementEffectuees < algo->nbCroisements
		if(nbCroisementEffectuees < algo->nbCroisements)
		{
			// On melange le tableau pour croiser les controleurs de maniere pseudo-aleatoire
			for(int i=0;i<nbControleur;i++)
			{
				random1 = rand()%nbControleur;
				random2 = rand()%nbControleur;
				algo->tabCtrl.swap(random1,random2);
			}
			
			// GENETIQUE: On crée nbRobots/2 fils avec mutation% de mutation
			for(int i=0;i+1<nbControleur;i=i+2)
			{
				// On prends les controleurs i et i+1 pour les croiser
				// On calcul combien, en pourcentage, va t-on garder du premier controleur
				pourcentage = algo->tabCtrl[i]->getResultat()->getDistance() / algo->tabCtrl[i+1]->getResultat()->getDistance();
				// On crée un nouveau controleur avec les caracteristiques du controleur i+1
				// On recopie donc le tableau des Sinusoides du controleur i+1
				controleurTMP = new ControleurRobot(algo->robot,algo->tabCtrl[i+1]->getTabSin());
				tailleTabTMP = controleurTMP->getTabSin().size();
				// On rajoute au hazard (pourcentage*tabSinTMP.size())% des genes du controleur i
				for(int j=0;j<(int)(pourcentage*3*tailleTabTMP);j++)
				{
					random1 = rand()%tailleTabTMP;
					random2 = rand()%3;
					switch(random2)
					{//SWITCH MELANGE GENE
						case 0:
						{
							// On modifie la periode
							controleurTMP->getTabSin()[random1]->setPeriode((algo->tabCtrl[i]->getTabSin())[random1]->getPeriode());
							break;
						}
						case 1:
						{
							// On modifie l'amplitude
							controleurTMP->getTabSin()[random1]->setAmplitude((algo->tabCtrl[i]->getTabSin())[random1]->getAmplitude());
							break;
						}
						case 2:
						{
							// On modifie le dephasage
							controleurTMP->getTabSin()[random1]->setDephasage( (algo->tabCtrl[i]->getTabSin())[random1]->getDephasage());
							break;
						}
						default:break;
					}// Fin SWITCH MELANGE GENE
				}// Fin des melanges des genes
				// On modifie maintenant le tableau des Sinusoides pour simuler les mutations
				for(int m=0;m<(int)(algo->mutation*3*tailleTabTMP);m++)
				{// MUTATION
					random1 = rand()%tailleTabTMP;
					random2 = rand()%3;
					switch(random2)
					{//SWITCH MUTATION
						case 0:
						{
							// On modifie la periode
							controleurTMP->getTabSin()[random1]->setPeriode( btScalar(rand()/RAND_MAX) *PERIODE_MAX);
							break;
						}
						case 1:
						{
							// On modifie l'amplitude
							controleurTMP->getTabSin()[random1]->setAmplitude( btScalar(rand()/RAND_MAX) *AMPLITUDE_MAX);
							break;
						}
						case 2:
						{
							// On modifie le dephasage
							controleurTMP->getTabSin()[random1]->setDephasage( btScalar(rand()/RAND_MAX) *DEPHASAGE_MAX);
							break;
						}
						default:break;
					}// Fin SWITCH MUTATION
				}// Fin MUTATION
				// On ajoute ce nouveau controleur au tableau
				algo->tabCtrl.expand(controleurTMP);
			}// Fin GENETIQUE
		}
	}

	// Code de retours du thread: 666 (pour diferencier de ceux des controleurs)
	ExitThread(666);
	return NULL;
}
