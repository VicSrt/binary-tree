//
// Created by victo on 18/12/2017.
//

#ifndef PROJET_PROJET_H
#define PROJET_PROJET_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//----------------------------------------------------------
// Données
//----------------------------------------------------------

typedef struct
{
    unsigned int nb_colonnes; // la 1ere <=> classe à prédire (Y). Autres colonnes <=> variables d'observatio (Xi)
    unsigned int nb_lignes;   // <=> les individus
    double** matrice;         // tableau de tableaux de réels (i.e. tableaux 2D de réels)
} matrice_donnees;

typedef struct // structure composée des criteres de division
{
    int index_colonne;
    double mediane;
    char* test;    // <=> le ">" implique que nous sommes dans la partie supérieur à la médiane et "<" le contraire
}critere;
struct _noeud // noeud complet
{
    matrice_donnees* data;
    int Y;
    critere alpha;
    int* tab_indice;
    int taille_tab;
    double precision;
    struct _noeud* parent;
    struct _noeud *fils_gauche;
    struct _noeud *fils_droit;

};
typedef  struct _noeud  noeud;

typedef struct // structure de test permettant de renvoyer plusieurs information d'une même fonction
{
    double prec;
    int nbr_sup;
    int nbr_inf;
    int index;
}test_prec;

typedef struct  // permet de retourner plusieurs information de la fonction traitant les entrées clavier.
{
    int Y;
    double seuil_min;
    double seuil_max;
    int nbr_min;
    int taille_max;

}IntHM;




matrice_donnees* charger_donnnees(const char* nom_fichier);

// Usage var =  liberer_donnees(var);
matrice_donnees* liberer_donnees(matrice_donnees * data);

double calcul_mediane(double* tab, int taille);

void permuter(double* tab,int index1,int index2);

int tri_rapide(double* tab,int debut, int fin);

double* mise_sous_tab(noeud* arbre, int colonne);

double max(double a, double b);

int hauteur(noeud* parent);

bool divisible(noeud* arbre, int hauteur_max,int nbr_mini,double prec_mini, double prec_max);

test_prec* test_division(noeud* arbre,int index, test_prec* test);

bool associer_fils_droit(noeud* parent, noeud* enfant);

bool associer_fils_gauche(noeud* parent, noeud* enfant);

void meilleur_division(noeud* arbre, test_prec* test);

noeud *creer_noeud(matrice_donnees* data,int*  tab, int taille_tab);

double calcul_prec(noeud* arbre);

noeud* initialisation();

bool affectation(noeud* arbre, test_prec* test);

void afficher_prefixe(noeud* arbre);

void creation_arbre(noeud* arbre, test_prec* test,IntHM* User);

int hauteur_p(noeud* arbre);

void arbre_final();

void afficher_offset(int offset);

void affichage_arborescence(noeud * arbre, int offset);

bool est_feuille(noeud const * element);

void recuperer_info(IntHM* User);


void predire(noeud* arbre,double* individus);
#endif //PROJET_PROJET_H
