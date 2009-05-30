#include "PistonRendering.h"


// Constructeur
PistonRendering::PistonRendering(Ogre::Real lMin, Ogre::Real lMax, Ogre::SceneManager *scene, int numPis) {

	// Calcul du nombre de cylindres necessaire pour respecter les
	// Specifications d'etirement du piston
	this->lMin = lMin+2.;//+2. temporaire en attendant que le piston touche la boule dans bullet
	this->lMax = lMax+2.;//idem
	float tmp = (0.98*this->lMax+0.04*this->lMin)/(this->lMin*0.96-0.02*this->lMax) ;
	this->nbC = tmp ;
	if ( tmp > this->nbC ) {
		this->nbC++;
	}
	printf("Creation Piston %d (nbC = %d, lMin = %f, lMax = %f)\n", numPis, this->nbC, this->lMin, this->lMax);
	// Calcul de la longueur d'un cylindre
	this->lC = this->lMin/(0.98+0.02*this->nbC) ;
	this->scene = scene;
	this->num = numPis;
	std::ostringstream out1;
	out1 << "Piston" << numPis << "Cylindre0" ;
	scene->createEntity(out1.str(), "Cylindre.mesh");
	std::ostringstream out2;
	out2 << "NodePiston" << numPis << "Cylindre0";
	scene->getRootSceneNode()->createChild(out2.str());
	scene->getSceneNode(out2.str())->setVisible(false,true);
	scene->getSceneNode(out2.str())->attachObject(scene->getEntity(out1.str()));
	Ogre::Vector3 longueur = scene->getEntity(out1.str())->getBoundingBox().getSize() ;
	Ogre::Real facteurScale = (this->lC)/(longueur.z);

	scene->getSceneNode(out2.str())->scale(facteurScale,facteurScale,facteurScale);

	for (int i=1 ; i<this->nbC ; i++) {

		std::ostringstream out1;
		std::ostringstream out2;
		std::ostringstream out3;
		out1 << "Piston" << numPis << "Cylindre" << i-1;
		out2 << "Piston" << numPis << "Cylindre" << i;
		out3 << "NodePiston" << numPis << "Cylindre" << i;
		scene->getEntity(out1.str())->clone(out2.str());
		//this->c.push_back(scene->getEntity(out2.str()));
		scene->getRootSceneNode()->createChild(out3.str());
		scene->getSceneNode(out3.str())->setVisible(false,true);
		scene->getSceneNode(out3.str())->attachObject(scene->getEntity(out2.str()));
		scene->getSceneNode(out3.str())->scale(facteurScale*(pow(0.8,i)),facteurScale*(pow(0.8,i)),facteurScale);
	}

}

PistonRendering::~PistonRendering() {

	
}

void PistonRendering::afficherPiston(Ogre::SceneNode *b1, Ogre::SceneNode *b2) {

	Ogre::Real lP; // Longueur courante du piston
	Ogre::Vector3 v; // Le vecteur b1-b2


	v = (b2->getPosition()-b1->getPosition());
	lP = v.length()-2*BOULE_RAYON;

	Ogre::Real lP2 = lP-lC;

	for (int i=0 ; i<this->nbC ; i++ ) {

		std::ostringstream out1;
		out1 << "NodePiston" << this->num << "Cylindre" << i;
		Ogre::Quaternion rot;
		rot = this->scene->getSceneNode(out1.str())->getOrientation();
		rot = rot.zAxis().getRotationTo(v);
		this->scene->getSceneNode(out1.str())->rotate(rot,Ogre::Node::TS_WORLD);

		Ogre::Real distance;
		if ( i== 0 ) {
			distance = this->lC/2+BOULE_RAYON;
		} else {
			std::ostringstream out2;
			out2 << "NodePiston" << this->num << "Cylindre" << i-1;
			distance = (this->scene->getSceneNode(out2.str())->getPosition()-b1->getPosition()).length()+lP2/(this->nbC-1);
		}

		v.normalise();

		this->scene->getSceneNode(out1.str())->setPosition(b1->getPosition()+distance*v);

		scene->getSceneNode(out1.str())->setVisible(true,true);
	}
}
