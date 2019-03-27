#include <math.h>
#include "figure.h"

void setColor(int r, int g, int b) {
	red = r;
	green = g;
	blue = b;
}

void afficher_texte(int x_centre, int y_centre, char *string, double r, double v, double b){
	glColor4f(r,v,b,1.0);
	texte(x_centre, y_centre, string);
}

void afficher_point(int x_centre, int y_centre, double r, double v, double b)
{
	/* r, v et b sont trois reels entre 0 et 1 correspondant aux trois composantes rouge, vert et bleu de la couleur*/
	glColor4f(r,v,b,1.0);
	glBegin(GL_POINTS);
	glVertex2i(x_centre,y_centre);
	glEnd();
}

void afficher_cercle(int x1, int y1, int r)
{
	int x = 0;
	int m;
	int y=r;

	m= 5 - 4*y;

	while(x<=y)
	{
	afficher_point((x+x1), (TAILLE_Y-(y+y1)), red, green, blue);
	afficher_point((y+x1), (TAILLE_Y-(x+y1)), red, green, blue);
	afficher_point((-x+x1), (TAILLE_Y-(y+y1)), red, green, blue);
	afficher_point((-y+x1), (TAILLE_Y-(x+y1)), red, green, blue);
	afficher_point((x+x1), (TAILLE_Y-(-y+y1)), red, green, blue);
	afficher_point((y+x1), (TAILLE_Y-(-x+y1)), red, green, blue);
	afficher_point((-x+x1), (TAILLE_Y-(-y+y1)), red, green, blue);
	afficher_point((-y+x1), (TAILLE_Y-(-x+y1)), red, green, blue);
	if(m>0) 
	{
		y--;
		m-=8*y;
	}
	x++;
	m+=8*x+4;
	}
}

void afficher_cercle_plein(int x1, int y1, int r)
{
	int x, y;
	
	for(y=-r; y<=r; y++)
	{
		for(x=-r; x<=r; x++) {
			if(x*x+y*y <= r*r)
			{
				afficher_point(x1+x, (TAILLE_Y-y1+y), red, green, blue);
			}
		}
	}
}
		
void afficher_rectangle(int x1, int x2, int y1, int y2)
{
	int longueur;
	int largeur;
	int i;

	longueur = abs(x2-x1);
	largeur = abs(y2-y1);

	for(i=0; i<=longueur; i++)
	{
		afficher_point(x1+i, (TAILLE_Y-y1), red, green, blue);
		afficher_point(x1+i, (TAILLE_Y-(y1+largeur)), red, green, blue);
	}

	for(i=0; i<=largeur; i++)
	{
		afficher_point(x1, (TAILLE_Y-(y1+i)), red, green, blue);
		afficher_point(x1+longueur, (TAILLE_Y-(y1+i)), red, green, blue);
	}
}

void afficher_rectangle_plein(int x1, int x2, int y1, int y2) {
	int longueur;
	int largeur;
	int i, j;

	longueur = abs(x2-x1);
	largeur = abs(y2-y1);

	for(j=0; j<=largeur; j++){
		for(i=0; i<=longueur; i++)
		{
			afficher_point((x1+i), (TAILLE_Y-(y1+j)), red, green, blue);
		}
	}
}

int afficher_droite(int x1, int x2, int y1, int y2) {

	double temp = (TAILLE_Y-y1-y2)/(x2-x1);
	int a = (int)temp;
	int b = y1-a*x1;
	
	x1=0;
	y1=b;
	x2=TAILLE_X+1;
	y2=x2*temp+b;

	int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
	int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
 
	for(;;){
		afficher_point(x1, y1, red, green, blue);
		if (x1==x2 && y1==y2) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x1 += sx; }
		if (e2 < dy) { err += dx; y1 += sy; }
	}
	return a;
}

/****************************************************************************************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/

/* Liste chaînéee */ 
struct noeudListe {
	int type; /* Compris entre 1 et 4, respectivement Point, Droite, Carré, Cercle */
	int x_origine; 
	int y_origine;
	int composant1; /* Fait référence au coefficiant directeur d'une droite, ou de la longueur d'un rectangle, ou du rayon d'un cercle */
	int composant2; /* Fait référence à l'ordonnée à l'origine d'une droite, ou de la largeur d'un rectangle */
	int plein;
	struct noeudListe *suivant;
};

struct noeudListe *tete = NULL;

struct noeudListe* deleteFirst() {

	struct noeudListe *tempLien = tete;

	tete = tete->suivant;

	return tempLien;
}

struct noeudListeBackup {
	int type;
	int x_origine;
	int y_origine;
	int composant1;
	int composant2; 
	int plein;
	struct noeudListeBackup *suivant;
};

