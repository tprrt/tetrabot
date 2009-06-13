/**
 * \file TetraMotionState.h
 * \brief Assure la liaison entre Bullet et Ogre (Wrapper Bullet/Ogre).
 * \author Frozen Brains
 * \version 0.1
 */

#ifndef TETRAMOTIONSTATE_H
#define TETRAMOTIONSTATE_H

#include "LinearMath/btMotionState.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "Ogre.h"
#else
#include <OGRE/Ogre.h>
#endif
/**
* \class TetraMotionState
* \brief Classe permettant la communication de la position d'un composant physiques � un noeud de sc�ne du moteur graphique Ogre.
	Cette classe est utilis�e sous Bullet pour d�finir un objet rigide, un composant...
	Les instances sont automatiquement mis � jour par le moteur physique.
*/
class TetraMotionState : public btMotionState 
{

protected:
	Ogre::SceneNode *mVisibleobj; /**< mVisibleobj : noeud de sc�ne du moteur Ogre repr�sentant un composant physique. */
	btTransform mPos1;/**< mPos1 : transformation ( rotation + translation ) du composant. */

public:
	/**
	* \fn TetraMotionState(const btTransform &initialpos, Ogre::SceneNode *node);
	* \brief Constructeur
	* \param [initialpos] : transformation initiale du composant.
	* \param [node] : pointeur de noeud de sc�ne repr�sentant le composant sous Ogre.
	*/
	TetraMotionState(const btTransform &initialpos, Ogre::SceneNode *node);
	//virtual ~TetraMotionState();

	/**
	* \fn void setNode(Ogre::SceneNode *node);
	* \brief setter : affecte un nouveau noeud de sc�ne Ogre � l'objet, composant,etc... manipul� par Bullet.
	* \param [node] : pointeur de noeud de sc�ne repr�sentant le composant sous Ogre.
	*/
	void setNode(Ogre::SceneNode *node);

	/**
	* \fn virtual void getWorldTransform(btTransform &worldTrans) const;
	* \brief getter : affecte la transformation courante de l'objet dans la variable worldTrans
	* \param [worldTrans] : variable permettant de r�cup�rer la transformation courante.
	*/
	virtual void getWorldTransform(btTransform &worldTrans) const;

	/**
	* \fn virtual void setWorldTransform(const btTransform &worldTrans);
	* \brief Mets � jours la position et l'orientation du noeud de sc�ne Ogre.
		Cette m�thode est appell�e de mani�re r�cursive et automatique par le moteur physique Bullet.
	* \param [worldTrans] : transformation de l'objet du point de vue du monde physique virtuel de Bullet.
	*/
	virtual void setWorldTransform(const btTransform &worldTrans);

};
#endif /* TETRAMOTIONSTATE_H */
