/*
constantes.h
------------

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : définit des constantes communes à tout le programme (taille de la fenêtre...)
*/

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define TAILLE_BLOC         34 // Taille d'un bloc (carré) en pixels
    #define NB_BLOCS_LARGEUR    18
    #define NB_BLOCS_HAUTEUR    18
    #define LARGEUR_FENETRE     TAILLE_BLOC * (NB_BLOCS_LARGEUR*2+1)
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
	#define MAX_AGE				75      //a def plus tard
	#define MAX_ERROR			20000	//a def plus tard
	#define ERROR_DECAY			10	    //a def plus tard


    enum {HAUT, BAS, GAUCHE, DROITE};
    enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif
