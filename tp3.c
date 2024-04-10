//Fonctions

#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

graphe* creerGraphe(){
    graphe* nvGraphe = NULL;
    nvGraphe = malloc(sizeof(graphe));
    if (nvGraphe == NULL) {
        // Gestion d'erreur, échec d'allocation mémoire
        return NULL;
    }
    nvGraphe->premier_sommet = NULL;
    return nvGraphe;
} 

void afficherGraphe(graphe* g) {
    sommet* current = g->premier_sommet;
    printf("Les sommets du graphe :\n");
    while (current != NULL) {
        printf("%d ", current->indice);
        current = current->next;
    }
    printf("\n");
}

sommet* rechercherSommet(graphe g, int id){
    sommet* current = g.premier_sommet;
    while(current != NULL){
        if(current->indice == id){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void creerSommet(graphe* g, int id) {
    sommet* nouveau = malloc(sizeof(sommet));
    nouveau->indice = id;
    nouveau->next = NULL;

    if (g->premier_sommet == NULL || id < g->premier_sommet->indice) {
        nouveau->next = g->premier_sommet;
        g->premier_sommet = nouveau;
    }

    sommet* prec = NULL;
    sommet* courant = g->premier_sommet;

    while (courant != NULL && id > courant->indice) {
        prec = courant;
        courant = courant->next;
    }

    prec->next = nouveau;
    nouveau->next = courant;
}


graphe* construireGraphe(int N){
    graphe* user_graph = creerGraphe();
    int id_somm = 0;
    printf("Saisissez l'id du sommet initial : \n");
    scanf("%d", &id_somm);
    insererSommet(user_graph, id_somm);

    for(int i=2; i<=N; i++){
        printf("Saisissez l'id du %deme sommet : \n", i);
        scanf("%d", &id_somm);
        insererSommet(user_graph, id_somm);
    }

    return user_graph; 
}

int rechercherDegre(graphe g){
    sommet* current = g.premier_sommet;
    int degre_max = 0;
    int deg = 0;
    while(current != NULL){
        deg = 0;
        voisin* current_voisin = current->first_voisin;
        while (current_voisin != NULL){
            deg++;
            current_voisin = current_voisin->next_voisin;
        }
        if(deg>degre_max){
            degre_max = deg;
        }
        current = current->next;
    }
    return degre_max;
}

int contientBoucle(graphe g){

}

