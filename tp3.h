//Struct

#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>

typedef struct sommet sommet;
typedef struct voisin voisin;
typedef struct graphe graphe;

struct sommet{  
    int indice;
    struct sommet* next;
    struct voisin* first_voisin;
};

struct voisin{
    int indice;
    struct voisin* next_voisin; 
};

struct graphe{
    struct sommet* premier_sommet;
}; 

#endif