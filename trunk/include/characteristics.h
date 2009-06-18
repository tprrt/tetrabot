/**
 * \file characteristics.h
 * \author Frozen Brains
 * \brief Fichier de description du monde et du robot
 * \version 0.1
 */


#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H

//-----------------------------------------------------------------------------
//-------------------------CARACTERISTIQUES PHYSIQUES--------------------------
//-----------------------------------------------------------------------------
#define NODE_NUMBER 4 /**< Nombre de nœuds composant le piston */
#define NODE_WEIGHT 1.80 /**< Poids de chaque nœud */
#define NODE_RADIUS 2.0 /**< Rayon de chaque nœud */

#define EDGE_NUMBER 6 /**< Nombre de pistons */
#define EDGE_MIN_SIZE 3.0 /**< Taille minimum d'un piston */
#define EDGE_MAX_SIZE 10.0 /**< Taille maximum d'un piston */
#define EDGE_WEIGHT 0.1 /**< Poids d'un piston */

#define EDGE_VELOCITY 2.5 /**< Vélocité de déploiement du piston. */
#define EDGE_STRENGTH 1 /**< Force générée par le moteur de chaque piston. */

#define EDGE_WAIT 10 /**< temps (en secondes) permis pour changer la taille d'un piston. */

#define CUBE_SIZE 1 /**< Taille des arêtes des cubes représentant les extrémités d'un piston. */

#define SIGNAL_PERIOD_MAX 2*M_PI /**< Période maximum (utilisée pour définir une sinusoide). */
#define SIGNAL_SCALE_MAX 10.0 /**< Amplitude maximum (utilisée pour définir une sinusoide). */
#define SIGNAL_PHASE_SHIFT_MAX 2*M_PI /**< Déphasage maximum (utilisé pour définir une sinusoide). */

#define RUBDOWN 4.0 /**< Friction entre les nœuds des robots et le terrain. */
#define CONE_ANGLE M_PI_4/1.5 /**< Angle définissant la base (cercle)  du cône représentant la contrainte conique. */


#define WORLD_GRAVITY -9.8 /**< Gravité du monde */
#define WORLD_MIN -1000 /**< Taille minimale du monde physique virtuel suivant un axe (même valeur pour les 3 axes x,y et z). */
#define WORLD_MAX 1000 /**< Taille maximale du monde physique virtuel suivant un axe (même valeur pour les 3 axes x,y et z). */

#define GROUND_SCALE 6 /**< Echelle de redimensionnement du terrain (utilisé lors de l'importation de mesh). */

//-----------------------------------------------------------------------------
//-----------------------CARACTERISTIQUES MATHEMATIQUES------------------------
//-----------------------------------------------------------------------------
#define M_PI 3.14159265358979323846 /**< Pi */
#define M_PI_2 1.57079632679489661923 /**< Pi/2 */
#define M_PI_4 0.785398163397448309616 /**< Pi/4 */

#endif /* CHARACTERISTICS_H */
