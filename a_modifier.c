#include "opengl.h"
#include "figure.h"
#include "a_modifier.h"

char choix=-1;

// Procédure appelée lors de la création de la fenêtre
// que vous pouvez réappeler de nouveau pour réinitilisation.
// Utile si vous voulez créer un menu ou une interface graphique...

void initialisation_fenetre(){
	effacer();
	for(int i=100;i<500;i++)
		afficher_point(i,i,0,0,0);
	
	afficher_texte(420,350,"ceci n'est pas une ligne",0,0,0);
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

	if(choix=='1')
	{
		temp = afficher_droite(x2, x1, y2, y1);
		inserer(DROITE, x2, y2, temp, (y2-temp*x2), 0);
		choix=-1;
	}
	if(choix=='2')
	{
		temp=afficher_cercle(x2, x1, y2, y1);
		inserer(CERCLE, x2, y2, temp, 0, 0);
		choix=-1;
	}

	if(choix=='3')
	{
		temp = afficher_cercle_plein(x2,x1,y2,y1);
		inserer(CERCLE, x2, y2, temp, 0, 1);
		choix =-1;
	}

	if(choix=='4')
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
		afficher_rectangle(x1, x2, y1, y2);
		inserer(RECTANGLE, x1, y1, abs(x1-x2), abs(y2-y1), 0);
		choix=-1;
	}

	if(choix=='5')
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
		afficher_rectangle_plein(x1, x2, y1, y2);
		inserer(RECTANGLE, x1, y1, abs(x1-x2), abs(y2-y1), 1);
		choix=-1;
	}

	if(choix=='6'){
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
		choix=-1;
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

