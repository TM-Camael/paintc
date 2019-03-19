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

void afficher_cercle()
{
  int x_centre, y_centre;
  int m; 

  printf("Donnez les coordonnées du centre :\n");
  scanf(" %d %d", &x_centre, &y_centre);
  printf("Donnez le rayon :\n");
  scanf(" %d", &y); 
  m= 5 - 4*y;

  while(x<=y)
  {
	afficher_point((x+x_centre), (y+y_centre), 0, 0, 0);
	afficher_point((y+x_centre), (x+y_centre), 0, 0, 0);
	afficher_point((-x+x_centre), (y+y_centre), 0, 0, 0);
	afficher_point((-y+x_centre), (x+y_centre), 0, 0, 0);
	afficher_point((x+x_centre), (-y+y_centre), 0, 0, 0);
	afficher_point((y+x_centre), (-x+y_centre), 0, 0, 0);
	afficher_point((-x+x_centre), (-y+y_centre), 0, 0, 0);
	afficher_point((-y+x_centre), (-x+y_centre), 0, 0, 0);
	if(m>0) 
	{
		y--;
		m-=8*y;
	}
	x++;
	m+=8*x+4;
  }
}

void afficher_cercle_plein()
{
  int x_centre, y_centre;
  int x, y, r;


  printf("Donnez les coordonnées du centre :\n");
  scanf(" %d %d", &x_centre, &y_centre);
  printf("Donnez le rayon :\n");
  scanf(" %d", &r); 
	
	for(y=-r; y<=r; y++)
	{
	    for(x=-r; x<=r; x++)
	    {
		if(x*x+y*y <= r*r)
		{
		    afficher_point(x_centre+x, y_centre+y, 0, 0, 0);
		}
	    }
        }
}
		

void afficher_rectangle(int x1, int x2, int y1, int y2)
{
  int longueur;
  int largeur;
  int i;

  longueur = x2-x1;
  largeur = y1-y2;

  for(i=0; i<=longueur; i++)
  {
    afficher_point((x1+i), y1, 0, 0, 0);
    afficher_point((x1+i), y2, 0, 0, 0);
  }

  for(i=0; i<=largeur; i++)
  {
    afficher_point((x1), (y2+i), 0, 0, 0);
    afficher_point((x2), (y2+i), 0, 0, 0);
  }
}

void afficher_rectangle_plein() {

  int x_centre, y_centre, x, y;
  int longueur;
  int largeur;
  int i,j;

  printf("Donnez les coordonnées du centre :\n");
  scanf(" %d %d", &x_centre, &y_centre);
  printf("Donnez la longueur :\n");
  scanf(" %d", &longueur); 
  printf("Donnez la largeur :\n");
  scanf(" %d", &largeur); 

  for(j=0; j<=largeur; j++){
	  for(i=0; i<=longueur; i++)
	  {
	    afficher_point((x_centre+i), y_centre+j, 0, 0, 0);
	  }
  }
}


void afficher_droite() {
 
  int x1, x2, y1, y2, a, b;

  printf("Donnez le coefficient directeur :\n");
  scanf(" %d", &a);
  printf("Donnez l'ordonnée à l'origine :\n");
  scanf(" %d", &b);
  
  x1=0;
  y1=b;
  x2=1000;
  y2=1000*a+b;

  int dx = abs(x2-x1), sx = x1<x2 ? 1 : -1;
  int dy = abs(y2-y1), sy = y1<y2 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    afficher_point(x1, y1, 0, 0, 0);
    if (x1==x2 && y1==y2) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x1 += sx; }
    if (e2 < dy) { err += dx; y1 += sy; }
  }
}

struct nodeListe {
   int indice;
   int x_origine;
   int y_origine;
   int composant1;
   int composant2; 
   int plein;
   struct nodeListe *next;
};

struct nodeListe *head = NULL;

struct nodeListe* deleteFirst() {

   struct nodeListe *tempLink = head;

   head = head->next;

   return tempLink;
}

struct nodeListeBackup {
   int indice;
   int x_origine;
   int y_origine;
   int composant1;
   int composant2; 
   int plein;
   struct nodeListeBackup *next;
};

struct nodeListeBackup *headBackup = NULL;

struct nodeListeBackup* deleteFirstBackup() {

   struct nodeListeBackup *tempLink = headBackup;
	
   headBackup = headBackup->next;
	
   return tempLink;
}



void afficherListe() {
   struct nodeListe *ptr = head;
   printf("\n[ ");
	
   while(ptr != NULL) {
      printf("(%d,%d,%d,%d,%d,%d) ",ptr->indice,ptr->x_origine,ptr->y_origine,ptr->composant1,ptr->composant2,ptr->plein);
      ptr = ptr->next;
   }
	
   printf(" ]\n");
}


void inserer(int indice, int x_origine, int y_origine, int composant1, int composant2, int plein) {

   struct nodeListe *link = (struct nodeListe*) malloc(sizeof(struct nodeListe));
	
   link->indice = indice;
   link->x_origine = x_origine;
   link->y_origine = y_origine;
   link->composant1 = composant1;
   link->composant2 = composant2;
   link->plein = plein;
	

   link->next = head;
	

   head = link;
}

void supprimer() {

   struct nodeListe *linkTemp = deleteFirst();
   struct nodeListeBackup *link = (struct nodeListeBackup*) malloc(sizeof(struct nodeListeBackup));
	
   link->indice = linkTemp->indice;
   link->x_origine = linkTemp->x_origine;
   link->y_origine = linkTemp->y_origine;
   link->composant1 = linkTemp->composant1;
   link->composant2 = linkTemp->composant2;
   link->plein = linkTemp->plein;

   link->next = headBackup;
	

   headBackup = link;
}

void restaurer() {

   struct nodeListeBackup *linkTemp = deleteFirstBackup();
   inserer(linkTemp->indice, linkTemp->x_origine, linkTemp->y_origine, linkTemp->composant1, linkTemp->composant2, linkTemp->plein);
}


	
  
  


