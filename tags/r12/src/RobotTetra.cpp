#include "RobotTetra.h"


RobotTetra::RobotTetra(btDynamicsWorld* world,Ogre::SceneManager * scene,const btVector3& posInit)
{
	Piston* pistonTMP;

	Noeud* bouleTMP;
	// le vecteur decalage sert � espacer les objets
	// pour eviter d'eventuelles erreurs de collisions

	btVector3 decalage;

	// Cr�ation des boules
	for(int i=0;i<4;i++) {

		decalage = btVector3(RAYON_BOULE*i*2,0,0);
		char nom[20] ;
		sprintf(nom,"NodeNoeud%d",(i+1));
		bouleTMP = new Noeud(world,scene->getSceneNode(nom),new btSphereShape(RAYON_BOULE),posInit+decalage,POIDS_BOULE);
		this->Sommets.expand(bouleTMP);
	}
	// Cr�ation des pistons
	for(int i=0;i<6;i++)
	{
		decalage = btVector3(0,0,5*i+15);
		pistonTMP = new Piston(world,NULL,posInit+decalage,PISTON_TAILLE_MIN,PISTON_TAILLE_MAX,VELOCITE_PISTON);
		pistonTMP->bloquerPiston();
		this->Arcs.expand(pistonTMP);
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

RobotTetra::RobotTetra(btDynamicsWorld* world,const btVector3& posInit)
{
	Noeud* bouleTMP;
	Piston* pistonTMP;
	// le vecteur decalage sert � espacer les objets
	// pour eviter d'eventuelles erreurs de collisions
	btVector3 decalage;
	// Cr�ation des boules
	for(int i=0;i<4;i++)
	{
		decalage = btVector3(RAYON_BOULE*i*2,0,0);
		bouleTMP = new Noeud(world,new btSphereShape(RAYON_BOULE),posInit+decalage,POIDS_BOULE);
		this->Sommets.expand(bouleTMP);
	}
	// Cr�ation des pistons
	for(int i=0;i<6;i++)
	{
		decalage = btVector3(0,0,5*i+15);
		pistonTMP = new Piston(world,posInit+decalage,PISTON_TAILLE_MIN,PISTON_TAILLE_MAX,VELOCITE_PISTON);
		//pistonTMP->bloquerPiston();
		this->Arcs.expand(pistonTMP);
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


btVector3 RobotTetra::getCenterOfMassPosition()
{
	btVector3 centre = btVector3(0,0,0);
	int nbNoeuds = this->Sommets.size();
	for(int i=0;i<nbNoeuds;i++)
	{
		centre+= this->Sommets[i]->getBody()->getCenterOfMassPosition();
	}
	if(nbNoeuds>0) return (centre/btScalar(nbNoeuds));
	else return btVector3(0,0,0);
}

void RobotTetra::stretch() {

	btScalar tailleTmp;
	for(int i=0;i<6;i++)
	{
		if(this->Arcs[i]!=NULL)
		{
			tailleTmp = this->Arcs[i]->getTailleMax()- this->Arcs[i]->getLength();
			if(tailleTmp< 0)tailleTmp= -tailleTmp;
			if(tailleTmp> btScalar(0.1))
			{
				this->action[i] = new ActionPiston(this->Arcs[i],this->Arcs[i]->getTailleMax());
				//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) actionThread,action[i], 0, &threadID);
				Thread((void*)this->action[i],actionThread);
			}
		}
	}
}

void RobotTetra::reduce() {

	btScalar tailleTmp;

	for(int i=0;i<6;i++)
	{
		if(this->Arcs[i]!=NULL)
		{
			tailleTmp = this->Arcs[i]->getTailleMax()- this->Arcs[i]->getLength();
			if(tailleTmp< 0)tailleTmp= -tailleTmp;
			if(tailleTmp> btScalar(0.1))
			{
				this->action[i] = new ActionPiston(this->Arcs[i],this->Arcs[i]->getTailleMax());
				//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) actionThread,action[i], 0, &threadID);
				Thread((void*)this->action[i],actionThread);
			}
		}
	}
}


void RobotTetra::move(int x, int y, int z) {

	int NHaut=0,N1=-1,N2=-1,NRestant=-1;
	int PBas = -1,PHaut = -1,P1=-1,P2=-1;
	int i,j;
	btVector3 vectTMP[3];
	Noeud* noeuds[4];
	// On va deplacer le robot
	// On choisi un point d'arrive du robot sur le cercle de centre ( G : center of masse et de rayon R = 5.)
	printf("Test 1 : btVector3 end = robot->bodyCube->getCenterOfMassPosition();\n");
	btVector3 end = this->bodyCube->getCenterOfMassPosition();
	/*
	 *
	 *
	 *
	 * Segfault ici ! Test 1 affiché, pas Test 2 !
	 *
	 *
	 *
	 *
	 */
	printf("Test 2 : end.setY(btScalar(robot->getCenterOfMassPosition().getY()));\n");
	end.setY(btScalar(this->getCenterOfMassPosition().getY()));

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
		//if(this->action[i]!=NULL){
		printf("Test 5 : robot->action[i] = new ActionPiston(robot->Arcs[i],robot->Arcs[i]->getTailleMax()/2); \n");
			this->action[i] = new ActionPiston(this->Arcs[i],this->Arcs[i]->getTailleMax()/2);
		//}
	}
	printf("Test 6 : while(robot->IsNotInArea(robot->getCenterOfMassPosition(),end)) \n");
	while(this->IsNotInArea(this->getCenterOfMassPosition(),end))
	{
		// Mettre le robot � l'etat initial (pistons au minimum de leur taille)
		for(i=0;i<6;i++)
		{
			this->action[i]->setPiston(this->Arcs[i]);
			this->action[i]->setTailleVoulu(this->Arcs[i]->getTailleMin());
			Thread((void*)this->action[i],actionThread);
		}
		// On attends 8 secondes que l'initialisation ce termine
		sleep(8);
		NHaut = 0;
		// On cherche le noeud NHaut le plus haut.
		for(i=1;i<4;i++)
		{
			vectTMP[0] = (this->Sommets[NHaut]->getCenterOfMassPosition());
			vectTMP[1] = (this->Sommets[i]->getCenterOfMassPosition());
			if((vectTMP[0].y()) < (vectTMP[1].y()))
				NHaut = i;
		}
		// On cherche maintenant les 2 noeuds de la base les plus proches du point d'arriv� end.
		j=0;
		for(i=0;i<4;i++)
		{
			if(i!= NHaut && j<3){
				noeuds[j] = this->Sommets[i];
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
		this->action[PBas]->setPiston(this->Arcs[PBas]);
		this->action[PBas]->setTailleVoulu(btScalar(8.));
		Thread((void*)this->action[PBas],actionThread);

		// On debloque les pistons liant le noeuds NHaut (P1 et P2)
		//printf("P1: %d, P2: %d\n",matLiaison[NHaut][N1],matLiaison[NHaut][N2]);
		P1 = matLiaison[NHaut][N1];
		P2 = matLiaison[NHaut][N2];
		//printf("P1: %d, P2: %d\n",P1,P2);
		this->Arcs[P1]->debloquerPiston();
		this->Arcs[P2]->debloquerPiston();


		// On mets le piston d'identificateur PHaut � sa taille maximale
		this->action[PHaut]->setPiston(this->Arcs[PHaut]);
		this->action[PHaut]->setTailleVoulu(this->Arcs[PHaut]->getTailleMax());
		Thread((void*)this->action[PHaut],actionThread);
		// On attends 10 secondes
		sleep(10);
		// On bloque les pistons liant le noeuds NHaut precedement debloques
		this->Arcs[P1]->bloquerPiston();
		this->Arcs[P2]->bloquerPiston();
		// On debloque les contraintes coniques des deux precedents pistons


	}// Fin WHILE
	// La marche du robot est termin�e.
	// Mettre le robot � l'etat final (pistons au minimum de leur taille)
	for(i=0;i<6;i++)
	{
		this->action[i]->setPiston(this->Arcs[i]);
		this->action[i]->setTailleVoulu(this->Arcs[i]->getTailleMin());
		Thread((void*)this->action[i],actionThread);
	}
	// Attendre que les pistons soient arretes
	sleep(8);

	printf("Arret du robot!\n");

}

