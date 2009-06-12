/**
 * \file GLTetraRendering.h
 * \brief Gere le mode debug ( OpenGL )
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


/// SliderConstraintDemo shows how to create a slider constraint
/**
 * \class GLTetraRendering
 * \brief Gere le mode debug ( OpenGL )
 */
class GLTetraRendering : public Application
{
public:
	//ATTRIBUTS
	//keep track of variables to delete memory at the end
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
	
	class btBroadphaseInterface*	m_overlappingPairCache; /**< m_overlappingPairCache : */
	
	class btCollisionDispatcher*	m_dispatcher; /**<  m_dispatcher : */
	
	class btConstraintSolver*	m_constraintSolver; /**< m_constraintSolver : */
	
	class btDefaultCollisionConfiguration* m_collisionConfiguration; /**< m_collisionConfiguration : */
	
	ActionPiston *action[6]; /**< tableau des actions des pistons */

	PhysicWorld * world; /**< le monde physique */
	
	RobotTetra * robot; /**< robot qui est dans le monde bullet*/
	
	btRigidBody* bodyCube; /**< bodyCube : indicateur de la position cible*/
	
	btRigidBody* bodyPave; /**< bodyPave : indicateur de piston*/

public:
	//METHODE
	/**
	* \fn GLTetraRendering();
	* \brief Constructeur de la classe GLTetraRendering pour initialiser les Actions des pistons d un robot
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
	* \brief 
	*/
	void	drawSliders();

	/**
	* \fn void	drawSliderConstraint(btSliderConstraint* constraint);
	* \brief 
	* \param constraint
	*/
	void	drawSliderConstraint(btSliderConstraint* constraint);

	virtual void clientMoveAndDisplay();
	
	/**
	* \fn virtual void displayCallback();
	* \brief Methode pour dessiner les contraintes lienaires des pistons du robot
	*/
	virtual void displayCallback();

	/**
	* \fn static Application* Create()
	* \brief Methode pour lancer l'appli
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
	* \brief Methode pour configuer l affichage de ecran
	*/
	void renderme();
};

#endif /* GLTETRARENDERING_H */

