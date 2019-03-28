#include "figure.h"

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

/*Gestion du cercle */
void afficher_cercle(int x1, int y1, int rayon, double r, double g, double b, int init)
{
	int x = 0;
	int m;
	int y=rayon;

	m= 5 - 4*y;

	while(x<=y)
	{
	if(init == 1 || (TAILLE_Y-(y+y1) < 500)){
	afficher_point((x+x1), (TAILLE_Y-(y+y1)), r, g , b);}

	if(init == 1 || (TAILLE_Y-(x+y1)) < 500){
	afficher_point((y+x1), (TAILLE_Y-(x+y1)), r, g , b);}

	if(init == 1 || (TAILLE_Y-(y+y1) < 500)){
	afficher_point((-x+x1), (TAILLE_Y-(y+y1)), r, g , b);}
	
	if(init == 1 || (TAILLE_Y-(x+y1) < 500)){
	afficher_point((-y+x1), (TAILLE_Y-(x+y1)), r, g , b);}
	
	if(init == 1 || (TAILLE_Y-(-y+y1) < 500)){
	afficher_point((x+x1), (TAILLE_Y-(-y+y1)), r, g , b);}
	
	if(init == 1 || (TAILLE_Y-(-x+y1) < 500)){
	afficher_point((y+x1), (TAILLE_Y-(-x+y1)), r, g , b);}
	
	if(init == 1 || (TAILLE_Y-(-y+y1) < 500)){
	afficher_point((-x+x1), (TAILLE_Y-(-y+y1)), r, g , b);}
	
	if(init == 1 || (TAILLE_Y-(-x+y1) < 500)){
	afficher_point((-y+x1), (TAILLE_Y-(-x+y1)), r, g , b);}
	
	if(m>0)
	{
		y--;
		m-=8*y;
	}
	x++;
	m+=8*x+4;
	}
}

void afficher_cercle_plein(int x1, int y1, int rayon, double r, double g, double b, int init)
{
	int x, y;

	for(y=-rayon; y<=rayon; y++)
	{
		for(x=-rayon; x<=rayon; x++) {
			if(x*x+y*y <= rayon*rayon)
			{
				if((TAILLE_Y-y1+y)>500 && init == 0){
					break;
				}
				afficher_point(x1+x, (TAILLE_Y-y1+y), r, g, b);
				
			}
		}
	}
}

/* Gestion du rectangle */
void afficher_rectangle(int x1, int x2, int y1, int y2, double r, double g, double b, int init)
{
	int longueur;
	int largeur;
	int i;

	longueur = abs(x2-x1);
	largeur = abs(y2-y1);

	for(i=0; i<=longueur; i++)
	{
		if(init==1 || (TAILLE_Y-y1) < 500){
		afficher_point(x1+i, (TAILLE_Y-y1), r, g, b);
		}
		if(init==1 || (TAILLE_Y-(y1+largeur))<500){
		afficher_point(x1+i, (TAILLE_Y-(y1+largeur)), r, g, b);
		}
	}

	for(i=0; i<=largeur; i++)
	{
		if(init==1 || (TAILLE_Y-(y1+i))<500){
		afficher_point(x1, (TAILLE_Y-(y1+i)), r, g, b);
		afficher_point(x1+longueur, (TAILLE_Y-(y1+i)), r, g, b);
		}
	}
		
}


void afficher_rectangle_plein(int x1, int x2, int y1, int y2, double r, double g, double b, int init) {
	int longueur;
	int largeur;
	int i, j;

	longueur = abs(x2-x1);
	largeur = abs(y2-y1);

	for(j=0; j<=largeur; j++){
		for(i=0; i<=longueur; i++)
		{
			if(init == 0 && (TAILLE_Y-y1-j)>500){
				break;
			}
			afficher_point((x1+i), (TAILLE_Y-(y1+j)), r, g, b);
		}
	}
}

/* Gestion de la droite */
void afficher_droite(double coef, int ordO, double r, double g, double b) {

	int x1, x2, y1, y2;

	x1=0;
	y1=ordO;
	x2=TAILLE_X;
	y2=TAILLE_X*coef+ordO;

	int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
	int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
	if(y1<500){
		afficher_point(x1, y1, r, g, b);
	}
		if ((x1==x2 && y1==y2)) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x1 += sx; }
		if (e2 < dy) { err += dx; y1 += sy; }
	}
}


