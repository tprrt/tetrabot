#include "Graphe.h"


// Methode permettant d'ajouter un sommet
template<class S,class A>
void Graphe<S,A>::addSommet(S newSommet)
{
	graph.insert(newSommet,btAlignedObjectArray<A>());

}

// Methode permettant de lier un Arc a un Sommet
template<class S, class A>
void Graphe<S,A>::ajouterArc(S sommet, A newArc)
{
	btAlignedObjectArray<A> tabArcs = graph.find(sommet);
	tabArcs.expand(newArc);
}