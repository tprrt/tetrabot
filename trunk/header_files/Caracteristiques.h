
#ifndef CARACTERISTIQUES
#define CARACTERISTIQUES
//-----------------------------------------------------------------------------
//-------------------------CARACTERISTIQUES PHYSIQUES--------------------------
//---------------------------- EXTERNES AU PROJET -----------------------------
#define POIDS_BOULE btScalar(8.)
#define RAYON_BOULE btScalar(3.)
#define VELOCITE_PISTON btScalar(3.)
#define FORCE_PISTON btScalar(14.)
#define PISTON_TAILLE_MIN btScalar(3.)
#define PISTON_TAILLE_MAX btScalar(10.)

#define PERIODE_MAX 20
#define AMPLITUDE_MAX 6
#define DEPHASAGE_MAX 2*M_PI
//---------------------------- INTERNES AU PROJET -----------------------------
#define FRICTION btScalar(4.)
#define POIDS_EXTREMITE_PISTON btScalar(1.)
#define ANGLES_CONE btScalar(M_PI_4/2.)

// Duree maximum pour etirer/retracter un piston
#define ATTENTE_PISTON 10



//-----------------------------------------------------------------------------
//-----------------------CARACTERISTIQUES MATHEMATIQUES------------------------
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
//-----------------------------------------------------------------------------
#endif