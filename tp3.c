#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

/*
A FAIRE : GESTION CAS EXTREMES, VERIFIER TOUS LES RETURN (null, 0 ou autre), USER FRIENDLY, CREER TOUS LES SOMMETS PUIS LES ARETES. 
DANS LA FONCTION CREER ARETE YA DEJA LA VERIF QUE LES SOMMETS EXISTE DONC BEAUCOUP PLUS SIMPLE
*/

graphe* creerGraphe(){
    graphe* nvGraphe = NULL;
    nvGraphe = malloc(sizeof(graphe));
    if (nvGraphe == NULL){
        printf("Echec d'allocation de la memoire !");
        return NULL;
    } 
    nvGraphe->premier_sommet = NULL;
    printf("Nouveau graphe cree !\n");
    return nvGraphe;
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

int rechercherArete(graphe g, int id1, int id2) {
    //comme les aretes existent pour les deux sommets, on peut juste vérifier que l'arete existe pour un sommet
    int minimum = 0, autre = 0;
    sommet* sommet = g.premier_sommet;
    voisin* voisin = malloc(sizeof(voisin));
    
    if (id1 <= id2) {
        minimum = id1;
    } else {
        minimum = id2;
        id2 = id1;
    }
    while (sommet->indice != minimum) {
        sommet = sommet->next;
    }
    voisin = sommet->first_voisin;
    while (voisin != NULL) {
        if (voisin->indice == id2) {
            return 1;
        }
        voisin = voisin->next_voisin;
    }
    return 0;
}

int ajouterVoisin(graphe *g, int id1, int id2){

    voisin* nouveau_voisin = NULL;
    nouveau_voisin = malloc(sizeof(voisin));
    if(nouveau_voisin == NULL){
        printf("Echec d'allocation de la memoire !");
        return 0;
    }

    nouveau_voisin->indice = id2;
    nouveau_voisin->next_voisin = NULL;

    sommet* sommet_arete = rechercherSommet(*g, id1);
    
    if (sommet_arete->first_voisin == NULL || id2 < sommet_arete->first_voisin->indice) {
        nouveau_voisin->next_voisin = sommet_arete->first_voisin;
        sommet_arete->first_voisin = nouveau_voisin;
        return 1;
    }
    
    voisin* courant  = sommet_arete->first_voisin;
    voisin* prec = NULL;
    prec = malloc(sizeof(voisin));
    if(prec == NULL){
        printf("Echec d'allocation de la memoire !");
        return 0;
    }

    while (courant != NULL && id2 > courant->indice) {
        prec = courant;
        courant = courant->next_voisin;
    }
    prec->next_voisin = nouveau_voisin;
    nouveau_voisin->next_voisin = courant;
    return 1;
}

void ajouterArete(graphe *g, int id1, int id2) {
    //il faut que le premier sommet soit voisin du deuxième et le deuxième du premier
    //on vérifie que les sommets existent
    if (rechercherSommet(*g, id1) == NULL) {
        printf("Le sommet %d n'existe pas, vous devez le créer !\n", id1);
        creerSommet(g, id1);
    }
    if (rechercherSommet(*g, id2) == NULL) {
        printf("Le sommet %d n'existe pas, vous devez le créer !\n", id2);
        creerSommet(g, id2);
    }
    //on vérifie que l'arete n'existe pas
    if (rechercherArete(*g, id1, id2)) {
        printf("L'arete qui relie les sommets %d et %d existe deja !\n", id1, id2);
        return NULL;
    }
    //on crée l'arete pour le premier sommet
    int result = ajouterVoisin(g, id1, id2);
    if(result){ //on crée l'arete pour le deuxième sommet si elle a bien été ajoutée pour le premier
        result = ajouterVoisin(g, id2, id1);
    }
}

void creerSommet(graphe* g, int id) {

    if(rechercherSommet(*g, id) != NULL) {
        printf("Un sommet avec l'indice %d existe déjà dans le graphe.\n", id);
        return NULL;
    }

    sommet* nouveau = malloc(sizeof(sommet));
    if (nouveau == NULL){
        printf("Echec d'allocation de la memoire !");
        return NULL;
    }

    nouveau->indice = id;
    nouveau->first_voisin = NULL;
    nouveau->next = NULL;

    if (g->premier_sommet == NULL || id < g->premier_sommet->indice) {
        nouveau->next = g->premier_sommet;
        g->premier_sommet = nouveau;
        return;
    }

    sommet* prec = g->premier_sommet;
    sommet* courant = prec->next;

    while (courant != NULL && id > courant->indice) {
        prec = courant;
        courant = courant->next;
    }

    nouveau->next = courant;
    prec->next = nouveau;
    

    int entree_id = 0;
    printf("Entrez un voisin de %d, -1 pour arreter : ", nouveau->indice);
    scanf("%d", &entree_id);

    while (entree_id != -1) {
        ajouterArete(g, id, entree_id);
        printf("Entrez le voisin suivant de %d, -1 pour arreter : ", nouveau->indice);
        scanf("%d", &entree_id);
    }
}


graphe* construireGraphe(int N){

    if(N<1){
        printf("Erreur : le nombre de sommets du graphe est invalide.");
        return NULL;
    }

    graphe* user_graph = creerGraphe();
    int id_somm = 0;

    printf("Saisissez l'id du sommet initial : \n");
    scanf("%d", &id_somm);
    creerSommet(user_graph, id_somm);

    for(int i=1; i<N; i++){
        printf("Saisissez l'id du %deme sommet : \n", i+1);
        scanf("%d", &id_somm);
        if(id_somm < 1 || id_somm > N){
            printf("Erreur : l'indice doit etre compris entre 1 et %d", N);
            break;
        }
        if (rechercherSommet(*user_graph, id_somm) != NULL) {
            printf("Le sommet avec l'indice %d a déjà été ajoute.\n", id_somm);
            break;
        }
        creerSommet(user_graph, id_somm);
    }
    return user_graph; 
}

void afficherGraphe(graphe g) {
    sommet* current_sommet = g.premier_sommet;
    voisin* current_voisin = NULL;
    current_voisin = malloc(sizeof(voisin));
    if(current_voisin == NULL){
        printf("Echec d'allocation de la memoire !");
        return 0;
    }
    
    while (current_sommet != NULL) {
        printf("\n|\n%d", current_sommet->indice);
        current_voisin = current_sommet->first_voisin;
        while (current_voisin != NULL) {
            printf(" - %d", current_voisin->indice);
            current_voisin = current_voisin->next_voisin;
        }
        printf(" - NULL");
        current_sommet = current_sommet->next;
    }
    printf("\n|\nNULL");
    printf("\n\n");
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

void supprimerSommet(graphe *g, int id){
    return;
}

int nombreSommet(graphe g){
    sommet *sommetActuel = g.premier_sommet;
    int nb_sommet = 0;
    while(sommetActuel != NULL){
        nb_sommet++;
        sommetActuel = sommetActuel->next;
    }
    return nb_sommet;
}

int Cycle(sommet* sommetCurrent, int* visited, int parent, graphe g) {

    voisin* currentV = sommetCurrent->first_voisin;
    while (currentV != NULL) {
        if (visited[currentV->indice] == 0){
            sommet* sommet_associe = rechercherSommet(g, currentV->indice);
            if(Cycle(sommet_associe, visited, sommetCurrent->indice, g) == 1){
                return 1;
            }
        }else if (currentV->indice != parent){
            return 1;
        }
        currentV = currentV->next_voisin;
    }
    return 0;
}

int contientBoucle(graphe g){

    int* visited = NULL;
    int nb_sommets = nombreSommet(g);
    visited = malloc(nb_sommets * sizeof(int));
    if(visited == NULL){
        printf("Erreur d'allocation de la mémoire");
        exit(0);
    }

    sommet* current = g.premier_sommet;
    if(current == NULL){
        printf("Le graphe est vide, il ne contient donc pas de boucle\n");
        return 0;
    }

    while (current != NULL) {
        if (visited[current->indice] == 0 && Cycle(current, visited, -1, g) == 1)
            return 1; 
        current = current->next;
    }
    return 0; 
}

void fusionnerSommet(graphe *g, int idSommet1, int idSommet2){
    return;
}

