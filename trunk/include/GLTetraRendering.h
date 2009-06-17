/**
 * \file GLTetraRendering.h
 * \brief Gere le rendu graphique en mode debug ( OpenGL ).
 * \author Frozen Brains
 * \version 0.1
 */

//-----------------------------------------------------------------------------

#ifndef GLTETRARENDERING_H
#define GLTETRARENDERING_H

//-----------------------------------------------------------------------------

#include <cstdio> //printf debugging

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/ConstraintSolver/btSliderConstraint.h"
#include "Application.h"
#include "Threads.h"
#include "PhysicWorld.h"
#include "WorldInfo.h"
#include "RobotTetra.h"
#include "characteristics.h"
#include "ControleurRobot.h"
#include "Sinusoide.h"
#include "PhysicPiston.h"
#include "PhysicNoeud.h"
#include "Action.h"
#include "LinearMath/btIDebugDraw.h"
#include "GLDebugDrawer.h"
#include "BMF_Api.h"
#include "GL_ShapeDrawer.h"
#include "GlutStuff.h"
//Pour TEST
#include "AlgoGenTetra.h"
//-----------------------------------------------------------------------------


/**
 * \class GLTetraRendering
 * \brief Gere le rendu graphique en mode debug ( OpenGL ).
 */
class GLTetraRendering : public Application
{
public:
	//ATTRIBUTS
	//keep track of variables to delete memory at the end
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
	
	class btBroadphaseInterface*	m_overlappingPairCache;
	
	class btCollisionDispatcher*	m_dispatcher;
	
	class btConstraintSolver*	m_constraintSolver;
	
	class btDefaultCollisionConfiguration* m_collisionConfiguration;
	
	ActionPiston *action[6]; /**< tableau des actions des pistons */

	PhysicWorld * world; /**< le monde physique */
	
	RobotTetra * robot; /**< robot qui est dans le monde bullet*/
	
	btRigidBody* bodyCube; /**< bodyCube : indicateur de la position cible*/
	
	btRigidBody* bodyPave; /**< bodyPave : indicateur de piston*/

public:
	//METHODE
	/**
	* \fn GLTetraRendering();
	* \brief Constructeur de la classe GLTetraRendering pour initialiser le rendu.
	*/
	GLTetraRendering();
	
	/**
	* \fn GLTetraRendering();
	* \brief Destructeur de la classe GLTetraRendering
	*/
	virtual ~GLTetraRendering();

	/**
	* \fn void	initPhysics();
	* \brief Methode pour initialiser le monde bullet et pour creer un robot
	*/
	void	initPhysics();
	
	/**
	* \fn void	initModel();
	* \brief Methode pour initialiser le model
	*/
	void	initModel();

	/**
	* \fn void	drawSliders();
	* \brief Méthode permettant d'afficher à l'écran les repères internes des objets Bullet (rigidBody). Les repères sont en bleu/vert/rouge.
	*/
	void	drawSliders();

	/**
	* \fn void	drawSliderConstraint(btSliderConstraint* constraint);
	* \brief Méthode permettant d'afficher en blanc la contrainte linéaire passée en paramètre.
	* \param [constraint] : Contrainte linéaire à afficher.
	*/
	void	drawSliderConstraint(btSliderConstraint* constraint);

	/**
	* \fn virtual void clientMoveAndDisplay();
	* \brief Méthode effectuant le rendu de l'application.
	*/
	virtual void clientMoveAndDisplay();
	
	/**
	* \fn virtual void displayCallback();
	* \brief Methode affichant les contraintes linéaires des pistons du robot
	*/
	virtual void displayCallback();

	/**
	* \fn static Application* Create()
	* \brief Methode créant l'application de manière statique.
	*/
	static Application* Create()
	{
		GLTetraRendering* demo = new GLTetraRendering();
		demo->myinit();
		demo->initPhysics();
		return demo;
	}
	
	/**
	* \fn void specialKeyboard(int key, int x, int y);
	* \brief Methode pour interagir avec bullet ( touches clavier Fn )
	* \param key : touche du clavier
	* \param x : position x
	* \param y : position y
	*/
	void specialKeyboard(int key, int x, int y);
	
	/**
	* \fn void keyboardCallback(unsigned char key, int x, int y);
	* \brief Methode pour interagir avec bullet ( touches clavier )
	* \param key : touche du clavier
	* \param x : position x
	* \param y : position y
	*/
	void keyboardCallback(unsigned char key, int x, int y);

	/**
	* \fn void renderme();
	* \brief Methode de rendu pour l'affichage de l'application.
	*/
	void renderme();
};

#endif /* GLTETRARENDERING_H */

