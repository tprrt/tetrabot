#ifndef GRAPHE_H
#define GRAPHE_H

#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btHashMap.h"
template<class S,class A>
class Graphe
{
protected:
	// Une HashMap ayant pour cle un pointeur de classe de Sommets.
	// Chaque sommet est mis en relation avec un tableau de pointeurs d'Arcs
	btHashMap<btHashKeyPtr<S>,btAlignedObjectArray<A>> graph;
/*public:
	// Le Constructeur
	Graphe();
	// Le Destructeur
	~Graphe();
	*/
public:
	// Les Methodes
	// Methode permettant d'ajouter un sommet
	void addSommet(S newSommet)
	{
		graph.insert(newSommet,btAlignedObjectArray<A>());

	}
	// Methode permettant de lier un Arc a un Sommet
	void ajouterArc(S sommet,A newArc)
	{
		btAlignedObjectArray<A> *tabArcs = graph.find(sommet);
		tabArcs->expand(newArc);
	}

};
#endif