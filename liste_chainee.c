#include<stdio.h>  
#include<stdlib.h>  

typedef struct maillon  
{  
    int val;  
    struct maillon *suiv;  
} MAILLON;

typedef MAILLON *ENSEMBLE;

ENSEMBLE ajouterElement(ENSEMBLE E, int i)
{
    ENSEMBLE nouvel_ensemble = malloc(sizeof(nouvel_ensemble));

    if (nouvel_ensemble == NULL)
        exit(EXIT_FAILURE);

    nouvel_ensemble->val = i;
    nouvel_ensemble->suiv = E;

    return nouvel_ensemble;
}

void retirerElement(ENSEMBLE E, int i)
{

    ENSEMBLE tmp = E , precedent;
    
    while (tmp != NULL && tmp->val != i) {
        precedent = tmp;
        tmp = tmp->suiv;
    }

    if (tmp == NULL)
        return;

    precedent->suiv = tmp->suiv;

    free(tmp); 

}

int nbElements(ENSEMBLE E){

    int length =0;

    while(E != NULL)
    {
        E = E->suiv;
        length++;
    }

    return length;

}

int recherche(ENSEMBLE E, int element)
{
    
	while(E != NULL)
    {
		if(E->val == element)
			return 1;
        E = E->suiv;
    }
    return 0;
}

ENSEMBLE complementaire(ENSEMBLE E1, ENSEMBLE E2)
{
    ENSEMBLE E3 = NULL;

    while(E1 != NULL)
    {
        if (!recherche(E2, E1->val))
            E3 = ajouterElement(E3, E1->val);
		
        E1 = E1->suiv;
    }   

    return E3; 
}

ENSEMBLE reunion(ENSEMBLE E1, ENSEMBLE E2)
{
    ENSEMBLE E3 = NULL;

    E3 = E1;
    while(E2 != NULL)
    {
        if (!recherche(E1, E2->val))
            E3 = ajouterElement(E3, E2->val);
		
        E2 = E2->suiv;
    }   

    return E3; 
}

ENSEMBLE intersection(ENSEMBLE E1, ENSEMBLE E2)
{
    ENSEMBLE E3 = NULL;

    while(E1 != NULL)
    {
        if (recherche(E2, E1->val))
            E3 = ajouterElement(E3, E1->val);
		
        E1 = E1->suiv;
    }   

    return E3; 
}

int inclusion(ENSEMBLE E1, ENSEMBLE E2)
{

    while(E1 != NULL)
    {
        if (!recherche(E2, E1->val))
            return 0;
		
        E1 = E1->suiv;
    }   

    return 1; 
}

ENSEMBLE differenceSymetrique(ENSEMBLE E1, ENSEMBLE E2)
{
    ENSEMBLE E3 = intersection(E1, E2),
        E4 = reunion(E1, E2);
    
    return complementaire(E4, E3);
}

void afficherEnsemble(ENSEMBLE E)
{
    while (E != NULL) {
        printf(" %d ", E->val);
        E = E->suiv;
    }
    printf("\n");
}


ENSEMBLE rechercheAutoAdaptative(ENSEMBLE E, int element)
{
    ENSEMBLE precedent, E1 = E;

	while(E1 != NULL)
    {
		if(E1->val == element)
        {
            precedent->suiv = E1->suiv;
            E1->suiv = E;
            E = E1;
        }
        precedent = E1;
        E1 = E1->suiv;
    }
    return E;
}


int main()
{
    ENSEMBLE E = NULL, E1 = NULL, E2 = NULL, E3 = NULL;

    E = ajouterElement(E, 7);
    E = ajouterElement(E, 1);
    E = ajouterElement(E, 3);
    E = ajouterElement(E, 2);

    printf("Le nombre d'elements de l'ensemble est %d\n", nbElements(E));
    printf("Les entiers de l'ensemble: ");
    afficherEnsemble(E);
    retirerElement(E, 1);
    printf("\nLes entiers de l'ensemble apres la suppression de 1: ");
    afficherEnsemble(E);

    E1 = ajouterElement(E1, 5);
    E1 = ajouterElement(E1, 7);
    E1 = ajouterElement(E1, 9);
    E1 = ajouterElement(E1, 1);
    E1 = ajouterElement(E1, 3);
    E1 = ajouterElement(E1, 2);
    E1 = ajouterElement(E1, 4);

    E2 = ajouterElement(E2, 7);
    E2 = ajouterElement(E2, 1);
    E2 = ajouterElement(E2, 3);
    E2 = ajouterElement(E2, 2);

    E3 = complementaire(E1, E2);
    printf("Le complementaire de E2 par rapport a E1 : ");
    afficherEnsemble(E3);

    E3 = reunion(E1, E2);
    printf("La reunion de E1 et E2 : ");
    afficherEnsemble(E3);

    E3 = intersection(E1, E2);
    printf("L'intersection de E1 et E2 : ");
    afficherEnsemble(E3);

    if (inclusion(E1, E2))
        printf("E1 est inclus dans E2\n");
    else
        printf("E1 n'est pas inclus dans E2\n");
    
    E3 = differenceSymetrique(E1, E2);
    printf("La difference symetrique de E1 et E2 : ");
    afficherEnsemble(E3);

    printf("Les entiers de l'ensemble avant la recherche adaptative : ");
    afficherEnsemble(E1);
    
    E3 = rechercheAutoAdaptative(E1, 1);
    printf("Les entiers de l'ensemble apres la recherche adaptative : ");
    afficherEnsemble(E3);
    
    return 0;
}