#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#include "tp3.c"

int main(int argc, const char * argv[]) {
    
    int choix = 0;
    int N = 0, indice = 0, indice1 = 0, indice2 = 0, degre_maximal = 0;
    graphe* graphe = NULL;
    
    while (choix != 10) {
        printf("\n1. Creer un graphe vide\n");
        printf("2. Construire un graphe de N sommets\n");
        printf("3. Ajouter un sommet\n");
        printf("4. Ajouter une arete\n");
        printf("5. Afficher un graphe\n");
        printf("6. Donner le degre maximal du graphe\n");
        printf("7. Supprimer un sommet\n");
        printf("8. Verifier si le graphe contient une boucle\n");
        printf("9. Fusionner deux sommets\n");
        printf("10. Quitter\n");
        
        scanf("%d", &choix);
        
        if (graphe == NULL) {
            switch (choix) {
                case 1:
                    graphe = creerGraphe();
                    break;
                case 2:
                    printf("Quelle est la taille du graphe a construire ?\n");
                    scanf("%d", &N);
                    graphe = construireGraphe(N);
                    break;
                case 10:
                    break;
                default:
                    printf("Vous n'avez pas encore cree de graphe !\n");
            }
        } else {
            switch (choix) {
                case 1:
                    graphe = creerGraphe();
                    break;
                case 2:
                    printf("Quelle est la taille du graphe a construire ?\n");
                    scanf("%d", &N);
                    graphe = construireGraphe(N);
                    break;
                case 3:
                    printf("Quel est l'indice du sommet ?\n");
                    scanf("%d", &indice);
                    creerSommet(graphe, indice);
                    break;
                case 4:
                    printf("Quels sont les indices des deux sommets qui constituent l'arete ?\n");
                    scanf("%d", &indice1);
                    scanf("%d", &indice2);
                    ajouterArete(graphe, indice1, indice2);
                    break;
                case 5:
                    afficherGraphe(*graphe);
                    break;
                case 6:
                    degre_maximal = rechercherDegre(*graphe);
                    printf("Le degre maximal du graphe est %d\n", degre_maximal);
                    break;
                case 7:
                    printf("Quel sommet voulez-vous supprimer ?\n");
                    scanf("%d", &indice);
                    supprimerSommet(graphe, indice);
                    break;
                case 8:
                    if (contientBoucle(*graphe) == 1) {
                        printf("Le graphe contient une boucle.\n");
                    } else if (contientBoucle(*graphe) == 0) {
                        printf("Le graphe ne contient pas de boucles.\n");
                    } else {
                        printf("Ne renvoie ni 1 ni 0, erreur\n");
                    }
                    break;
                case 9:
                    printf("Quel est le premier sommet qui sera fusionne ?\n");
                    scanf("%d", &indice1);
                    printf("Quel est le deuxieme sommet qui sera fusionne ?\n");
                    scanf("%d", &indice2);
                    fusionnerSommet(graphe, indice1, indice2);
                    break;
                default:
                    printf("Merci d'avoir utilise ce simulateur de graphe, au revoir !\n");  
                    
            }
        
        }
        
    }
    
    return 0;
}
