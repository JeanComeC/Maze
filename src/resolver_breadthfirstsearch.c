#include "resolver_breadthfirstsearch.h"

int choix_utilisateur(int min_choice, int max_choice){
    int rep;
    scanf(" %d",&rep);
    if(rep>max_choice || rep<min_choice){
        printf("Votre choix doit être compris entre %d et %d inclus.\n",min_choice,max_choice);
        return choix_utilisateur(min_choice,max_choice);
    }
    return rep;
}

