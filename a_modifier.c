#include "opengl.h"
#include "figure.h"
#include "a_modifier.h"
#include <math.h>

int choix=-1;
int compteurClic = 0;
double test;
double dx;

// Procédure appelée lors de la création de la fenêtre
// que vous pouvez réappeler de nouveau pour réinitilisation.
// Utile si vous voulez créer un menu ou une interface graphique...

void initialisation_fenetre(){
	effacer();
	initialisation_IG();
	
}

void initialisation_IG(){
	for(temp=0; temp<TAILLE_X;temp++){
		afficher_point(temp, 500, 0, 0, 0);
	}
	afficher_rectangle(50, 75, 10, 60, 0, 0, 0);
	afficher_rectangle(100, 125, 10, 60, 0, 0, 0);
	afficher_rectangle_plein(130, 155, 10, 60, 0, 0, 0);
	afficher_cercle(185, 35, 25, 0, 0, 0);
	afficher_cercle_plein(240, 35, 25, 0, 0, 0);
	afficher_rectangle_plein(500, 525, 50, 75, 1, 0, 0);
	afficher_rectangle_plein(530, 555, 50, 75, 0, 1, 0);
	afficher_rectangle_plein(560, 585, 50, 75, 0, 0, 1);
}

void setColor(double r, double g, double b) {
	red = r;
	green = g;
	blue = b;
}
 
// Cette procédure est appelée lorsqu'aucun
// événement clavier/souris n'est détecté
// donc quasiment en continu.
// C'est cette procédure qui doit gèrer l'affichage.

void affichage()
{
	// L'affichage ne peut se faire que ici !
	// Utilisez des variables globales si vous avez besoin de faire communiquer
	// cette procédure et les autres.

	// On affiche 4 points à chaque fois pour que ce soit plus
	// visible qu'un seul pixel - juste plus de confort
	// pour ce programme de test.

	if(choix==1 && compteurClic==2)
	{
		dx = x1-x2;
		test = ((TAILLE_Y-y1)-(TAILLE_Y-y2))/dx;
		printf("Coef dir : %lf", test);
		afficher_droite(test, (TAILLE_Y-y2-test*x2), red, green, blue);
		inserer(DROITE, 0, 0, test, (TAILLE_Y-y2-test*x2), red, green, blue, 0);
		choix=-1;
	}

	if(choix==2 && compteurClic == 2)
	{
		temp = sqrt((x2-x1)*(x2-x1)+(y1-y2)*(y1-y2));
		afficher_cercle(x2, y2, temp, red, green, blue);
		inserer(CERCLE, x2, y2, temp, 0, red, green, blue, 0);
		choix=-1;
	}

	if(choix==3 && compteurClic == 2) 
	{
		temp = sqrt((x2-x1)*(x2-x1)+(y1-y2)*(y1-y2));
		afficher_cercle_plein(x2,y2, temp, red, green, blue);
		inserer(CERCLE, x2, y2, temp, 0, red, green, blue, 1);
		choix =-1;
		compteurClic = 0;
	}

	if(choix==4 && compteurClic == 2)
	{
		if(x2<x1)
		{
			temp = x2;
			x2 = x1;
			x1 = temp;
		}

		if(y2<y1)
		{
			temp = y2;
			y2 = y1;
			y1 = temp;
		}
		afficher_rectangle(x1, x2, y1, y2, red, green, blue);
		inserer(RECTANGLE, x1, y1, abs(x1-x2), abs(y2-y1), red, green, blue, 0);
		choix=-1;
	}

	if(choix==5 && compteurClic == 2)
	{
		if(x2<x1)
		{
		temp = x2;
		x2 = x1;
		x1 = temp;
	}

	if(y2<y1){
		temp = y2;
		y2 = y1;
		y1 = temp;
	}
		afficher_rectangle_plein(x1, x2, y1, y2, red, green, blue);
		inserer(RECTANGLE, x1, y1, abs(x1-x2), abs(y2-y1), red, green, blue, 1);
		compteurClic = 0;
		choix=-1;
	}

	if(choix==6){
		printf("Entrez la coordonnées X du point à afficher :\n");
		scanf(" %d",&x);
		printf("Entrez la coordonnées Y du point à afficher :\n");
		scanf(" %d",&y);
		afficher_point(x,y,0,0,0);
		choix=-1;
	}

	if(choix=='7'){
		initialisation_fenetre();
		choix=-1;
	}

	if(choix=='8'){
		effacer();
		choix=-1;
	}

	if(choix=='a')
	{
		afficherListe();
		choix=-1;
	}
 
	if(choix=='z')
	{
	 	supprimerLien();
		supprimerFigure();
		initialisation_IG();
		choix=-1;
	}

	if(choix=='y')
	{
		restaurer();
		choix=-1;
	}

	if((x1>50 && x1 < 75) && (y1>10 && y1<60)){
		compteurClic = 0;
		choix = 1;
	}

	if((x1>100 && x1 < 125) && (y1>10 && y1<60)){
		compteurClic = 0;
		choix = 4;
	}

	if((x1>130 && x1 < 155) && (y1>10 && y1<60)){
		compteurClic = 0;
		choix = 5;
	}

	if((x1>160 && x1 < 210) && (y1>10 && y1<60)){
		compteurClic = 0;
		choix = 2;
	}

	if((x1>215 && x1 < 265) && (y1>10 && y1<60)){
		compteurClic = 0;
		choix = 3;
	}

	if((x1>500 && x1<525) && (y1>50 && y1<75)){
		setColor(1, 0, 0);
	}

	if((x1>530 && x1<555) && (y1>50 && y1<75)){
		setColor(0, 1, 0);
	}

	if((x1>560 && x1<585) && (y1>50 && y1<75)){
		setColor(0, 0, 1);
	}
}

void clic_gauche(int x, int y){
	// Code exécuté lors d'un clic gauche
	// Attention ! Pas de dessin dans cette fonction/procédure.
	// Utilisez des variables globales si vous avez besoin de faire communiquer
	// cette procédure et celles du dessous.
	x2=x1;
	y2=y1;
	x1=x;
	y1=y;
	compteurClic++;
	printf("Clic gauche en %d %d\n",x,y);
}


void clic_droit(int x, int y){
	// Code exécuté lors d'un clic droit
	// Attention ! Pas de dessin dans cette fonction/procédure
	// Utilisez des variables globales si vous avez besoin de faire communiquer
	// cette procédure et celles du dessous.
	printf("Clic droit en %d %d\n",x,y);
}

void clavier(unsigned char key, int x, int y){
	// Code exécuté lors d'un 
	// Attention ! Pas de dessin dans cette fonction/procédure
	// Utilisez des variables globales si vous avez besoin de faire communiquer
	// cette procédure et celles du dessous.
	
	printf("Appui sur la touche %c du clavier lorsque la souris est en %d %d\n",key,x,y);

	// Si la touche appuyée est un chiffre entre 1 et 6,
	// la case correspondante dans le tableau choix est mise à vrai.
	// Si une autre touche est appuyée, le programme se ferme.
	choix=key;
	if(key=='9')
	exit(0);
}

