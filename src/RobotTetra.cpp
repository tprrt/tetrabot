#include "RobotTetra.h"

//JAZZ MODIF : 7 JUIN 2009 : 12h39

// Methode pour purger les threads
void RobotTetra::purgeThread(void){
	// attente de la fin des threads en cours
	int tmp = 8;
	printf("Purge en cours ...\n veuiller patienter %d sec, merci de votre comprehension.\n",tmp);
	sleep(tmp);
	for(int qd=0;qd<6;qd++){
	this->action[qd]=NULL;
	}
}

// Permet de verifier s'il y a des actions prevues et de les commencer s'il n'y a pas de d'action en cours
// True : on remplit le tableau Action
// False : on remplit le tableau ActionFuture
bool RobotTetra::gestionAction(void){
	
	PhysicPiston* pistonTMP;
	// marqueur des actions en cours : true = Non, il n'y en a pas du tout : permission de faire les actions futures
	//				   false= Oui, il y en a au moins une : on doit terminer cette/ces action(s)
	bool permission = true;
	// marqueur des actions prevues : true = oui, il y en a au moins une
	//			          false= Non, il n'y en a pas du tout
	bool permissionFuture = false;
	
	if(this->end == NULL){
	printf("Analyse des tableau d'action 1 = true, 0 = false\n");
	// regarde s'il y a des actions en cours et prevues
	for(int ok1=0;ok1<6;ok1++)
	{	// marqueur des actions en cours
		if(this->action[ok1]!=NULL)
			{	
				permission=false;
				break;
			}
		// marqueur des actions prevues
		if(this->actionFuture[ok1]!=NULL)
			{	
				permissionFuture=true;
				break;
			}
	}
	if(permission){
		printf(" permission de faire les actions futures \n");
		if(permissionFuture){
			printf(" il y a au moins une action future\n");
		} else {
			printf(" il n'y a aucune action future\n");
		}
	} else{
		printf(" action(s) en cours on attend \n");
	}
	// Si il n'y a pas d'action a faire et qu'il y a des actions des prevues
	if(permission&&permissionFuture){
	// alors pour toutes les actions prevues faire 
	printf(" chargement des actions futures dans les actions courantes\n");
		for(int ok2=0; ok2<6; ok2++){
			if(this->Arcs[ok2]!=NULL)
			{
				pistonTMP = (PhysicPiston*) this->Arcs[ok2];
				if(this->actionFuture[ok2]!=NULL){
					printf(" chargement de l'actionfuture [%d]...\n",ok2);
					// on remplit le tableau d'action par les actions prévues
					this->action[ok2] = new ActionPiston(pistonTMP,this->actionFuture[ok2]->getTailleVoulue());
					Thread((void*)this->action[ok2],actionThread);
					this->actionFuture[ok2]=NULL;
				}
			}
		}
	// on signale qu'il y a des actions en cours
	permission = false;
	// on signale qu'il n'y a plus d'action de prévue
	permissionFuture=false;
	}
	} // fin this->end == NULL
	else {
		printf("il y a un deplacement en cours,\n aucune autre action ne sera entreprise\n");
	}
	printf("Fin de la gestions des Actions\n");
	// autorise la mise en memoire des actions suivantes
	return (permission);
}

