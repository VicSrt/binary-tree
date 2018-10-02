//
// Created by victo on 18/12/2017.
//
 // IL RESTE A FAIRE UN PROGRAMME REGROUPPANT 1+2+3 étapes,  + interraction H/M(MENU)+ programme menu

#include "projet.h"

//----------------------------------------------------------
// Données
//----------------------------------------------------------

matrice_donnees* charger_donnnees(const char* nom_fichier)
{
    FILE* fichier = fopen("C:\\Users\\victo\\Documents\\ESILV\\A3\\Algorithmique en c\\PROJET\\iris.txt","r");  // full path a rajouter pour que cela fonctionne sous c-lion.
    if( fichier != NULL )
    {
        unsigned int nb_lignes;
        unsigned int nb_colonnes;

        // Etape 1 - traitement première ligne
        fscanf(fichier, "%u %u", &nb_lignes, &nb_colonnes); // %u <=> unsigned int
        fgetc(fichier); // lecture du retour chariot ('\n'). Valeur ignorée => passage à la ligne suivante

        // Etape 2 - allocation des lignes de la matrice
        double** matrice = (double**) malloc( nb_lignes * sizeof(double*) );

        // Etape 3 - remplissage de la matrice
        for(int ligne = 0 ; ligne < nb_lignes ; ligne++)
        {
            // allocation des colonnes de la matrice (pour chaque ligne)
            matrice[ligne] = (double*) malloc( nb_colonnes * sizeof(double) );

            for(int colonne = 0 ; colonne < nb_colonnes ; colonne++)
            {
                if(colonne != nb_colonnes-1)
                {
                    fscanf(fichier, "%lg ", &matrice[ligne][colonne]);
                }
                else // dernière colonne (où le réel n'est pas suivi d'un espace)
                {
                    fscanf(fichier, "%lg" , &matrice[ligne][colonne]);
                }
            }

            fgetc(fichier); // lecture du retour chariot ('\n'). Valeur ignorée => passage à la ligne suivante
        }

        matrice_donnees * data = (matrice_donnees*) malloc(sizeof(matrice_donnees));
        data->nb_colonnes = nb_colonnes;
        data->nb_lignes = nb_lignes;
        data->matrice = matrice;

        fclose(fichier);
        return data;
    }

    printf("Fichier %s inconnu.\n", nom_fichier);
    return NULL;
}

// Usage : var = liberer_donnees(var);  => var devient NULL
matrice_donnees* liberer_donnees(matrice_donnees * data)
{
    if(data != NULL)
    {
        for(int ligne = 0 ; ligne < data->nb_lignes ; ligne++)
        {
            if(data->matrice[ligne] != NULL) // normalement toujours vrai
                free(data->matrice[ligne]);
        }
        free(data->matrice);
        free(data);
    }
    return NULL;
}

double calcul_mediane(double* tab, int taille)
{
    double result=0.0 ;
    if( taille%2==0)
    {
        result= (tab[taille/2]+tab[(taille/2)-1])/2 ;
        if (result==tab[taille-1])
        {
            int i=1;
            while(tab[taille-i]==result)
            {
                i--;
            }
            result=tab[taille-i];
        }

    }
    else
    {
        result=tab[(taille+1)/2];
        if (result==tab[taille-1])
        {
            int i=1;
            while(tab[taille-i]==result)
            {
                i--;
            }
            result=tab[taille-i];
        }

    }
    return result;
}

double* mise_sous_tab(noeud* arbre, int colonne)
{
    double* tab=(double*)malloc(sizeof(double)*arbre->taille_tab);
    for(int i=0;i<arbre->taille_tab;i++)
    {
       tab[i]=arbre->data->matrice[arbre->tab_indice[i]][colonne];
    }
    return tab;
}
void permuter(double* tab,int index1,int index2)
{
    double intermediraire=tab[index1];
    tab[index1]=tab[index2];
    tab[index2]=intermediraire;
}

int tri_rapide(double * tab,int debut, int fin)
{
    int condition=0;
    int gauche=debut-1;
    int droite=fin+1;
    const double pivot= tab[debut];

    if (debut>=fin)
    {
        return 1;
    }
    while(condition==0)
    {
        do
        {
            droite--;
        }while(tab[droite]>pivot);

        do
        {
            gauche++;
        }while(tab[gauche]<pivot);

        if(gauche<droite)
        {
            permuter(tab,gauche,droite);

        }

        else
            condition=1;
    }


    {
    }


    tri_rapide(tab, debut, droite);
    tri_rapide(tab,droite+1,fin);

}
double max(double a, double b)
{
    double result=0;
    if(a>=b)
    {
       result=a;
    }
    else
    {
        result=b;
    }
    return result;
}
int hauteur(noeud* parent)
{
    if(parent==NULL)
    {
        return 0;
    }
    else
    {
        return 1+(int)max(hauteur(parent->fils_droit),hauteur(parent->fils_gauche));
    }
}


