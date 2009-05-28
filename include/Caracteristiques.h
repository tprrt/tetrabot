
#ifndef CARACTERISTIQUES
#define CARACTERISTIQUES

//-----------------------------------------------------------------------------
//-------------------------CARACTERISTIQUES PHYSIQUES--------------------------
//---------------------------- EXTERNES AU PROJET -----------------------------
#define POIDS_BOULE btScalar(0.7)
#define RAYON_BOULE btScalar(2.)
#define VELOCITE_PISTON btScalar(2.5)
#define FORCE_PISTON btScalar(0.01)
#define PISTON_TAILLE_MIN btScalar(3.)
#define TAILLE_PISTON_MIN 3.
#define PISTON_TAILLE_MAX btScalar(10.)
#define TAILLE_PISTON_MAX 10.
#define NB_PISTON 6

#define PERIODE_MAX btScalar(2*M_PI)
#define AMPLITUDE_MAX btScalar(10)
#define DEPHASAGE_MAX btScalar(2*M_PI)


//---------------------------- INTERNES AU PROJET -----------------------------
#define FRICTION btScalar(4.)
#define POIDS_EXTREMITE_PISTON btScalar(0.1)
#define ANGLES_CONE btScalar(M_PI_4/1.5)

// Duree maximum pour etirer/retracter un piston
#define ATTENTE_PISTON 10



//-----------------------------------------------------------------------------
//-----------------------CARACTERISTIQUES MATHEMATIQUES------------------------
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
//-----------------------------------------------------------------------------
#endif /* CARACTERISTIQUES */