// JAZZ MODIF : 1 JUIN 2009 : 11h39
void RobotTetra::Deplacement(unsigned char key)
{
	btScalar taille, tailleTmp,Step;
	PhysicPiston* pistonTMP;
	int sensMouvement =1;
	int Num_Piston = -1;
	taille=0.;
	tailleTmp=0.;
	Step = 1.F;

	switch (key)
	{
		case 'A':
		{	sensMouvement =1;
			Num_Piston = 0;
		break;
		}
		case 'Z':
		{	sensMouvement =1;
			Num_Piston = 1;
		break;
		}
		case 'E':
		{	sensMouvement =1;
			Num_Piston = 2;
		break;
		}
		case 'R':
		{	sensMouvement =1;
			Num_Piston = 3;
		break;
		}
		case 'T':
		{	sensMouvement =1;
			Num_Piston = 4;
		break;
		}
		case 'Y':
		{	sensMouvement =1;
			Num_Piston = 5;
		break;
		}
		case 'Q':
		{	sensMouvement =-1;
			Num_Piston = 0;
		break;
		}
		case 'S':
		{	sensMouvement =-1;
			Num_Piston = 1;
		break;
		}
		case 'D':
		{	sensMouvement =-1;
			Num_Piston = 2;
		break;
		}
		case 'F':
		{	sensMouvement =-1;
			Num_Piston = 3;
		break;
		}
		case 'G':
		{	sensMouvement =-1;
			Num_Piston = 4;
		break;
		}
		case 'H':
		{	sensMouvement =-1;
			Num_Piston = 5;
		break;
		}
		case 'I':
		{
		btVector3 G = this->getCenterOfMassPosition();
		// vers le nord
		G.setX(G.getX()+(btScalar)10.);
		this->StartThread(G);
		Num_Piston = -1;
		break;
		}
		case 'J':
		{
		btVector3 G = this->getCenterOfMassPosition();
		// vers le Ouest
		G.setZ(G.getZ()+(btScalar)(-10.));
		this->StartThread(G);
		Num_Piston = -1;
		break;
		}
		case 'K':
		{
		btVector3 G = this->getCenterOfMassPosition();
		// vers le Sud
		G.setX(G.getX()+(btScalar)(-10.));
		this->StartThread(G);
		Num_Piston = -1;
		break;
		}
		case 'L':
		{
		btVector3 G = this->getCenterOfMassPosition();
		// vers le Est
		G.setZ(G.getZ()+(btScalar)10.);
		this->StartThread(G);
		Num_Piston = -1;
		break;
		}
	default : Num_Piston = -1;
	break;
	}// FIN SWITCH
	//        std::cout << "unused key : " << key << std::endl;
	if(Num_Piston != -1){
		//printf("Piston %d : %f",Num_Piston,sensMouvement);
		// verif piston existe
		if(this->Arcs[Num_Piston]!=NULL)
		{	// verif taille futur valide
			pistonTMP = (PhysicPiston*)this->Arcs[Num_Piston];
			taille = pistonTMP->getLength() + sensMouvement*(Step);
			printf(" ==> taille : %f\n",taille);
			if(sensMouvement == -1 ){
				tailleTmp = pistonTMP->getTailleMax() - taille ;
			} else {
				tailleTmp = pistonTMP->getTailleMin() + taille ;
			}
			if(tailleTmp< 0) tailleTmp= -tailleTmp;
			if(tailleTmp> btScalar(0.1))
			{
				// configuration de la nouvelle action
				pistonTMP = (PhysicPiston*)this->Arcs[Num_Piston];
				bool test = gestionAction();
				printf("Test = %d = 1 => on remplit le tableau Action\n",test);
				if(test){
					this->action[Num_Piston] = new ActionPiston(pistonTMP, (btScalar) (taille/1));
					// lancement du thread
					// JAZZ 4 JUIN 2009 : 21h21 -- ajout d une subtilite pour le deplacement manuel du robot
					btScalar G = this->getCenterOfMassPosition().getY();
					btScalar max = G;
					btScalar Gs = G;
					int Som = 0;
					for(int t=0;t<4;t++){
						Gs = this->Sommets[t]->getCenterOfMassPosition().getY();
						if((Gs >= G) &&(Gs >= max))
						{
							Som = t;
						}
					}
					switch(Som)
					{
					case 0 :	if((Num_Piston==0)||(Num_Piston==1)||(Num_Piston==2))
							{
								this->Arcs[0]->unlock();
								this->Arcs[1]->unlock();
								this->Arcs[2]->unlock();
							}
					break;
					case 1 :	if((Num_Piston==1)||(Num_Piston==3)||(Num_Piston==4))
							{
								this->Arcs[1]->unlock();
								this->Arcs[3]->unlock();
								this->Arcs[4]->unlock();
							}
					break;
					case 2 :	if((Num_Piston==0)||(Num_Piston==3)||(Num_Piston==5))
							{
								this->Arcs[0]->unlock();
								this->Arcs[3]->unlock();
								this->Arcs[5]->unlock();
							}
					break;
					case 3 :	if((Num_Piston==2)||(Num_Piston==4)||(Num_Piston==5))
							{
								this->Arcs[2]->unlock();
								this->Arcs[4]->unlock();
								this->Arcs[5]->unlock();
							}
					break;
					default : break;
					}
					Thread((void*)this->action[Num_Piston],actionThread);
				} else {
					for(int qd=0;qd<6;qd++){
						this->actionFuture[qd]=NULL;
					}
					this->actionFuture[Num_Piston] = new ActionPiston(pistonTMP, (btScalar) (taille/1));
					printf("Parametrage d une action future %d \n",Num_Piston);
;
				}
			//purgeThread();
			}
			else{
				printf("Taille invalide\n");
			}
		}
		else {
			printf("Le piston %d n'existe pas !!\n",Num_Piston);
		}
	}
	//glutPostRedisplay();
}

