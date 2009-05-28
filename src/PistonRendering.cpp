#include "PistonRendering.h"


// Constructeur
PistonRendering::PistonRendering(Ogre::Real lMin, Ogre::Real lMax, Ogre::SceneManager *scene, int numPis) {

	// Calcul du nombre de cylindres necessaire pour respecter les
	// Specifications d'etirement du piston
	this->lMin = lMin;
	this->lMax = lMax;
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
	//printf("longueur = %f\n, facteurScale = %f\n", longueur.z, facteurScale);
	scene->getSceneNode(out2.str())->scale(facteurScale,facteurScale,facteurScale);
	//Ogre::Vector3 truc = scene->getSceneNode(out2.str())->getScale();
	//printf("new longueur = (%f,%f,%f) * (%f,%f,%f) = (%f,%f,%f)\n", longueur.x, longueur.y, longueur.z, truc.x, truc.y, truc.z, longueur.x*truc.x, longueur.y*truc.y, longueur.z*truc.z);
	//this->c.push_back(scene->getEntity(out1.str())) ;
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
		scene->getSceneNode(out3.str())->scale(facteurScale*0.8,facteurScale*0.8,facteurScale);
	}

}


void PistonRendering::afficherPiston(Ogre::SceneNode *b1, Ogre::SceneNode *b2) {
	Ogre::Real lP; // Longueur courante du piston
	Ogre::Vector3 v; // Le vecteur b1-b2
	//printf("Affichage Piston %d (nbC = %d, lC = %f)\n", this->num, this->nbC, this->lC	);
	v = (b2->getPosition()-b1->getPosition());
	lP = v.length()-2*BOULE_RAYON;
	printf("lP = %f\n", lP);
	//Ogre::Vector3 temp = b1->getPosition();
	//printf("\t\tb1 :\tx = %f ; y = %f ; z = %f\n", temp.x, temp.y, temp.z);
	Ogre::Real lP2 = lP-lC;
	//printf("lP2 = %f\n", lP2);
	for (int i=0 ; i<this->nbC ; i++ ) {
		//printf("Affichage Piston %d Cylindre %d\n", this->num, i);
		std::ostringstream out1;
		out1 << "NodePiston" << this->num << "Cylindre" << i;
		Ogre::Quaternion rot;
		rot = this->scene->getSceneNode(out1.str())->getOrientation();
		rot = rot.zAxis().getRotationTo(v);
		this->scene->getSceneNode(out1.str())->rotate(rot);
		Ogre::Real distance;
		if ( i== 0 ) {
			distance = this->lC/2+BOULE_RAYON;
		} else {
			std::ostringstream out2;
			out2 << "NodePiston" << this->num << "Cylindre" << i-1;
			distance = (this->scene->getSceneNode(out2.str())->getPosition()-b1->getPosition()).length()+lP2/(this->nbC-1);
		}
		//Ogre::Vector3 temp = b1->getPosition();
		v.normalise();
		//printf("Distance = %f ; pos(b1) = (%f,%f,%f) ; v(normé) = (%f,%f,%f) \n", distance, temp.x, temp.y, temp.z, v.x, v.y, v.z);
		this->scene->getSceneNode(out1.str())->setPosition(b1->getPosition()+distance*v);
		//temp = this->scene->getSceneNode(out1.str())->getPosition();
		//printf("Piston %d Cylindre %d : \tx = %f ; y = %f ; z = %f\n", this->num, i, temp.x, temp.y, temp.z);
		scene->getSceneNode(out1.str())->setVisible(true,true);
	}
	//temp = b2->getPosition();
	//printf("\t\tb2 :\tx = %f ; y = %f ; z = %f\n", temp.x, temp.y, temp.z);
}
