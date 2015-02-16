/* 
 * File:   dijkstra.h
 * Author: guillaume
 *
 * Created on 14 février 2015, 12:12
 */

#ifndef DIJKSTRA_H
#define	DIJKSTRA_H

//Librairies
#include "math.h"

#define INF 1000000 //Valeur infini

#define NB_NOEUD 14

//Matrice des connections entre les différentes actions
extern int MATRICE_NOEUD[NB_NOEUD][NB_NOEUD] =
{
    {0,100,200,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
};

//Tableau du chemin à parcourrir
extern t_noeud CHEMIN [NB_NOEUD];

struct t_noeud
{
    //Variables
    //Nom de l'action
    char nom[50];
    //La position en X
    float position_x;
    //La position en Y
    float postion_y;
    //La position en Angle
    float position_angle;
    //Si l'action a été faite
    BOOL etat;

};

struct t_dijkstra
{
    //Variables
    int sommet;
    int destination;
    int longueur[NB_NOEUD];
    int pred[NB_NOEUD];

};

typedef struct t_dijkstra dijkstra;

typedef struct t_noeud noeud;


void initDijkstra(int Position_depart,int Position_final);
void dijkstra(int sommet, int destination);

#endif	/* DIJKSTRA_H */