// JAZZ MODIF :  1 JUIN 2009 : 2h50
void RobotTetra::StartThread(btVector3 ending){
	printf("StartThread used\n");
	if(gestionAction()){
	if(this->end == NULL){
	this->end = new btVector3;
		if(this->endFuture != NULL ){
			printf(" Le robot va au point suivant indique\n");
			this->end = this->endFuture;
			this->endFuture = NULL;
		} else {
			printf(" Le robot va au point indique\n");
			this->end = (btVector3*)&ending;
		}
	Thread(this,RobotTetra::marcherRobot);
	} else {
		printf("Mise en memoire du chekpoint suivant\n");
		this->endFuture = new btVector3;
		this->endFuture = (btVector3*)&ending;
	}
	
	 } else {
		printf(" Il y a une action local en cours, ce mouvement necessitant un certain temps,\nle programe attendra une totale liberte de mouvement\nANNULATION DE LA COMMANDE ...\n");
	}
}

bool RobotTetra::IsNotInArea(const btVector3 &G,const btVector3 &end2){
	return (
		 end2.distance(G) > btScalar(5.)
	);
}

void RobotTetra::nanoRobot(){
	//printf("Nainification du robot\n");
	PhysicPiston* pistonTMP;
	bool permission;

	// Tous les pistons a la taille minimale
	btScalar tailleTmp;
	permission = gestionAction();
	for(int i=0;i<6;i++)
	{
		if(this->Arcs[i]!=NULL)
		{
			pistonTMP = (PhysicPiston*) this->Arcs[i];
			tailleTmp = pistonTMP->getTailleMin()- pistonTMP->getLength();
			if(tailleTmp< 0)tailleTmp= -tailleTmp;
			if(tailleTmp> btScalar(0.1))
			{
				if(permission){
					printf("Parametrage d une action courante %d \n",i);
					this->action[i]=NULL;
					this->action[i] = new ActionPiston(pistonTMP,pistonTMP->getTailleMin());
					//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)actionThread,action[i], 0, &threadID);
					Thread((void*)this->action[i],actionThread);
				} else {
					this->actionFuture[i] = NULL;
					this->actionFuture[i] = new ActionPiston(pistonTMP,pistonTMP->getTailleMin());
					printf("Parametrage d une action future %d \n",i);
				}
			
			}
		}
	}
	if(!permission){
	purgeThread();
	}
}

