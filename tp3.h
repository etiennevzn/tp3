#ifndef HEADER_FILE
#define HEADER_FILE

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

graphe* creerGraphe();
void creerSommet(graphe *g, int id);
sommet* rechercherSommet(graphe g, int id);
int rechercherArete(graphe g, int id1, int id2);
int ajouterVoisin(graphe *g, int id1, int id2);
void ajouterArete(graphe *g, int id1, int id2);
graphe* construireGraphe(int N);
void afficherGraphe(graphe g);
int rechercherDegre(graphe g);
void supprimerSommet(graphe *g, int id);
int nombreSommet(graphe g);
int Cycle(sommet* sommetCurrent, int* visited, int parent, graphe g);
int contientBoucle(graphe g);
void fusionnerSommet(graphe *g, int idSommet1, int idSommet2);

#endif
