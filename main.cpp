/*
main.c
------

Par mateo21, pour Le Site du Z�r0 (www.siteduzero.com)

R�le : menu du jeu. Permet de choisir entre l'�diteur et le jeu lui-m�me.
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

	SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL); // L'ic�ne doit �tre charg�e avant SDL_SetVideoMode
	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Sokoban", NULL);

	jouer(ecran);
	SDL_Quit();
	return 0;
}