void RobotTetra::maxiRobot(){
	// printf("Maximisation du robot\n");
	// Tous les pistons a la taille maximale
		PhysicPiston* pistonTMP;
	bool permission;

	// Tous les pistons a la taille minimale
	btScalar tailleTmp;
	permission = gestionAction();
	for(int i=0;i<6;i++)
	{
		if(this->Arcs[i]!=NULL)
		{
			pistonTMP = (PhysicPiston*) this->Arcs[i];
			tailleTmp = pistonTMP->getTailleMin()- pistonTMP->getLength();
			if(tailleTmp< 0)tailleTmp= -tailleTmp;
			if(tailleTmp> btScalar(0.1))
			{
				if(permission){
					printf("Parametrage d une action courante %d \n",i);
					this->action[i]=NULL;
					this->action[i] = new ActionPiston(pistonTMP,pistonTMP->getTailleMax());
					//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)actionThread,action[i], 0, &threadID);
					Thread((void*)this->action[i],actionThread);
				} else {
					this->actionFuture[i] = NULL;
					this->actionFuture[i] = new ActionPiston(pistonTMP,pistonTMP->getTailleMax());
					printf("Parametrage d une action future %d \n",i);
				}
			
			}
		}
	}
	if(!permission){
	purgeThread();
	}
}



