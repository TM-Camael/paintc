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

void afficher_cercle(int x1, int y1, int rayon, double r, double g, double b);        

void afficher_cercle_plein(int x1, int y1, int rayon, double r, double g, double b);

void afficher_rectangle(int x1, int x2, int y1, int y2, double r, double g, double b);

void afficher_rectangle_plein(int x1, int x2, int y1, int y2, double r, double g, double b);

void afficher_droite(double coef, int ordO, double r, double g, double b);


void afficherListe();
void inserer(int type, int x_origine, int y_origine, double composant1, double composant2, double r, double g, double b, int plein);
void supprimerLien();
void supprimerFigure();
void restaurer();

#endif
