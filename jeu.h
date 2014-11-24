/*
jeu.h
-----

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : prototypes des fonctions du jeu.
*/

#ifndef DEF_JEU
#define DEF_JEU

#include "node.h"
#include "edge.h"
#include <vector>

using namespace std;

    void jouer(SDL_Surface* ecran);
    void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
    void deplacerCaisse(int *premiereCase, int *secondeCase);
    void updateGNG(SDL_Rect *pos, vector<Node*> nodes, vector<Edge*> edges);


#endif