void* RobotTetra::marcherRobot(void *demo)
{	printf("marcher robot\n");
	//printf("Test 0: RobotTetra* robot = (RobotTetra*) demo;\n");
	RobotTetra* robot = (RobotTetra*) demo;
	int TimeOut = 5;
	int NHaut=0,N1=-1,N2=-1,NRestant=-1;
	int PBas = -1,PHaut = -1,P1=-1,P2=-1;
	int i,j;
	btVector3 vectTMP[3];
	PhysicPiston* pistonTMP;
	PhysicNoeud* noeuds[4];
	// MODIF JAZZ : 31 / 05 /09 : 23h45
	// De base on definit le pt d'arrivee
	btVector3 end = btVector3(btScalar(30.),btScalar(5.),btScalar(0.));
	printf("end0 %f %f %f\n",end.getX(),end.getY(),end.getZ());
	// On va deplacer le robot
	// On choisi un point d'arrive du robot sur le cercle de centre ( G : center of masse et de rayon R = 5.)
	// MODIF JAZZ : 31 / 05 /09 : 23h45
	if(robot->bodyCube != NULL){
	//printf("Test 1 : btVector3 end = robot->bodyCube->getCenterOfMassPosition();\n");
		 end = robot->bodyCube->getCenterOfMassPosition();
		printf("end1 %f %f %f\n",end.getX(),end.getY(),end.getZ());
	}
	else{
		if(robot->end != NULL){
		//	printf("Test 1Bis: btVector3 end = robot->end;\n");
			 end = *robot->end;
			printf("end2 %f %f %f\n",end.getX(),end.getY(),end.getZ());
		}
		else{
			//printf("Definition d'un nouveau point d'arrivee ( 30,5,0 )\n");
			 end = btVector3(btScalar(30.),btScalar(5.),btScalar(0.));
			printf("end3 %f %f %f\n",end.getX(),end.getY(),end.getZ());
		}
	}

	//printf("Test 2 : end.setY(btScalar(robot->getCenterOfMassPosition().getY()));\n");
	end.setY(btScalar(robot->getCenterOfMassPosition().getY()));
	printf("end4 %f %f %f\n",end.getX(),end.getY(),end.getZ());

	// Pour faire simple, on va creer la matrice de liaison des noeuds (matrice d'identificateurs)
	//printf("Test 3 : Suite \n");
	int matLiaison[4][4];
	// initialisation de matLiaison � -1
	for( i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			matLiaison[i][j] = -1;
		}
	}
	matLiaison[0][2] = 0;
	matLiaison[2][0] = 0;
	matLiaison[0][1] = 1;
	matLiaison[1][0] = 1;
	matLiaison[0][3] = 2;
	matLiaison[3][0] = 2;
	matLiaison[1][2] = 3;
	matLiaison[2][1] = 3;
	matLiaison[1][3] = 4;
	matLiaison[3][1] = 4;
	matLiaison[2][3] = 5;
	matLiaison[3][2] = 5;
	// Tant que le robot n'est pas assez proche du point end, on fait avancer le robot (de maniere simple)
	// Le point end est assez proche si la distance entre ce dernier et le centre de gravite du robot
	// est inferieure � 6.
	// test anti-pointeur null

	for(int i=0;i<6;i++){
	//printf(" Test 4 : if(robot->action[i]==NULL)\n");
		if(robot->action[i]==NULL){
			robot->action[i] = NULL;
		}
		//printf("Test 5 : robot->action[i] = new ActionPiston(robot->Arcs[i],robot->Arcs[i]->getTailleMax()/2); \n");
			pistonTMP = (PhysicPiston*)robot->Arcs[i];
			robot->action[i] = new ActionPiston(pistonTMP,pistonTMP->getTailleMax()/2);

	}
	//printf("Test 6 : while(robot->IsNotInArea(robot->getCenterOfMassPosition(),end)) \n");
	while(((TimeOut--) != 0)&&(robot->IsNotInArea(robot->getCenterOfMassPosition(),end)))
	{ printf("TimeOut %d\n",TimeOut);
		// Mettre le robot � l'etat initial (pistons au minimum de leur taille)
		for(i=0;i<6;i++)
		{
			pistonTMP = (PhysicPiston*) robot->Arcs[i];
			robot->action[i]->setPiston(pistonTMP);
			robot->action[i]->setTailleVoulue(pistonTMP->getTailleMin());
			Thread((void*)robot->action[i],actionThread);
		}
		// On attends 8 secondes que l'initialisation ce termine
		// MODIF JAZZ : 31 / 05 /09 : 23h50 : 10 => 3
		sleep(8);
		NHaut = 0;
		// On cherche le noeud NHaut le plus haut.
		for(i=1;i<4;i++)
		{
			vectTMP[0] = (robot->Sommets[NHaut]->getCenterOfMassPosition());
			vectTMP[1] = (robot->Sommets[i]->getCenterOfMassPosition());
			if((vectTMP[0].y()) < (vectTMP[1].y()))
				NHaut = i;
		}
		// On cherche maintenant les 2 noeuds de la base les plus proches du point d'arriv� end.
		j=0;
		for(i=0;i<4;i++)
		{
			if(i!= NHaut && j<3){
				noeuds[j] =(PhysicNoeud*) robot->Sommets[i];
				vectTMP[j] = noeuds[j]->getCenterOfMassPosition();
				j++;
			}
		}
		if( (vectTMP[0].distance(end)) < (vectTMP[1].distance(end)) )
		{
			N1 = noeuds[0]->getID();
			if( (vectTMP[1].distance(end)) < (vectTMP[2].distance(end)) )
			{
				N2 = noeuds[1]->getID();
				NRestant = noeuds[2]->getID();
			}
			else
			{
				N2 = noeuds[2]->getID();
				NRestant = noeuds[1]->getID();
			}
		}
		else
		{
			if( (vectTMP[0].distance(end)) < (vectTMP[2].distance(end)) )
			{
				N1 = noeuds[0]->getID();
				N2 = noeuds[1]->getID();
				NRestant = noeuds[2]->getID();
			}
			else
			{
				N1 = noeuds[2]->getID();
				N2 = noeuds[1]->getID();
				NRestant = noeuds[0]->getID();
			}
		}
		// On cherche les pistons liant N1 et N2 (PBas), et celui liant NRestant � NHaut(PHaut).
		PBas = matLiaison[N1][N2];
		PHaut = matLiaison[NRestant][NHaut];

		// On mets le piston d'identificateur PBas � 8
		printf("NHaut: %d, N1: %d,N2: %d,NRestant: %d\n",NHaut,N1,N2,NRestant);
		printf("PHaut: %d, PBas: %d\n",PHaut,PBas);
		pistonTMP = (PhysicPiston*) robot->Arcs[PBas];
		robot->action[PBas]->setPiston(pistonTMP);
		robot->action[PBas]->setTailleVoulue(btScalar(8.));
		Thread((void*)robot->action[PBas],actionThread);

		// On debloque les pistons liant le noeuds NHaut (P1 et P2)
		//printf("P1: %d, P2: %d\n",matLiaison[NHaut][N1],matLiaison[NHaut][N2]);
		P1 = matLiaison[NHaut][N1];
		P2 = matLiaison[NHaut][N2];
		//printf("P1: %d, P2: %d\n",P1,P2);
		pistonTMP = (PhysicPiston*) robot->Arcs[P1];
		pistonTMP->unlock();
		pistonTMP = (PhysicPiston*) robot->Arcs[P2];
		pistonTMP->unlock();


		// On mets le piston d'identificateur PHaut � sa taille maximale
		pistonTMP = (PhysicPiston*) robot->Arcs[PHaut];
		robot->action[PHaut]->setPiston(pistonTMP);
		robot->action[PHaut]->setTailleVoulue(pistonTMP->getTailleMax());
		Thread((void*)robot->action[PHaut],actionThread);
		// On attends 12 secondes
		// MODIF JAZZ : 31 / 05 /09 : 23h55 12 => 4
		sleep(10);
		// On bloque les pistons liant le noeuds NHaut precedement debloques
		pistonTMP = (PhysicPiston*) robot->Arcs[P1];
		pistonTMP->lock();
		pistonTMP = (PhysicPiston*) robot->Arcs[P2];
		pistonTMP->lock();
		// On debloque les contraintes coniques des deux precedents pistons

	// MODIF JAZZ : 31 / 05 /09 : 23h54
	end.setY(btScalar(robot->getCenterOfMassPosition().getY()));
	printf("end5 %f %f %f\n",end.getX(),end.getY(),end.getZ());
	}// Fin WHILE
	// La marche du robot est termin�e.
	// Mettre le robot � l'etat final (pistons au minimum de leur taille)
	for(i=0;i<6;i++)
	{
		pistonTMP = (PhysicPiston*) robot->Arcs[i];
		robot->action[i]->setPiston(pistonTMP);
		robot->action[i]->setTailleVoulue(pistonTMP->getTailleMin());
		Thread((void*)robot->action[i],actionThread);
	}
	// Attendre que les pistons soient arretes
	// MODIF JAZZ : 31 / 05 /09 : 23h53  8 => 3
	// attente de la fin des threads en cours
	sleep(8);
	for(int qd=0;qd<6;qd++){
	robot->action[qd]=NULL;
	}
	robot->end = NULL;
	printf("Arret du robot!\n");

	return NULL;
}