struct noeudListeBackup *teteBackup = NULL;

struct noeudListeBackup* deleteFirstBackup() {

	struct noeudListeBackup *tempLien = teteBackup;
	
	teteBackup = teteBackup->suivant;
	
	return tempLien;
}

void afficherListe() {
	struct noeudListe *ptr = tete;
	
	while(ptr != NULL) {
		switch (ptr->type)
		{
			case 0:
				printf("Point -\n(%d,%d)\n\n",ptr->x_origine,ptr->y_origine);
				break;
		
			case 1:
				printf("Droite :\ncoeffDirec : %d\nordOrigine : %d\n\n",ptr->composant1,ptr->composant2);
				break;
			
			case 2: 
				printf("Rectangle -\nOrigine : (%d,%d)\nLongueur : %d\nLargeur : %d\nPlein : %d\n\n",ptr->x_origine,ptr->y_origine,ptr->composant1,ptr->composant2,ptr->plein);
				break;
			
			case 3: 
				printf("Cercle -\nCentre : (%d,%d)\nRayon : %d\nPlein : %d\n\n",ptr->x_origine,ptr->y_origine,ptr->composant1,ptr->plein);
				break;

			default:
				break;
		}
		ptr=ptr->suivant;
	}
}


void inserer(int type, int x_origine, int y_origine, int composant1, int composant2, int plein) {

	struct noeudListe *lien = (struct noeudListe*) malloc(sizeof(struct noeudListe));
	
	lien->type = type;
	lien->x_origine = x_origine;
	lien->y_origine = y_origine;
	lien->composant1 = composant1;
	lien->composant2 = composant2;
	lien->plein = plein;
	lien->suivant = tete;
	tete = lien;
}

void supprimerLien() {

	struct noeudListe *lienTemp = deleteFirst();
	struct noeudListeBackup *lien = (struct noeudListeBackup*) malloc(sizeof(struct noeudListeBackup));
	
	lien->type = lienTemp->type;
	lien->x_origine = lienTemp->x_origine;
	lien->y_origine = lienTemp->y_origine;
	lien->composant1 = lienTemp->composant1;
	lien->composant2 = lienTemp->composant2;
	lien->plein = lienTemp->plein;
	lien->suivant = teteBackup;
	teteBackup = lien;
}

void supprimerFigure() {
	effacer();
	struct noeudListe *ptrSF = tete;
	while(ptrSF != NULL) 
	{
				if(ptrSF->type == 2 && ptrSF->plein == 0){
				afficher_rectangle((ptrSF->x_origine),(ptrSF->x_origine+ptrSF->composant1),(ptrSF->y_origine),(ptrSF->y_origine+ptrSF->composant2));
				}

				if(ptrSF->type == 2 && ptrSF->plein == 1){
				afficher_rectangle_plein((ptrSF->x_origine),(ptrSF->x_origine+ptrSF->composant1),(ptrSF->y_origine),(ptrSF->y_origine+ptrSF->composant2));
				}

				if(ptrSF->type == 3 && ptrSF->plein == 0){
				afficher_cercle((ptrSF->x_origine), (ptrSF->y_origine),(ptrSF->composant1));
				}

				if(ptrSF->type == 3 && ptrSF->plein == 1){
				afficher_cercle_plein((ptrSF->x_origine),(ptrSF->y_origine),(ptrSF->composant1));
				}
				
				ptrSF = ptrSF->suivant;
	}

}

void restaurer() {

	struct noeudListeBackup *lienTemp = deleteFirstBackup();
		if(lienTemp->type == 2 && lienTemp->plein == 0){
			afficher_rectangle((lienTemp->x_origine),(lienTemp->x_origine+lienTemp->composant1),(lienTemp->y_origine),(lienTemp->y_origine+lienTemp->composant2));
		}

		if(lienTemp->type == 2 && lienTemp->plein == 1){
			afficher_rectangle_plein((lienTemp->x_origine),(lienTemp->x_origine+lienTemp->composant1),(lienTemp->y_origine),(lienTemp->y_origine+lienTemp->composant2));
		}

		if(lienTemp->type == 3 && lienTemp->plein == 0){
			afficher_cercle((lienTemp->x_origine), (lienTemp->y_origine),(lienTemp->composant1));
		}

		if(lienTemp->type == 3 && lienTemp->plein == 1){
			afficher_cercle_plein((lienTemp->x_origine),(lienTemp->y_origine),(lienTemp->composant1));
		}
		inserer(lienTemp->type, lienTemp->x_origine, lienTemp->y_origine, lienTemp->composant1, lienTemp->composant2, lienTemp->plein);
}
