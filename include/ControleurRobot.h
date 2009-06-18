/**
 * \file ControleurRobot.h
 * \brief Gère les mouvements d'un robot par le biais de sinusoides (une par piston).
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
 * Le comportement est défini suivant un tableau de sinusoïdes.
 * Chaque sinusoïde controle la taille d'un arc (classe Edge) du robot donné.
 * Un déplacement correspond à une étape du controleurRobot, le numéro de l'étape servant à calculer la longueur de chaque arc du robot.
 */
class ControleurRobot
{
protected:
	// robot : robot traitait par ce controleur
	PhysicRobot* robot; /**< Robot sur lequel on va appliquer un comportement. */
	// tabSin : vecteur de sinusoide
	btAlignedObjectArray<Sinusoide*> tabSin; /**< Tableau de sinusoïdes représentant le comportement du robot. Chaque sinusoide controle un arc ( classe Edge ) donné. */
	// tabction : vecteur d Action de piston
	btAlignedObjectArray<ActionPiston*> tabAction; /**< Tableau d'actions sur les arcs (classe Edge) du robot. */
	// etape : etape courante
	int etape; /**< Numéro de l'étape courante.*/
	// id : identifiant
	int id; /**< Identifiant du contrôleur.*/
	// posInitial : position initiale du robot au debut du test
	btVector3 posInitial; /**< Position du robot au début du déplacement.*/
	// resultat : distance entre le point d arrivee et le point de depart
	Resultat* resultat; /**< Données obtenues après déplacement. */

public:
	// Constructeur de la classe ControleurRobot avec les parametres d une sinusoide
	/**
	 * \fn ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax)
	 * \brief Constructeur de la classe ControleurRobot créant un comportement aléatoire basé sur les paramètres limites de sinusoïde.
	 * Chacune des sinusoïdes crées contrôlera un des arcs (classe Edge) du robot.
	 * \param robot Robot sur lequel on applique le contrôleur.
	 * \param periodeMax Période maximum autorisée pour définir aléatoirement les sinusoïdes.
	 * \param amplitudeMax Amplitude maximum autorisée pour définir aléatoirement les sinusoïdes.
	 * \param dephasageMax Déphasege maximum autorisée pour définir aléatoirement les sinusoïdes.
	 */
	ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);

	// Constructeur de la classe ControleurRobot avec un vecteur de sinusoide
	/**
	 * \fn ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);
	 * \brief Constructeur de la classe ControleurRobot affectant un comportement défini par l'utilisateur.
	 * Le comportement est décrit par un tableau de sinusoïdes. Chaque sinusoïde agit sur un arc (classe Edge) donné.
	 * Il faut donc s'assurer d'avoir autant de sinusoïdes que le robot a d'arc.
	 * \param robot Robot sur lequel on applique le contrôleur.
	 * \param tab_Sinus Tableau de sinusoïdes définissant le comportement du robot.
	 */
	ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);

	// Destructeur de l objet
	/**
	 * \fn ~ControleurRobot();
	 * \brief Ce destructeur détruit tout hormis le robot, car il ne fait qu'utiliser celui-ci.
	 */
	~ControleurRobot();

	// Retourne un vecteur de sinusoide
	/**
	 * \fn btAlignedObjectArray<Sinusoide*> getTabSin();
	 * \brief getter
	 * \return Le tableau de sinusoïdes définissant le comportement du robot. Chaque sinusoïde agit sur un des arcs (classe Edge) constituant le robot.
	 */
	btAlignedObjectArray<Sinusoide*> getTabSin();

	// Retourne l etape courante du controleur
	/**
	 * \fn int getEtape();
	 * \brief getter
	 * \return Numéro de l'étape courante du contrôleur.
	 */
	int getEtape();

	// Retourne le robot traité par ce controleur
	/**
	 * \fn PhysicRobot* getRobot();
	 * \brief getter
	 * \return Robot utilisé par le contrôleur.
	 */
	PhysicRobot* getRobot();

	// Retourne le resultat du controleur
	/**
	 * \fn Resultat* getResultat();
	 * \brief getter
	 * \return Résultats du robot obtenu après un déplacement. Retourne un résultat neutre (non indicatif) si aucun déplacement n'a été effectué.
	 */
	Resultat* getResultat();

	// retourne l'identifiant du controleur
	/**
	 * \fn int getID();
	 * \brief getter
	 * \return Identifiant du contrôleur de robot.
	 */
	int getID();

	//Les methodes
	// Methode effectuant l'etape  numEtape.
	/**
	 * \fn void execute(int numEtape);
	 * \brief Méthode éxécutant un mouvement ( déplacement ).
	 * Chaque sinusoïde représentant la longueur d'un des arcs du robot, le mouvement créé est tel que chaque piston p aura une longueur de tabSin[p].sinus(numEtape).
	 * \param numEtape numéro de l'étape à effectuer
	 */
	void execute(int numEtape);

	// Methode creant une instance Resultat
	/**
	 * \fn void updateResultat();
	 * \brief Méthode recalculant les résultats obtenus par le robot.
	 */
	void updateResultat();

private:
	// methode appelée lors de a creation du controleur
	// pour lui ttribuer un identificateur.
	/**
	 * \fn void setID();
	 * \brief methode privée appelée lors de la creation du contrôleur pour lui attribuer un identificateur.
	 */
	void setID();
};

#endif /* CONTROLEURROBOT_H */
