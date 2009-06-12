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
#define NODE_WEIGHT 1.80 /**< Poid de chaque nœud */
#define NODE_RADIUS 2.0 /**< Rayon de chaque nœud */

#define EDGE_NUMBER 6 /**< Nombre d'aretes */
#define EDGE_MIN_SIZE 3.0 /**< Taille minimum d'une arete */
#define EDGE_MAX_SIZE 10.0 /**< Taille maximum d'une arete */
#define EDGE_WEIGHT 0.1 /**< Poids d'une arete */

#define EDGE_VELOCITY 2.5 /**<  */
#define EDGE_STRENGTH 1 /**<  */

#define EDGE_WAIT 10 /**<  */

#define CUBE_SIZE 1 /**<  */

#define SIGNAL_PERIOD_MAX 2*M_PI /**<  */
#define SIGNAL_SCALE_MAX 10.0 /**<  */
#define SIGNAL_PHASE_SHIFT_MAX 2*M_PI /**<  */

#define RUBDOWN 4.0 /**<  */
#define CONE_ANGLE M_PI_4/1.5 /**<  */

#define WORLD_GRAVITY -9.8 /**< Gravite du monde */
#define WORLD_MIN -1000 /**<  */
#define WORLD_MAX 1000 /**<  */

#define GROUND_SCALE 6 /**<  */

//-----------------------------------------------------------------------------
//-----------------------CARACTERISTIQUES MATHEMATIQUES------------------------
//-----------------------------------------------------------------------------
#define M_PI 3.14159265358979323846 /**< Pi */
#define M_PI_2 1.57079632679489661923 /**< Pi/2 */
#define M_PI_4 0.785398163397448309616 /**< Pi/4 */

#endif /* CHARACTERISTICS_H */
