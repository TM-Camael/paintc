#ifndef FIGURE__H
#define FIGURE__H
#include <GL/glut.h>
#include "opengl.h"

#define POINT 0
#define LIGNE 1
#define RECTANGLE 2
#define CERCLE 3
#define TEXTE 4

// Mettre en place ici la SD pour les figures
// Mettre en place ici la SD pour la (les) liste(s) chainée(s)

int x;
int y;

void afficher_texte(int x, int y, char *string, double r, double v, double b);

void afficher_point(int x, int y, double r, double v, double b);

void afficher_cercle();

void afficher_cercle_plein();

void afficher_rectangle(int x1, int x2, int y1, int y2);

void afficher_rectangle_plein();

void afficher_droite();

void afficherListe();

void inserer(int indice, int x_origine, int y_origine, int composant1, int composant2, int plein);

void supprimer();

void restaurer();

#endif
