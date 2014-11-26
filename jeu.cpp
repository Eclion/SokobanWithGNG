/*
jeu.c
-----

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : fonctions du jeu.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

#include "constantes.h"
#include "jeu.h"
#include "fichiers.h"
#include "Position.h"

#include "node.h"
#include "draw.h"

#include <vector>

void jouer(SDL_Surface* ecran)
{
	vector<Position *> positionMemory;
	SDL_Surface *mario[4] = {NULL}; // 4 surfaces pour chacune des directions de mario
	SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	SDL_Rect position, positionJoueur;
	SDL_Event event;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

	vector<Node*> _nodes;
	vector<Edge*> _edges;
	int mx=0, my=0;

	// Chargement des sprites (décors, personnage...)
	mur = IMG_Load("mur.jpg");
	caisse = IMG_Load("caisse.jpg");
	caisseOK = IMG_Load("caisse_ok.jpg");
	objectif = IMG_Load("objectif.png");
	mario[BAS] = IMG_Load("mario_bas.gif");
	mario[GAUCHE] = IMG_Load("mario_gauche.gif");
	mario[HAUT] = IMG_Load("mario_haut.gif");
	mario[DROITE] = IMG_Load("mario_droite.gif");

	marioActuel = mario[BAS]; // Mario sera dirigé vers le bas au départ

	// Chargement du niveau
	if (!chargerNiveau(carte))
		exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau

	// Recherche de la position de Mario au départ
	for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
	{
		for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
		{
			if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}

	_nodes.push_back(new Node(positionJoueur.x,positionJoueur.y));
	// Activation de la répétition des touches
	SDL_EnableKeyRepeat(100, 100);

	Uint32 start;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						continuer = 0;
						break;
					case SDLK_UP:
						marioActuel = mario[HAUT];
						deplacerJoueur(carte, &positionJoueur, HAUT);
						updateGNG(&positionJoueur, _nodes, _edges);
						break;
					case SDLK_DOWN:
						marioActuel = mario[BAS];
						deplacerJoueur(carte, &positionJoueur, BAS);
						updateGNG(&positionJoueur, _nodes, _edges);
						break;
					case SDLK_RIGHT:
						marioActuel = mario[DROITE];
						deplacerJoueur(carte, &positionJoueur, DROITE);
						updateGNG(&positionJoueur, _nodes, _edges);
						break;
					case SDLK_LEFT:
						marioActuel = mario[GAUCHE];
						deplacerJoueur(carte, &positionJoueur, GAUCHE);
						updateGNG(&positionJoueur, _nodes, _edges);
						break;
					default:
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				mx=event.motion.x;
				my=event.motion.y;
				break;
			default:
				break;
		}

		// Effacement de l'écran
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

		// Placement des objets à l'écran
		objectifsRestants = 0;

		for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
		{
			for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch(carte[i][j])
				{
					case MUR:
						SDL_BlitSurface(mur, NULL, ecran, &position);
						break;
					case CAISSE:
						SDL_BlitSurface(caisse, NULL, ecran, &position);
						break;
					case CAISSE_OK:
						SDL_BlitSurface(caisseOK, NULL, ecran, &position);
						break;
					case OBJECTIF:
						SDL_BlitSurface(objectif, NULL, ecran, &position);
						objectifsRestants = 1;
						break;
					default:
						break;
				}

				if(carte[i][j]!=0){
					//placement du mur sur la partie gng
					position.x = TAILLE_BLOC*(NB_BLOCS_LARGEUR+1+i);
					SDL_BlitSurface(mur, NULL, ecran, &position);	
				}
				
			}
		}

		// Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
		if (!objectifsRestants)
			continuer = 0;

		// On place le joueur à la bonne position
		position.x = positionJoueur.x * TAILLE_BLOC;
		position.y = positionJoueur.y * TAILLE_BLOC;
		Position newPosition(positionJoueur.x,positionJoueur.y);
		positionMemory.push_back(&newPosition);
		//cout << newPosition.GetX() << ";" << newPosition.GetY() << endl;  
		SDL_BlitSurface(marioActuel, NULL, ecran, &position);

		//drawLine(ecran,mx,my,LARGEUR_FENETRE/2,HAUTEUR_FENETRE/2);
		//drawPoint(ecran,LARGEUR_FENETRE/2,HAUTEUR_FENETRE/2,10);
		float x0pt=0,x1pt=0,y0pt=0,y1pt=0;



		if(!_nodes.empty()){
			for(int i =0; i<_nodes.size();i++){
				x0pt = NB_BLOCS_LARGEUR + 1 + round(_nodes[i]->getX())+0.5;
				y0pt = round(_nodes[i]->getY())+0.5;
				drawPoint(ecran,
						x0pt*TAILLE_BLOC,
						y0pt*TAILLE_BLOC,
						9);
			}
		}
		if(!_edges.empty()){
			for(int i =0; i<_edges.size();i++){
				x0pt = NB_BLOCS_LARGEUR + 1 + round(_edges[i]->getNode(0)->getX())+0.5;
				y0pt = round(_edges[i]->getNode(0)->getY())+0.5;
				x1pt = NB_BLOCS_LARGEUR + 1 + round(_edges[i]->getNode(1)->getX())+0.5;
				y1pt = round(_edges[i]->getNode(1)->getY())+0.5;
				drawLine(ecran,
						/*(NB_BLOCS_LARGEUR + 1 + _edges[i]->getNode(0)->getX()+0.5)*TAILLE_BLOC,
						(_edges[i]->getNode(0)->getY()+0.5)*TAILLE_BLOC,
						(NB_BLOCS_LARGEUR + 1 + _edges[i]->getNode(1)->getX()+0.5)*TAILLE_BLOC,
						(_edges[i]->getNode(1)->getY()+0.5)*TAILLE_BLOC,*/
						x0pt*TAILLE_BLOC,
						y0pt*TAILLE_BLOC,
						x1pt*TAILLE_BLOC,
						y1pt*TAILLE_BLOC,
						9);
			}
		}

		SDL_Flip(ecran);

	}

	// Désactivation de la répétition des touches (remise à 0)
	SDL_EnableKeyRepeat(0, 0);

	// Libération des surfaces chargées
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(caisseOK);
	SDL_FreeSurface(objectif);
	for (i = 0 ; i < 4 ; i++)
		SDL_FreeSurface(mario[i]);
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
	switch(direction)
	{
		case HAUT:
			if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
				break;
			if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
				break;
			// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
			if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
				(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
				carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
				break;

			// Si on arrive là, c'est qu'on peut déplacer le joueur !
			// On vérifie d'abord s'il y a une caisse à déplacer
			deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

			pos->y--; // On peut enfin faire monter le joueur (oufff !)
			break;


		case BAS:
			if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
				break;
			if (carte[pos->x][pos->y + 1] == MUR)
				break;

			if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
				(pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
				carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
				break;


			deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

			pos->y++;
			break;


		case GAUCHE:
			if (pos->x - 1 < 0)
				break;
			if (carte[pos->x - 1][pos->y] == MUR)
				break;

			if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
				(pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
				carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
				break;


			deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

			pos->x--;
			break;


		case DROITE:
			if (pos->x + 1 >= NB_BLOCS_LARGEUR)
				break;
			if (carte[pos->x + 1][pos->y] == MUR)
				break;

			if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
				(pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
				carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
				break;

			deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

			pos->x++;
			break;
		default:
			break;
	}
}

void deplacerCaisse(int *premiereCase, int *secondeCase)
{
	if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
	{
		if (*secondeCase == OBJECTIF)
			*secondeCase = CAISSE_OK;
		else
			*secondeCase = CAISSE;

		if (*premiereCase == CAISSE_OK)
			*premiereCase = OBJECTIF;
		else
			*premiereCase = VIDE;
	}
}

void updateGNG(SDL_Rect *pos, vector<Node*> &nodes, vector<Edge*> &edges){
	Node* currentNode = new Node(pos->x,pos->y);
	//Node* currentNode = findNode(nodes,pos->x,pos->y);
	

	if(nodes.empty())nodes.push_back(currentNode);
	else if(nodes.size() == 1){
		nodes.push_back(currentNode);
		edges.push_back(new Edge(nodes[0],nodes[1]));
	}
	else{
		currentNode->setClosests(nodes);
		//cout<<"first->y = "<<currentNode->getClosest(0)->getY() <<endl;
		//cout<<"second->y = "<<currentNode->getClosest(1)->getY() <<endl;
		edges.push_back(new Edge(currentNode->getClosest(0),currentNode->getClosest(1)));
		currentNode->getClosest(0)->addError(currentNode->distanceWith(currentNode->getClosest(0)));
		//cout<<currentNode->getClosest(0)->getError()<<endl;
		
		//	Attract first toward (x,y)
		currentNode->getClosest(0)->moveForward(currentNode,0.03);

		for(int i = 0; i< edges.size();i++){
			edges[i]->addAge(1);
			if(edges[i]->getAge() > MAX_AGE) edges.erase(edges.begin()+i);
		}
		// Attract neighbours(first) toward (x,y)
		for(int i=0; i< currentNode->getClosest(0)->_edges.size(); i++ ){
			currentNode->getClosest(0)->getNeighbourNode(currentNode->getClosest(0)->_edges[i])->moveForward(currentNode,0.006);
		}

		for(int i =0; i< nodes.size();i++){
			nodes[i]->addError(-ERROR_DECAY);
		}

		if(currentNode->getClosest(0)->getError() > MAX_ERROR){
			Node* maxErrNei = currentNode->maxErrorNeighbour();
			Node* newN = new Node(pos->x,pos->y);//between(currentNode->getClosest(0),maxErrNei);
			currentNode->getClosest(0)->addError(-currentNode->getClosest(0)->getError()/2);
			maxErrNei->addError(-maxErrNei->getError()/2);
			float newError = currentNode->getClosest(0)->getError()+maxErrNei->getError();
			newN->addError(newError);
			//currentNode->addError(newError);
			//nodes.push_back(currentNode);
			nodes.push_back(newN);
			/**/
		}
	}
}