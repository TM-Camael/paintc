#ifndef A_MODIFIER__H
#define A_MODIFIER__H

#include <GL/glut.h>

int x;
int y;
int x1 ; // Principalement pour les derniers clics
int y1 ; // Principalement pour les derniers clics
int x2; // Principalement pour l'avant dernier clic
int y2; // Principalement pour l'avant dernier clic
int temp;

// Vous pouvez modifier ce fichier si vous voulez mais ce n'est pas forcément nécessaire

void initialisation_fenetre();
void initialisation_IG();
void affichage();
void clic_gauche(int x, int y);
void clic_droit(int x, int y);
void clavier(unsigned char key, int x, int y);
#endif																																																											
