//  @ Project : Tetrabot
//  @ File Name : ControleurRobot.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains

#ifndef CONTROLEURROBOT_H
#define CONTROLEURROBOT_H

#include "Sinusoide.h"
#include "PhysicRobot.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "Threads.h"
#include "ActionPiston.h"
#include "Resultat.h"

// pour les fonctions rand() et srand(...)
#include <cstdlib>
// redefinition de la constante RAND_MAX
#define RAND_MAX 0xffff 

class ControleurRobot
{
protected:
	// robot : robot traitait par ce controleur
	PhysicRobot* robot;
	// tabSin : vecteur de sinusoide
	btAlignedObjectArray<Sinusoide*> tabSin;
	// tabction : vecteur d Action de piston
	btAlignedObjectArray<ActionPiston*> tabAction;
	// etape : etape courante
	int etape;
	// id : identifieur
	int id;
	// posInitial : position initiale du robot au debut du test
	btVector3 posInitial;
	// resultat : distance entre le point d arrivee et le point de depart
	Resultat* resultat;

public:
	// Constructeur de la classe ControleurRobot avec les parametres d une sinusoide
	ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);
	// Constructeur de la classe ControleurRobot avec un vecteur de sinusoide
	ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);
	// Destructeur de l objet
	~ControleurRobot();
	// Retourne un vecteur de sinusoide
	btAlignedObjectArray<Sinusoide*> getTabSin();
	// Retourne l etape courante du controleur
	int getEtape();
	// Retourne le robot traitait par ce controleur
	PhysicRobot* getRobot();
	// Retourne le resultat du controleur
	Resultat* getResultat();

	// retourne l'identifiant du controleur
	int getID();

	//Les methodes
	// Methode effectuant l'etape  numEtape.
	void execute(int numEtape);

	// Methode creant une instance Resultat
	void updateResultat();

private:
	// methode appelée lors de a creation du controleur
	// pour lui ttribuer un identificateur.
	void setID();
};

#endif /* CONTROLEURROBOT_H */
