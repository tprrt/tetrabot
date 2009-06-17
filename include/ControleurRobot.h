//  @ Project : Tetrabot
//  @ File Name : ControleurRobot.h
//  @ Date : 01/06/2009
//  @ Author : Frozen Brains
/**
 * \file ControleurRobot.h
 * \brief G�re les mouvements d'un robot par le biais de sinusoides ( une par piston ).
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
* \brief Classe permettant de d�finir le comportement du d�placement d'un robot.
	Le comportement est d�fini suivant un tableau de sinusoides. 
	Chaque sinusoide controle la taille d'un arc (classe Edge) du robot donn�.
	Un d�placement correspond � une �tape du controleurRobot, le num�ro de l'�tape servant � calculer la longueur de chaque arc du robot.
*/
class ControleurRobot
{
protected:
	// robot : robot traitait par ce controleur
	PhysicRobot* robot; /**< robot : robot sur lequel on va appliquer un comportement. */
	// tabSin : vecteur de sinusoide
	btAlignedObjectArray<Sinusoide*> tabSin; /**< tabSin : tableau de sinusoides repr�sentant le comportement du robot. Chaque sinusoide controle un arc ( classe Edge ) donn�. */
	// tabction : vecteur d Action de piston
	btAlignedObjectArray<ActionPiston*> tabAction; /**< tabAction : tableau d'actions sur les arcs ( classe Edge ) du robot. */
	// etape : etape courante
	int etape; /**< etape :  num�ro de l'�tape courante.*/
	// id : identifiant
	int id; /**< id : identifiant du controleur.*/
	// posInitial : position initiale du robot au debut du test
	btVector3 posInitial; /**< posInitial : position du robot au d�but du d�placement.*/
	// resultat : distance entre le point d arrivee et le point de depart
	Resultat* resultat; /**< resultat : donn�es obtenues apr�s d�placement. */

public:
	// Constructeur de la classe ControleurRobot avec les parametres d une sinusoide
	/**
	 * \fn ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);
	 * \brief Constructeur de la classe ControleurRobot cr�ant un comportement al�atoire bas� sur les param�tres limite de sinusoide.
		Chacune des sinusoides cr�es controlera un des arc ( classe Edge ) du robot.
	 * \param [robot] :  robot sur lequel on applique le controleur.
	 * \param [periodeMax] : p�riode maximum autoris�e pour d�finir al�atoirement les sinusoides.
	 * \param [amplitudeMax] : amplitude maximum autoris�e pour d�finir al�atoirement les sinusoides.
	 * \param [dephasageMax] : dephasege maximum autoris�e pour d�finir al�atoirement les sinusoides.
	 */
	ControleurRobot(PhysicRobot* robot,btScalar periodeMax,btScalar amplitudeMax,btScalar dephasageMax);
	
	// Constructeur de la classe ControleurRobot avec un vecteur de sinusoide
	/**
	 * \fn ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);
	 * \brief Constructeur de la classe ControleurRobot affectant un comportement d�finit par l'utilisateur. 
		Le comportement est d�crit par un tableau de sinusoides. Chaque sinusoide agit sur un arc ( classe Edge ) donn�.
		Il faut donc s'assurer d'avoir autant de sinusoide que le robot a d'arc.
	 * \param [robot] :  robot sur lequel on applique le controleur.
	 * \param [tab_Sinus] : tableau de sinusoides d�finissant le comportement du robot.
	 */
	ControleurRobot(PhysicRobot* robot, btAlignedObjectArray<Sinusoide*> tab_Sinus);
	
	// Destructeur de l objet
	/**
	 * \fn ~ControleurRobot();
	 * \brief Ce destructeur d�truit tout hormis le robot, car il ne fais qu'utiliser celui-ci.
	 */
	~ControleurRobot();
	
	// Retourne un vecteur de sinusoide
	/**
	 * \fn btAlignedObjectArray<Sinusoide*> getTabSin();
	 * \brief getter
	 * \return Le tableau de sinusoides d�finissant le comportement du robot. Chaque sinusoide agit sur un des arcs ( classe Edge ) constituant le robot.
	 */
	btAlignedObjectArray<Sinusoide*> getTabSin();
	
	// Retourne l etape courante du controleur
	/**
	 * \fn int getEtape();
	 * \brief getter
	 * \return Num�ro de l'�tape courante du controleur.
	 */
	int getEtape();
	
	// Retourne le robot trait� par ce controleur
	/**
	 * \fn PhysicRobot* getRobot();
	 * \brief getter
	 * \return Robot utilis� par le controleur.
	 */
	PhysicRobot* getRobot();
	
	// Retourne le resultat du controleur
	/**
	 * \fn Resultat* getResultat();
	 * \brief getter
	 * \return R�sultats du robot obtenu  apr�s un d�placement. Retourne un r�sultat neutre ( non indicatif ) si aucun d�placement n'a �t� effectu�.
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
	 * \brief M�thode �x�cutant un mouvement ( d�placement ). 
		Chaque sinusoides repr�sentant la longueur d'un des arcs du robot, le mouvement cr�� est tel que chaque piston p aura une longueur de tabSin[p].sinus(numEtape).	
	 * \param [numEtape] : num�ro de l'�tape � effectuer.
	 */
	void execute(int numEtape);

	// Methode creant une instance Resultat
	/**
	 * \fn void updateResultat();
	 * \brief M�thode recalculant les r�sultats obtenu par le robot.
	 */
	void updateResultat();

private:
	// methode appel�e lors de a creation du controleur
	// pour lui ttribuer un identificateur.
	/**
	 * \fn void setID();
	 * \brief  methode priv�e appel�e lors de a creation du controleur pour lui ttribuer un identificateur.
	 */
	void setID();
};

#endif /* CONTROLEURROBOT_H */