bool divisible(noeud* arbre, int hauteur_max,int nbr_mini,double prec_mini, double prec_max)
{
    bool result=false;
    if((hauteur_p(arbre)<hauteur_max)&&(arbre->taille_tab>=nbr_mini)&&(arbre->precision>=prec_mini)&&(arbre->precision<=prec_max))
    {
        result=true;
    }
    return result;
}

test_prec* test_division(noeud* arbre, int index, test_prec* test) // test de division
{
    double prec=-1.0;
    double*tab =mise_sous_tab(arbre,index);
    tri_rapide(tab,0,arbre->taille_tab-1);
    double mediane=calcul_mediane(tab,arbre->taille_tab);
    int nbr_inf=0;
    int nbr_sup=0;
    int nbr_sup_ok=0;
    int nbr_inf_ok=0;
    for(int i=0;i<arbre->taille_tab;i++)
    {
        if(arbre->data->matrice[arbre->tab_indice[i]][index]>mediane)
        {
            nbr_sup++;

            if (arbre->data->matrice[arbre->tab_indice[i]][0]==arbre->Y)
            {
                nbr_sup_ok++;
            }
        }
        else
        {
            nbr_inf++;
            if (arbre->data->matrice[arbre->tab_indice[i]][0]==arbre->Y)
            {
                nbr_inf_ok++;
            }
        }
    }
    prec=max(((double)nbr_sup_ok/nbr_sup),((double)nbr_inf_ok/nbr_inf));
    test->nbr_inf=nbr_inf;
    test->nbr_sup=nbr_sup;
    test->prec=prec;
    return test;



}

double calcul_prec(noeud* arbre) // calcul de précision
{
    int compt_Y=0;
    matrice_donnees * databis=arbre->data;
    int* tabbis=arbre->tab_indice;
    for (int i=0;i<arbre->taille_tab;i++)
    {

        if (databis->matrice[tabbis[i]][0] == arbre->Y)
        {
            compt_Y++;
        }

    }

    return((double)compt_Y/arbre->taille_tab);
}


void meilleur_division(noeud* arbre, test_prec* test) // recherche de la meilleure division a partie du test de precision
{

    double prec_max=-1.0;

    int meilleur=-1;
    for(int i=1;i<5;i++)
    {

        test=test_division(arbre,i,test);  // test de la division -> simulation de la partition
        if(test->prec>prec_max)
        {
            prec_max=test->prec;
            meilleur=i;
        }
        test->index=meilleur;
    }

}
bool affectation(noeud* arbre, test_prec* test) // creation de deux tableau, permettant de mémoriser les indices des valeurs supérieur et infénieur a la mediane. Creation des noeud droit et gauche
{
    bool result=false;
    int j=0;
    int j2=0;
    int* tabg=(int*)malloc(sizeof(int)*test->nbr_inf);
    int* tabd=(int*)malloc(sizeof(int)*test->nbr_sup);
    double mediane=calcul_mediane(mise_sous_tab(arbre,test->index),arbre->taille_tab);
    for(int i=0; i<arbre->taille_tab;i++)
    {
        if(arbre->data->matrice[arbre->tab_indice[i]][test->index]>mediane)
        {
            tabd[j]=arbre->tab_indice[i];

            j++;

        }
        else
        {
            tabg[j2]=arbre->tab_indice[i];

            j2++;


        }
    }

    noeud* D=creer_noeud(arbre->data,tabd,j);
    noeud* G=creer_noeud(arbre->data,tabg,j2);
    G->Y=arbre->Y;
    G->alpha.index_colonne=test->index;
    G->alpha.mediane=mediane;
    G->alpha.test="=<";
    G->precision=calcul_prec(G);



    D->Y=arbre->Y;
    D->alpha.index_colonne=test->index;
    D->alpha.mediane=mediane;
    D->alpha.test=">";
    D->precision=calcul_prec(D);

    bool verif_d=associer_fils_droit(arbre, D);
    bool verif_g=associer_fils_gauche(arbre,G);

    if((verif_d)&&(verif_g))
    {
        result=true;
    }

    return result;
}





bool associer_fils_gauche(noeud* parent, noeud* enfant)
{
    bool result= false;
    if (parent!=NULL)
    {
        parent->fils_gauche=enfant;
        enfant->parent=parent;
        if (parent->fils_gauche != NULL)
        {
            result=true;
        }
    }
    return result;
}

bool associer_fils_droit(noeud* parent, noeud* enfant)
{
    bool result= false;
    if ((parent!=NULL)&&(enfant!=NULL)) {
        parent->fils_droit = enfant;
        enfant->parent = parent;
        if (parent->fils_droit != NULL)
        {
            result = true;
        }
    }
    return result;
}

noeud *creer_noeud(matrice_donnees* data,int*  tab, int taille_tab) // programme permettant la creation d'un noeud
{
    noeud* new_noeud=(noeud*)malloc(sizeof(noeud));
    new_noeud->tab_indice=tab;
    new_noeud->taille_tab=taille_tab;
    new_noeud->data=data;
    new_noeud->fils_droit=NULL;
    new_noeud->fils_gauche=NULL;
    new_noeud->parent=NULL;
    return new_noeud;
}
noeud* initialisation() //initialise la racine et la rempli des 120 indices, creation de la matrice
{

    matrice_donnees* data=(matrice_donnees*)malloc(sizeof(matrice_donnees));
    data=charger_donnnees("iris.txt");
    int* tab=(int*)malloc(sizeof(int)*120);
    for(int i=0; i<120;i++)
    {
        tab[i]=i;
    }
    noeud* arbre=creer_noeud(data,tab,120);
    arbre->Y=1;
    arbre->precision=calcul_prec(arbre);


}


