#include "PistonRendering.h"


// Constructeur
PistonRendering::PistonRendering(Ogre::Real lMin, Ogre::Real lMax, Ogre::SceneManager *scene, int numPis) {

	// Initialisation des parametres que l'on a pas a calculer
	this->scene = scene;
	this->num = numPis;

	/* Calcul du nombre minumum de cylindres necessaires pour respecter les
	 * specifications d'etirement du piston
	 */
	this->lMin = lMin+2.; // +2. temporaire en attendant que le piston touche la boule dans bullet
	this->lMax = lMax+2.; // idem
	float tmp = (0.98*this->lMax+0.04*this->lMin)/(this->lMin*0.96-0.02*this->lMax) ;
	this->nbC = tmp ;
	if ( tmp > this->nbC ) {
		this->nbC++;
	}
	printf("Creation Piston %d (nbC = %d, lMin = %f, lMax = %f)\n", numPis, this->nbC, this->lMin, this->lMax);

	// Calcul de la longueur d'un cylindre
	this->lC = this->lMin/(0.98+0.02*this->nbC) ;

	/* Creation du SceneNode de chaque Cylindre du Piston
	 * Dont le nom est de la forme NodePistonXCylindreY
	 */
	//- On le fait d'abord pour le premier cylindre
	//-- Creation de l'entity
	// On definit le nom de l'entity
	std::ostringstream out1;
	out1 << "Piston" << numPis << "Cylindre0" ;
	// On cree l'entity a partir du mesh du cylindre
	scene->createEntity(out1.str(), "Cylindre.mesh");
	//-- Creation du sceneNode
	std::ostringstream out2;
	out2 << "NodePiston" << numPis << "Cylindre0";
	scene->getRootSceneNode()->createChild(out2.str());
	// On ne veut pas encore afficher le cylindre, on le met donc invisible
	scene->getSceneNode(out2.str())->setVisible(false,true);
	// On attache le cylindre (entity) au sceneNode
	scene->getSceneNode(out2.str())->attachObject(scene->getEntity(out1.str()));
	// On calcule la longueur actuelle du cylindre
	Ogre::Vector3 longueur = scene->getEntity(out1.str())->getBoundingBox().getSize() ;
	// On calcule le facteur de redimensionnement a appliquer pour que le cylindre soit de longueur lC
	Ogre::Real facteurScale = (this->lC)/(longueur.z);
	// On redimensionne le cylindre à la longueur lC
	scene->getSceneNode(out2.str())->scale(facteurScale,facteurScale,facteurScale);
	//- On fait de meme pour les autres pistons
	for (int i=1 ; i<this->nbC ; i++) {

		std::ostringstream out1;
		std::ostringstream out2;
		std::ostringstream out3;
		out1 << "Piston" << numPis << "Cylindre" << i-1;
		out2 << "Piston" << numPis << "Cylindre" << i;
		out3 << "NodePiston" << numPis << "Cylindre" << i;
		//-- Creation de l'entity
		// On cree l'entity par clonage du cylindre 0
		scene->getEntity(out1.str())->clone(out2.str());
		//-- Creation du sceneNode
		scene->getRootSceneNode()->createChild(out3.str());
		// On ne veut pas encore afficher le cylindre, on le met donc invisible
		scene->getSceneNode(out3.str())->setVisible(false,true);
		// On attache le cylindre (entity) au sceneNode
		scene->getSceneNode(out3.str())->attachObject(scene->getEntity(out2.str()));
		// On redimensionne le cylindre à la longueur lC, et avec un diametre inferieur au cylindre precedent
		scene->getSceneNode(out3.str())->scale(facteurScale*(pow(0.8,i)),facteurScale*(pow(0.8,i)),facteurScale);
	}

}

PistonRendering::~PistonRendering() {


}

void PistonRendering::afficherPiston(Ogre::SceneNode *b1, Ogre::SceneNode *b2) {

	Ogre::Real lP; // Longueur courante du piston
	Ogre::Vector3 v; // Le vecteur b2-b1

	// On calcule le vecteur entre les deux nœuds
	v = (b2->getPosition()-b1->getPosition());
	// La longueur du piston est egale a la longueur separant les centres des deux nœuds moins leur rayon
	lP = v.length()-2*NODE_RADIUS;
	// Calcul de la longueur separant les centres des cylindres aux extremites
	Ogre::Real lP2 = lP-lC;

	// Positionnement des pistons
	for (int i=0 ; i<this->nbC ; i++ ) {
		// On recupere le nom du sceneNode du cylindre courant
		std::ostringstream out1;
		out1 << "NodePiston" << this->num << "Cylindre" << i;
		// On calcule la rotation a appliquer au cylindre pour qu'il soit oriente correctement
		Ogre::Quaternion rot;
		rot = this->scene->getSceneNode(out1.str())->getOrientation();
		rot = rot.zAxis().getRotationTo(v);
		// On applique la rotation au cylindre
		this->scene->getSceneNode(out1.str())->rotate(rot,Ogre::Node::TS_WORLD);

		// Calcul de la distance entre le cylindre et ne nœud d'origine
		Ogre::Real distance;
		if ( i== 0 ) {
			distance = this->lC/2+NODE_RADIUS;
		} else {
			std::ostringstream out2;
			out2 << "NodePiston" << this->num << "Cylindre" << i-1;
			distance = distance+lP2/(this->nbC-1);
		}

		/* On place le piston a la distance voulue de b1, dans la sens et la direction
		 * du vecteur allant de b1 a b2
		 */
		v.normalise();
		this->scene->getSceneNode(out1.str())->setPosition(b1->getPosition()+distance*v);

		scene->getSceneNode(out1.str())->setVisible(true,true);
	}
}
