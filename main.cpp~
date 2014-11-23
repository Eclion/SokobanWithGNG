/*
main.c
------

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : menu du jeu. Permet de choisir entre l'éditeur et le jeu lui-même.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constantes.h"
#include "jeu.h"


int main()
{
	SDL_Surface *ecran = NULL;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Sokoban", NULL);

	jouer(ecran);
	SDL_Quit();
	return 0;
}