void afficher_prefixe(noeud* arbre)
{
    if(arbre!=NULL)
    {
        for(int i=0; i<arbre->taille_tab;i++)
        {
            printf("%lf ", arbre->data->matrice[arbre->tab_indice[i]][arbre->alpha.index_colonne]);
        }
        printf("\n\n");
        afficher_prefixe(arbre->fils_gauche);
        afficher_prefixe(arbre->fils_droit);
    }
}


void arbre_final() // programme regroupant l'initialisation, la creation et l'affichage
{
    IntHM* User=(IntHM*)malloc(sizeof(IntHM));
    recuperer_info(User);

    noeud* arbre=initialisation();
    test_prec* test=(test_prec*)malloc(sizeof(test_prec));
    creation_arbre(arbre,test,User);
    affichage_arborescence(arbre,0);

}

int hauteur_p(noeud* arbre) // hauteur de l'arbre calculé avec le dernier noeud, en remontant
{
    if(arbre==NULL)
    {
        return 0;
    }
    else
    {
        return 1+hauteur_p(arbre->parent);
    }
}

void creation_arbre(noeud* arbre, test_prec* test,IntHM* User) //creation de l'arbre recursivement
{


    meilleur_division(arbre, test);
    affectation(arbre,test);
    if (divisible(arbre,User->taille_max,User->nbr_min,User->seuil_min,User->seuil_max))
    {
        printf("ici");
         creation_arbre(arbre->fils_droit, test,User);
         creation_arbre(arbre->fils_gauche, test,User);

    }


}


void afficher_offset(int offset)
{
    for(int i = 0 ; i < offset ; i++)
    {
        printf("  ");
    }
}


void affichage_arborescence(noeud * arbre, int offset)
{
    if(arbre != NULL)
    {

        printf("\n");
        afficher_offset(offset);
        if( offset != 0 )
        {
            printf("|-");
        }
        printf("Precision:%lg  Nombre individus: %d Chemin: %s%lg ", arbre->precision,arbre->taille_tab,arbre->alpha.test, arbre->alpha.mediane);


        if( !est_feuille(arbre) && (arbre->fils_gauche == NULL) )
        {
            printf("\n");
            afficher_offset(offset+1);
            printf("|-x");
        }
        affichage_arborescence(arbre->fils_gauche, offset+1);



        if( !est_feuille(arbre) && (arbre->fils_droit == NULL) )
        {
            printf("\n");
            afficher_offset(offset+1);
            printf("|-x");
        }
        affichage_arborescence(arbre->fils_droit, offset+1);
    }

}

bool est_feuille(noeud const * element)
{
    bool result=false;
    if(((element->fils_droit)==NULL)&&((element->fils_gauche)==NULL))
    {
        result=true;
    }
    return result;
}

void viderBuffer()
{
    int c;
    while((c=getchar()) != EOF && c != '\n');

}

void recuperer_info(IntHM* User) // recuperer les informations de la console
{
    printf("Bonjour, j'aimerai les informations suivantes:\n" );
    printf("la valeur de Y a predire:");
    int Y;
    scanf("%d",&Y);
    //User->Y =recuperation_conversion_int(chaine1);
    printf("Seuil minimal de precision:");
    double seuil_min;
    scanf("%lf",&seuil_min);
    printf("Seuil maximal de precision:");
    double seuil_max;
    scanf("%lg",&seuil_max);
    printf("nombre minimal d'individus par echantillon");
    int nbr_min;
    scanf("%d",&nbr_min);
    printf("taille maximal de l'arbre:");
    int taille_max;
    scanf("%d",&taille_max);

    User->taille_max=taille_max;
    User->Y=Y;
    User->seuil_max=seuil_max;
    User->seuil_min=seuil_min;
    User->nbr_min=nbr_min;


}


void predire(noeud* arbre,double* individus) // en considerant individus comme un tableau de 4 éléments dans l'ordre X1;X2;X3;X4
{
    while(!est_feuille(arbre))
    {
        if(individus[arbre->alpha.index_colonne-1]>arbre->alpha.mediane)
        {
            predire(arbre->fils_droit, individus);
            printf("Precision:%lg  Nombre individus: %d Chemin: %s%lg ", arbre->precision,arbre->taille_tab,arbre->alpha.test, arbre->alpha.mediane);
        }
        else
        {
            predire(arbre->fils_gauche,individus);
            printf("Precision:%lg  Nombre individus: %d Chemin: %s%lg ", arbre->precision,arbre->taille_tab,arbre->alpha.test, arbre->alpha.mediane);

        }
        printf("Cette individu est un %d avec une precision de %lg",arbre->Y,arbre->precision );
    }
}