/****************************************************************************************************************************/
/****************************************************************************************************************************/
/****************************************************************************************************************************/

/* Liste chaînéee */
struct noeudListe {
	int type; /* Compris entre 1 et 4, respectivement Point, Droite, Carré, Cercle */
	int x_origine;
	int y_origine;
	double composant1; /* Fait référence au coefficiant directeur d'une droite, ou de la longueur d'un rectangle, ou du rayon d'un cercle */
	double composant2; /* Fait référence à l'ordonnée à l'origine d'une droite, ou de la largeur d'un rectangle */
	double couleurRouge;
	double couleurVerte;
	double couleurBleu;
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
	double composant1;
	double composant2;
	double couleurRouge;
	double couleurVerte;
	double couleurBleu;
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
				printf("Droite :\ncoeffDirec : %f\nordOrigine : %f\n\n",ptr->composant1,ptr->composant2);
				break;

			case 2:
				printf("Rectangle -\nOrigine : (%d,%d)\nLongueur : %f\nLargeur : %f\nPlein : %d\n\n",ptr->x_origine,ptr->y_origine,ptr->composant1,ptr->composant2,ptr->plein);
				break;

			case 3:
				printf("Cercle -\nCentre : (%d,%d)\nRayon : %f\nPlein : %d\n\n",ptr->x_origine,ptr->y_origine,ptr->composant1,ptr->plein);
				break;

			default:
				break;
		}
		ptr=ptr->suivant;
	}
}


void inserer(int type, int x_origine, int y_origine, double composant1, double composant2, double r, double g, double b, int plein) {

	struct noeudListe *lien = (struct noeudListe*) malloc(sizeof(struct noeudListe));

	lien->type = type;
	lien->x_origine = x_origine;
	lien->y_origine = y_origine;
	lien->composant1 = composant1;
	lien->composant2 = composant2;
	lien->couleurRouge = r;
	lien->couleurVerte = g;
	lien->couleurBleu = b;
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
	lien->couleurRouge = lienTemp->couleurRouge;
	lien->couleurVerte = lienTemp->couleurVerte;
	lien->couleurBleu = lienTemp->couleurBleu;
	lien->plein = lienTemp->plein;
	lien->suivant = teteBackup;
	teteBackup = lien;
}

void supprimerFigure() {
	effacer();
	struct noeudListe *ptrSF = tete;
	while(ptrSF != NULL)
	{

				if(ptrSF->type == POINT){
				afficher_point(ptrSF->x_origine, ptrSF->y_origine, ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu);
				}
				if(ptrSF->type == DROITE){
				afficher_droite(ptrSF->composant1, ptrSF->composant2, ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu);
				}
				if(ptrSF->type == 2 && ptrSF->plein == 0){
				afficher_rectangle((ptrSF->x_origine),(ptrSF->x_origine+ptrSF->composant1),(ptrSF->y_origine),(ptrSF->y_origine+ptrSF->composant2), ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu, 0);
				}

				if(ptrSF->type == 2 && ptrSF->plein == 1){
				afficher_rectangle_plein((ptrSF->x_origine),(ptrSF->x_origine+ptrSF->composant1),(ptrSF->y_origine),(ptrSF->y_origine+ptrSF->composant2), ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu, 0);
				}

				if(ptrSF->type == 3 && ptrSF->plein == 0){
				afficher_cercle((ptrSF->x_origine), (ptrSF->y_origine),(ptrSF->composant1), ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu, 0);
				}

				if(ptrSF->type == 3 && ptrSF->plein == 1){
				afficher_cercle_plein((ptrSF->x_origine),(ptrSF->y_origine),(ptrSF->composant1), ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu, 0);
				}

				ptrSF = ptrSF->suivant;
	}

}

