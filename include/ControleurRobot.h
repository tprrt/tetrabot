//  @ Project : Tetrabot
//  @ File Name : ControleurRobot.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file ControleurRobot.h
 * \brief Gère les mouvements d'un robot par le biais de sinusoides ( une par piston ).
 * \author Frozen Brains
 * \version 0.1
 */
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
/**
* \class ControleurRobot
* \brief Classe permettant de définir le comportement du déplacement d'un robot.
	Le comportement est défini suivant un tableau de sinusoides. 
	Chaque sinusoide controle la taille d'un arc (classe Edge) du robot donné.
	Un déplacement correspond à une étape du controleurRobot, le numéro de l'étape servant à calculer la longueur de chaque arc du robot.
*/
class ControleurRobot
{
protected:
	// robot : robot traitait par ce controleur
	PhysicRobot* robot; /**< robot : robot sur lequel on va appliquer un comportement. */
	// tabSin : vecteur de sinusoide
	btAlignedObjectArray<Sinusoide*> tabSin; /**< tabSin : tableau de sinusoides représentant le comportement du robot. Chaque sinusoide controle un arc ( classe Edge ) donné. */
	// tabction : vecteur d Action de piston
	btAlignedObjectArray<ActionPiston*> tabAction; /**< tabAction : tableau d'actions sur les arcs ( classe Edge ) du robot. */
	// etape : etape courante
	int etape; /**< etape :  numéro de l'étape courante.*/
	// id : identifiant
	int id; /**< id : identifiant du controleur.*/
	// posInitial : position initiale du robot au debut du test
	btVector3 posInitial; /**< posInitial : position du robot au début du déplacement.*/
	// resultat : distance entre le point d arrivee et le point de depart
	Resultat* resultat; /**< resultat : données obtenues après déplacement. */

public:
	// Constructeur de la classe ControleurRobot avec les parametres d une sinusoide
	/**
	 * \fn ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);
	 * \brief Constructeur de la classe ControleurRobot créant un comportement aléatoire basé sur les paramètres limite de sinusoide.
		Chacune des sinusoides crées controlera un des arc ( classe Edge ) du robot.
	 * \param [robot] :  robot sur lequel on applique le controleur.
	 * \param [periodeMax] : période maximum autorisée pour définir aléatoirement les sinusoides.
	 * \param [amplitudeMax] : amplitude maximum autorisée pour définir aléatoirement les sinusoides.
	 * \param [dephasageMax] : dephasege maximum autorisée pour définir aléatoirement les sinusoides.
	 */
	ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);
	
	// Constructeur de la classe ControleurRobot avec un vecteur de sinusoide
	/**
	 * \fn ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);
	 * \brief Constructeur de la classe ControleurRobot affectant un comportement définit par l'utilisateur. 
		Le comportement est décrit par un tableau de sinusoides. Chaque sinusoide agit sur un arc ( classe Edge ) donné.
		Il faut donc s'assurer d'avoir autant de sinusoide que le robot a d'arc.
	 * \param [robot] :  robot sur lequel on applique le controleur.
	 * \param [tab_Sinus] : tableau de sinusoides définissant le comportement du robot.
	 */
	ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);
	
	// Destructeur de l objet
	/**
	 * \fn ~ControleurRobot();
	 * \brief Ce destructeur détruit tout hormis le robot, car il ne fais qu'utiliser celui-ci.
	 */
	~ControleurRobot();
	
	// Retourne un vecteur de sinusoide
	/**
	 * \fn btAlignedObjectArray<Sinusoide*> getTabSin();
	 * \brief getter
	 * \return Le tableau de sinusoides définissant le comportement du robot. Chaque sinusoide agit sur un des arcs ( classe Edge ) constituant le robot.
	 */
	btAlignedObjectArray<Sinusoide*> getTabSin();
	
	// Retourne l etape courante du controleur
	/**
	 * \fn int getEtape();
	 * \brief getter
	 * \return Numéro de l'étape courante du controleur.
	 */
	int getEtape();
	
	// Retourne le robot traité par ce controleur
	/**
	 * \fn PhysicRobot* getRobot();
	 * \brief getter
	 * \return Robot utilisé par le controleur.
	 */
	PhysicRobot* getRobot();
	
	// Retourne le resultat du controleur
	/**
	 * \fn Resultat* getResultat();
	 * \brief getter
	 * \return Résultats du robot obtenu  après un déplacement. Retourne un résultat neutre ( non indicatif ) si aucun déplacement n'a été effectué.
	 */
	Resultat* getResultat();

	// retourne l'identifiant du controleur
	/**
	 * \fn int getID();
	 * \brief getter
	 * \return Identifiant du controleur de robot.
	 */
	int getID();

	//Les methodes
	// Methode effectuant l'etape  numEtape.
	/**
	 * \fn void execute(int numEtape);
	 * \brief Méthode éxécutant un mouvement ( déplacement ). 
		Chaque sinusoides représentant la longueur d'un des arcs du robot, le mouvement créé est tel que chaque piston p aura une longueur de tabSin[p].sinus(numEtape).	
	 * \param [numEtape] : numéro de l'étape à effectuer.
	 */
	void execute(int numEtape);

	// Methode creant une instance Resultat
	/**
	 * \fn void updateResultat();
	 * \brief Méthode recalculant les résultats obtenu par le robot.
	 */
	void updateResultat();

private:
	// methode appelée lors de a creation du controleur
	// pour lui ttribuer un identificateur.
	/**
	 * \fn void setID();
	 * \brief  methode privée appelée lors de a creation du controleur pour lui ttribuer un identificateur.
	 */
	void setID();
};

#endif /* CONTROLEURROBOT_H */