RobotTetra::RobotTetra(btDynamicsWorld* world,Ogre::SceneManager * scene,const btVector3& posInit)
{
	PhysicPiston* pistonTMP;

	PhysicNoeud* bouleTMP;
	// le vecteur decalage sert � espacer les objets
	// pour eviter d'eventuelles erreurs de collisions

	btVector3 decalage;

	// Cr�ation des boules
	for(int i=0;i<4;i++) {

		decalage = btVector3(NODE_RADIUS*i*2,0,0);
		char nom[20] ;
		sprintf(nom,"NodeNoeud%d",(i+1));
		bouleTMP = new PhysicNoeud(world,scene->getSceneNode(nom),new btSphereShape(NODE_RADIUS),posInit+decalage,NODE_WEIGHT);
		this->Sommets.expand(bouleTMP);
	}
	// Cr�ation des pistons
	for(int i=0;i<6;i++)
	{
		decalage = btVector3(0,0,5*i+15);
		pistonTMP = new PhysicPiston(world,NULL,posInit+decalage,EDGE_MIN_SIZE,EDGE_MAX_SIZE,EDGE_VELOCITY);
		pistonTMP->unlock();
		this->Arcs.expand(pistonTMP);
	}
	// On lie les pistons aux boules
	btScalar angle1 = btScalar(M_PI_4*(4.F/3.F));
	for(int i=0;i<3;i++)
	{
		this->Sommets[0]->linkEdge(Arcs[i],'A',angle1,(i*2*M_PI)/3);
	}
	this->Sommets[1]->linkEdge(Arcs[1],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[1]->linkEdge(Arcs[3],'A',angle1,(1*2*M_PI)/3);
	this->Sommets[1]->linkEdge(Arcs[4],'A',angle1,(2*2*M_PI)/3);

	this->Sommets[2]->linkEdge(Arcs[0],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[2]->linkEdge(Arcs[5],'B',angle1,(1*2*M_PI)/3);
	this->Sommets[2]->linkEdge(Arcs[3],'B',angle1,(2*2*M_PI)/3);

	this->Sommets[3]->linkEdge(Arcs[2],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[3]->linkEdge(Arcs[4],'B',angle1,(1*2*M_PI)/3);
	this->Sommets[3]->linkEdge(Arcs[5],'A',angle1,(2*2*M_PI)/3);

	for(int k=0;k<6;k++){
		this->action[k]=NULL;
		this->actionFuture[k]=NULL;
	}
	this->bodyCube = NULL;
	this->end = NULL;
	this->endFuture = NULL;

}

RobotTetra::RobotTetra(btDynamicsWorld* world,const btVector3& posInit)
{
	PhysicNoeud* bouleTMP;
	PhysicPiston* pistonTMP;
	// le vecteur decalage sert � espacer les objets
	// pour eviter d'eventuelles erreurs de collisions
	btVector3 decalage;
	// Cr�ation des boules
	for(int i=0;i<4;i++)
	{
		decalage = btVector3(NODE_RADIUS*i*2,0,0);
		bouleTMP = new PhysicNoeud(world,new btSphereShape(NODE_RADIUS),posInit+decalage,NODE_WEIGHT);
		this->Sommets.expand(bouleTMP);
	}
	// Cr�ation des pistons
	for(int i=0;i<6;i++)
	{
		decalage = btVector3(0,0,5*i+15);
		pistonTMP = new PhysicPiston(world,posInit+decalage,EDGE_MIN_SIZE,EDGE_MAX_SIZE,EDGE_VELOCITY);
		//pistonTMP->lock();
		this->Arcs.expand(pistonTMP);
	}
	// On lie les pistons aux boules
	btScalar angle1 = btScalar(M_PI_4*(4.F/3.F));
	for(int i=0;i<3;i++)
	{
		this->Sommets[0]->linkEdge(Arcs[i],'A',angle1,(i*2*M_PI)/3);
	}
	this->Sommets[1]->linkEdge(Arcs[1],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[1]->linkEdge(Arcs[3],'A',angle1,(1*2*M_PI)/3);
	this->Sommets[1]->linkEdge(Arcs[4],'A',angle1,(2*2*M_PI)/3);

	this->Sommets[2]->linkEdge(Arcs[0],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[2]->linkEdge(Arcs[5],'B',angle1,(1*2*M_PI)/3);
	this->Sommets[2]->linkEdge(Arcs[3],'B',angle1,(2*2*M_PI)/3);

	this->Sommets[3]->linkEdge(Arcs[2],'B',angle1,(0*2*M_PI)/3);
	this->Sommets[3]->linkEdge(Arcs[4],'B',angle1,(1*2*M_PI)/3);
	this->Sommets[3]->linkEdge(Arcs[5],'A',angle1,(2*2*M_PI)/3);

	for(int k=0;k<6;k++){
		this->action[k]=NULL;
		this->actionFuture[k]=NULL;
	}
	this->bodyCube = NULL;
	this->end = NULL;
	this->endFuture = NULL;
}


btVector3 RobotTetra::getCenterOfMassPosition()
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

void RobotTetra::translate(const btVector3& to) {

	btVector3 translation = (to - this->getCenterOfMassPosition());
	int nbSommets = this->Sommets.size();
	for(int i=0;i<nbSommets;i++) {
		this->Sommets[i]->translate(translation);
	}
}

