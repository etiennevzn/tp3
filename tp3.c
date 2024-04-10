#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#define NB_MAX_SOMMETS 50

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

    sommet* currentSommet = g->premier_sommet;
    while (currentSommet != NULL) {
        if (currentSommet->indice == id) {
            printf("Un sommet avec l'indice %d existe déjà dans le graphe.\n", id);
            return;
        }
        currentSommet = currentSommet->next;
    }

    sommet* nouveau = malloc(sizeof(sommet));
    if (nouveau == NULL) {
        return NULL;
    }

    nouveau->indice = id;
    nouveau->first_voisin = NULL;
    nouveau->next = NULL;

    int entree_id = 0;
    printf("Entrez un voisin de %d, -1 pour arreter : ", nouveau->indice);
    scanf_s("%d", &entree_id);

    while (entree_id != -1) {
        ajouterArete(g, id, entree_id);
        printf("Entrez le voisin suivant de %d, -1 pour arreter : ", nouveau->indice);
        scanf_s("%d", &entree_id);
    }

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
    int liste_sommets[NB_MAX_SOMMETS];
    int i,j;

    printf("Saisissez l'id du sommet initial : \n");
    scanf("%d", &id_somm);
    liste_sommets[0] = id_somm;
    creerSommet(user_graph, id_somm);

    for(i=1; i<N; i++){
        printf("Saisissez l'id du %deme sommet : \n", i);
        scanf("%d", &id_somm);

        for (j = 0; j < i; j++) {
            if (liste_sommets[j] == id_somm) {
                printf("Le sommet avec l'indice %d a déjà été ajouté.\n", id_somm);
                break;
            }
        }
        liste_sommets[i] = id_somm;
        creerSommet(user_graph, id_somm);
        i++;
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

int Cycle(sommet* s, int* visited, int parent) {
    visited[s->indice] = 1;

    voisin* v = s->first_voisin;
    while (v != NULL) {
        if (!visited[v->indice]) {
            if (estCycleDFS(v, visited, s->indice))
                return 1;
        } else if (v->indice != parent)
            return 1;
        v = v->next_voisin;
    }
    return 0;
}

int contientBoucle(graphe g){

    int visited[NB_MAX_SOMMETS] = {0};

    sommet* current = g.premier_sommet;
    while (current != NULL) {
        if (!visited[current->indice] && estCycleDFS(current, visited, -1))
            return 1; 
        current = current->next;
    }
    return 0; 
}