void restaurer() {

	struct noeudListeBackup *lienTemp = deleteFirstBackup();

		if(lienTemp->type == POINT){
			afficher_point(lienTemp->x_origine, lienTemp->y_origine, lienTemp->couleurRouge, lienTemp->couleurVerte, lienTemp->couleurBleu);
		}
		if(lienTemp->type == DROITE){
			afficher_droite(lienTemp->composant1, lienTemp->composant2, lienTemp->couleurRouge, lienTemp->couleurVerte, lienTemp->couleurBleu);
		}
		if(lienTemp->type == 2 && lienTemp->plein == 0){
			afficher_rectangle((lienTemp->x_origine),(lienTemp->x_origine+lienTemp->composant1),(lienTemp->y_origine),(lienTemp->y_origine+lienTemp->composant2), lienTemp->couleurRouge, lienTemp->couleurVerte, lienTemp->couleurBleu, 0);
		}

		if(lienTemp->type == 2 && lienTemp->plein == 1){
			afficher_rectangle_plein((lienTemp->x_origine),(lienTemp->x_origine+lienTemp->composant1),(lienTemp->y_origine),(lienTemp->y_origine+lienTemp->composant2), lienTemp->couleurRouge, lienTemp->couleurVerte, lienTemp->couleurBleu, 0);
		}

		if(lienTemp->type == 3 && lienTemp->plein == 0){
			afficher_cercle((lienTemp->x_origine), (lienTemp->y_origine),(lienTemp->composant1), lienTemp->couleurRouge, lienTemp->couleurVerte, lienTemp->couleurBleu, 0);
		}

		if(lienTemp->type == 3 && lienTemp->plein == 1){
			afficher_cercle_plein((lienTemp->x_origine),(lienTemp->y_origine),(lienTemp->composant1), lienTemp->couleurRouge, lienTemp->couleurVerte, lienTemp->couleurBleu, 0);
		}
		inserer(lienTemp->type, lienTemp->x_origine, lienTemp->y_origine, lienTemp->composant1, lienTemp->composant2, lienTemp->couleurRouge, lienTemp->couleurVerte, lienTemp->couleurBleu, lienTemp->plein);
}

void sauvegarder_fichier() {
	int compteurFigure = 0;
	struct noeudListe *ptr = tete;
	while(ptr != NULL){
		compteurFigure++;
		ptr=ptr->suivant;
	}

	ptr = tete;

	FILE *fichier;
	fichier = NULL;
	fichier = fopen("test.txt", "w");

    if (fichier == NULL)
    {
        exit(1);
    }

	else {
		fprintf(fichier, "%d\n", compteurFigure);
		while(ptr != NULL){
			fprintf(fichier, "%d %d %d %f %f %f %f %f %d\n", ptr->type, ptr->x_origine, ptr->y_origine, ptr->composant1, ptr->composant2, ptr->couleurRouge, ptr->couleurVerte, ptr->couleurBleu, ptr->plein);
			ptr=ptr->suivant;
		}
	}
	fclose(fichier);
}

void ouvrir_fichier() {
	int compteur;
	int i;
	int a, b, c, p;
	double d, e, f, g, h; 

	FILE *fichier;
	fichier = NULL;
	fichier = fopen("test.txt", "r");
	if(fichier == NULL)
    {
        exit(1);
    }

	fscanf(fichier, "%d", &compteur);
	for(i=0; i<compteur; i++){
		fscanf(fichier, "%d %d %d %lf %lf %lf %lf %lf %d", &a, &b, &c, &d, &e, &f, &g, &h, &p);
		inserer(a, b, c, d, e, f, g, h, p);
	}

	fclose(fichier);

	struct noeudListe *ptrSF = tete;
	while(ptrSF != NULL)
	{
		if(ptrSF->type == POINT){
			afficher_point(ptrSF->x_origine, ptrSF->y_origine, ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu);
		}
		if(ptrSF->type == DROITE){
			afficher_droite(ptrSF->composant1, ptrSF->composant2, ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu);
		}
		if(ptrSF->type == 2 && ptrSF->plein == 0){
			afficher_rectangle((ptrSF->x_origine),(ptrSF->x_origine+ptrSF->composant1),(ptrSF->y_origine),(ptrSF->y_origine+ptrSF->composant2), ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu, 0);
		}

		if(ptrSF->type == 2 && ptrSF->plein == 1){
			afficher_rectangle_plein((ptrSF->x_origine),(ptrSF->x_origine+ptrSF->composant1),(ptrSF->y_origine),(ptrSF->y_origine+ptrSF->composant2), ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu, 0);
		}

		if(ptrSF->type == 3 && ptrSF->plein == 0){
			afficher_cercle((ptrSF->x_origine), (ptrSF->y_origine),(ptrSF->composant1), ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu, 0);
		}

		if(ptrSF->type == 3 && ptrSF->plein == 1){
			afficher_cercle_plein((ptrSF->x_origine),(ptrSF->y_origine),(ptrSF->composant1), ptrSF->couleurRouge, ptrSF->couleurVerte, ptrSF->couleurBleu, 0);
		}

		ptrSF = ptrSF->suivant;
	}
}