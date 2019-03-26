#ifndef FIGURE__H
#define FIGURE__H
#include <GL/glut.h>
#include "opengl.h"

#define POINT 0
#define DROITE 1
#define RECTANGLE 2
#define CERCLE 3
#define TEXTE 4

int x;
int y;

void afficher_texte(int x, int y, char *string, double r, double v, double b);

void afficher_point(int x, int y, double r, double v, double b);

int afficher_cercle(int x1, int x2, int y1, int y2);        

int afficher_cercle_plein(int x1, int x2, int y1, int y2);

void afficher_rectangle(int x1, int x2, int y1, int y2);

void afficher_rectangle_plein();

int afficher_droite(int x1, int x2, int y1, int y2);

void afficherListe();

void inserer(int indice, int x_origine, int y_origine, int composant1, int composant2, int plein);
void supprimerLien();
void supprimerFigure();
void restaurer();

#endif
