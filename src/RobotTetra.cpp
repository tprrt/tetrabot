#include "RobotTetra.h"


// JAZZ MODIF : 1 JUIN 2009 : 11h39
void RobotTetra::Deplacement(unsigned char key)
{
	btScalar taille, tailleTmp,Step;
	PhysicPiston* pistonTMP;
	int Num_Piston = 99;
	taille=0.;
	tailleTmp=0.;
	Step = 1.F;
	//PhysicNoeud* noeudTMP;
	
	// Calcul de la position du piston voulu
/*	noeudTMP = (PhysicNoeud*) robot->Sommets[0];
	const btVector3& b0 =  noeudTMP->getBody()->getCenterOfMassPosition();
	noeudTMP = (PhysicNoeud*) robot->Sommets[1];
	const btVector3& b1 =  noeudTMP->getBody()->getCenterOfMassPosition();
	noeudTMP = (PhysicNoeud*) robot->Sommets[2];
	const btVector3& b2 =  noeudTMP->getBody()->getCenterOfMassPosition();
	noeudTMP = (PhysicNoeud*) robot->Sommets[3];
	const btVector3& b3 =  noeudTMP->getBody()->getCenterOfMassPosition();
	const btVector3& b4 =  this->bodyPave->getCenterOfMassPosition();
	btVector3 Gravity = btVector3(0.,0.,0.);
*/
	switch (key) 
	{
	/*	case 'z' :
			{	
				printf("Indication du piston 0\n"); 
				// test boule 0 et boule 2
				Gravity =  (b0+b2)*0.5 ;
				this->bodyPave->translate(-b4);
				this->bodyPave->translate(Gravity);
				break;	
			}
		case 'q' :
			{	
				printf("Indication du piston 1\n");
				// test boule 0 et boule 1
				Gravity =  (b0+b1)*0.5 ;
				this->bodyPave->translate(-b4);
				this->bodyPave->translate(Gravity);
				break;	
			}
		case 'w' :{
			printf("Indication du piston 2\n");
			// test boule 0 et boule 3
			Gravity =  (b0+b3)*0.5 ;
			this->bodyPave->translate(-b4);
			this->bodyPave->translate(Gravity);
			break;	
		}
		case 'e' :{
			printf("Indication du piston 3\n");
			// test boule 1 et boule 2
			Gravity =  (b1+b2)*0.5 ;
			this->bodyPave->translate(-b4);
			this->bodyPave->translate(Gravity);
			break;	
		}
		case 'd' :{
			printf("Indication du piston 4\n");
			// test boule 1 et boule 3
			Gravity =  (b1+b3)*0.5 ;
			this->bodyPave->translate(-b4);
			this->bodyPave->translate(Gravity);
			break;	
		}
		case 'x' :{
			printf("Indication du piston 5\n");
			// test boule 2 et boule 3
			Gravity =  (b2+b3)*0.5 ;
			this->bodyPave->translate(-b4);
			this->bodyPave->translate(Gravity);
			break;
		} */

		case 'Z':
		{	Num_Piston = 0;
		break;
		}
		case 'Q':
		{	Num_Piston = 1;
		break;
		}
		case 'W':
		{	Num_Piston = 2;
		break;
		}
		case 'E':
		{	Num_Piston = 3;
		break;
		}
		case 'D':
		{	Num_Piston = 4;
		break;
		}
		case 'X':
		{	Num_Piston = 5;
		break;
		}
		case 'S':
		{
			
			printf("Inversion %f -> %f \n",this->incremente, (-1)*this->incremente);
			this->incremente *=(btScalar) -1.;
			
		}

		default: break; 
	}// FIN SWITCH
	//        std::cout << "unused key : " << key << std::endl;
	if(Num_Piston != 99){
		printf("Piston %d : %f",Num_Piston,this->incremente);
		// verif piston existe
		if(this->Arcs[Num_Piston]!=NULL)
		{	// verif taille futur valide
			pistonTMP = (PhysicPiston*)this->Arcs[Num_Piston];
			taille = pistonTMP->getLength() + this->incremente*(Step);
			printf(" ==> taille : %f\n",taille);
			if(this->incremente == -1 ){
				tailleTmp = pistonTMP->getTailleMax() - taille ;
			}
			else{
				tailleTmp = pistonTMP->getTailleMin() + taille ;
				this->incremente =(btScalar) 1.;
			}
			if(tailleTmp< 0) tailleTmp= -tailleTmp;
			if(tailleTmp> btScalar(0.1))
			{	
				// configuration de la nouvelle action
				pistonTMP = (PhysicPiston*)this->Arcs[Num_Piston];
				this->action[Num_Piston] = new ActionPiston(pistonTMP, (btScalar) (taille/1));
				// lancement du thread
				Thread((void*)this->action[Num_Piston],actionThread);
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
void RobotTetra::StartThread(void * a, void * b, void * c){
	printf("StartThread used\n");
	this->end = new btVector3;
	this->end = (btVector3*)((btScalar*)a,(btScalar*)b,(btScalar*)c);
	Thread(this,RobotTetra::marcherRobot);
}

bool RobotTetra::IsNotInArea(const btVector3 &G,const btVector3 &end2){
	return (
		 end2.distance(G) > btScalar(5.)
	);
}

void RobotTetra::nanoRobot(){
	printf("Nainification du robot\n");
	PhysicPiston* pistonTMP;

	// Tous les pistons a la taille minimale
	btScalar tailleTmp;
	for(int i=0;i<6;i++)
	{
		if(this->Arcs[i]!=NULL)
		{
			pistonTMP = (PhysicPiston*) this->Arcs[i];
			tailleTmp = pistonTMP->getTailleMin()- pistonTMP->getLength();
			if(tailleTmp< 0)tailleTmp= -tailleTmp;
			if(tailleTmp> btScalar(0.1))
			{
				this->action[i] = new ActionPiston(pistonTMP,pistonTMP->getTailleMin());
				//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)actionThread,action[i], 0, &threadID);
				Thread((void*)this->action[i],actionThread);
			}
		}
	}
}

void RobotTetra::maxiRobot(){
	printf("Nainification du robot\n");
	// Tous les pistons a la taille maximale
	PhysicPiston* pistonTMP;
	btScalar tailleTmp;
	for(int i=0;i<6;i++)
	{
		if(this->Arcs[i]!=NULL)
		{
			pistonTMP = (PhysicPiston*) this->Arcs[i];
			tailleTmp = pistonTMP->getTailleMax()- pistonTMP->getLength();
			if(tailleTmp< 0)tailleTmp= -tailleTmp;
			if(tailleTmp> btScalar(0.1))
			{
				this->action[i] = new ActionPiston(pistonTMP,pistonTMP->getTailleMax());
				Thread((void*)this->action[i],actionThread);
			}
		}
	}
}



void* RobotTetra::marcherRobot(void *demo)
{	printf("marcher robot\n");
	printf("Test 0: RobotTetra* robot = (RobotTetra*) demo;\n");
	RobotTetra* robot = (RobotTetra*) demo;

	int NHaut=0,N1=-1,N2=-1,NRestant=-1;
	int PBas = -1,PHaut = -1,P1=-1,P2=-1;
	int i,j;
	btVector3 vectTMP[3];
	PhysicPiston* pistonTMP;
	PhysicNoeud* noeuds[4];
	// MODIF JAZZ : 31 / 05 /09 : 23h45
	// De base on definit le pt d'arrivee
	btVector3 end = btVector3(btScalar(30.),btScalar(5.),btScalar(0.));
	// On va deplacer le robot
	// On choisi un point d'arrive du robot sur le cercle de centre ( G : center of masse et de rayon R = 5.)
	// MODIF JAZZ : 31 / 05 /09 : 23h45
	if(robot->bodyCube != NULL){
	printf("Test 1 : btVector3 end = robot->bodyCube->getCenterOfMassPosition();\n");
	btVector3 end = robot->bodyCube->getCenterOfMassPosition();
	}
	else{
		if(robot->end != NULL){
				printf("Test 1Bis: btVector3 end = robot->end;\n");
			btVector3 end = *robot->end;
		}
		else{
			printf("Definition d'un nouveau point d'arrivee ( 30,5,0 )\n");
			btVector3 end = btVector3(btScalar(30.),btScalar(5.),btScalar(0.));}
	}
	
	printf("Test 2 : end.setY(btScalar(robot->getCenterOfMassPosition().getY()));\n");
	end.setY(btScalar(robot->getCenterOfMassPosition().getY()));

	// Pour faire simple, on va creer la matrice de liaison des noeuds (matrice d'identificateurs)
	printf("Test 3 : Suite \n");
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
	printf(" Test 4 : if(robot->action[i]!=NULL)\n");
		if(robot->action[i]!=NULL){
		printf("Test 5 : robot->action[i] = new ActionPiston(robot->Arcs[i],robot->Arcs[i]->getTailleMax()/2); \n");
			pistonTMP = (PhysicPiston*)robot->Arcs[i];
			robot->action[i] = new ActionPiston(pistonTMP,pistonTMP->getTailleMax()/2);
		}
	}
	printf("Test 6 : while(robot->IsNotInArea(robot->getCenterOfMassPosition(),end)) \n");
	while(robot->IsNotInArea(robot->getCenterOfMassPosition(),end))
	{
		// Mettre le robot � l'etat initial (pistons au minimum de leur taille)
		for(i=0;i<6;i++)
		{	
			pistonTMP = (PhysicPiston*) robot->Arcs[i];
			robot->action[i]->setPiston(pistonTMP);
			robot->action[i]->setTailleVoulu(pistonTMP->getTailleMin());
			Thread((void*)robot->action[i],actionThread);
		}
		// On attends 8 secondes que l'initialisation ce termine
		// MODIF JAZZ : 31 / 05 /09 : 23h50 : 10 => 3
		sleep(3);
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
		robot->action[PBas]->setTailleVoulu(btScalar(8.));
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
		robot->action[PHaut]->setTailleVoulu(pistonTMP->getTailleMax());
		Thread((void*)robot->action[PHaut],actionThread);
		// On attends 12 secondes
		// MODIF JAZZ : 31 / 05 /09 : 23h55 12 => 4
		sleep(4);
		// On bloque les pistons liant le noeuds NHaut precedement debloques
		pistonTMP = (PhysicPiston*) robot->Arcs[P1];
		pistonTMP->lock();
		pistonTMP = (PhysicPiston*) robot->Arcs[P2];
		pistonTMP->lock();
		// On debloque les contraintes coniques des deux precedents pistons
	
	// MODIF JAZZ : 31 / 05 /09 : 23h54
	end.setY(btScalar(robot->getCenterOfMassPosition().getY()));
	}// Fin WHILE
	// La marche du robot est termin�e.
	// Mettre le robot � l'etat final (pistons au minimum de leur taille)
	for(i=0;i<6;i++)
	{
		pistonTMP = (PhysicPiston*) robot->Arcs[i];
		robot->action[i]->setPiston(pistonTMP);
		robot->action[i]->setTailleVoulu(pistonTMP->getTailleMin());
		Thread((void*)robot->action[i],actionThread);
	}
	// Attendre que les pistons soient arretes
	// MODIF JAZZ : 31 / 05 /09 : 23h53  8 => 3
	sleep(3);

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
		pistonTMP->lock();
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

