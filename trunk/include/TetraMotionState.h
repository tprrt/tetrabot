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
* \brief Classe permettant la communication de la position d'un composant physiques à un noeud de scène du moteur graphique Ogre.
	Cette classe est utilisée sous Bullet pour définir un objet rigide, un composant...
	Les instances sont automatiquement mis à jour par le moteur physique.
*/
class TetraMotionState : public btMotionState 
{

protected:
	Ogre::SceneNode *mVisibleobj; /**< mVisibleobj : noeud de scène du moteur Ogre représentant un composant physique. */
	btTransform mPos1;/**< mPos1 : transformation ( rotation + translation ) du composant. */

public:
	/**
	* \fn TetraMotionState(const btTransform &initialpos, Ogre::SceneNode *node);
	* \brief Constructeur
	* \param [initialpos] : transformation initiale du composant.
	* \param [node] : pointeur de noeud de scène représentant le composant sous Ogre.
	*/
	TetraMotionState(const btTransform &initialpos, Ogre::SceneNode *node);
	//virtual ~TetraMotionState();

	/**
	* \fn void setNode(Ogre::SceneNode *node);
	* \brief setter : affecte un nouveau noeud de scène Ogre à l'objet, composant,etc... manipulé par Bullet.
	* \param [node] : pointeur de noeud de scène représentant le composant sous Ogre.
	*/
	void setNode(Ogre::SceneNode *node);

	/**
	* \fn virtual void getWorldTransform(btTransform &worldTrans) const;
	* \brief getter : affecte la transformation courante de l'objet dans la variable worldTrans
	* \param [worldTrans] : variable permettant de récupérer la transformation courante.
	*/
	virtual void getWorldTransform(btTransform &worldTrans) const;

	/**
	* \fn virtual void setWorldTransform(const btTransform &worldTrans);
	* \brief Mets à jours la position et l'orientation du noeud de scène Ogre.
		Cette méthode est appellée de manière récursive et automatique par le moteur physique Bullet.
	* \param [worldTrans] : transformation de l'objet du point de vue du monde physique virtuel de Bullet.
	*/
	virtual void setWorldTransform(const btTransform &worldTrans);

};
#endif /* TETRAMOTIONSTATE_H */
