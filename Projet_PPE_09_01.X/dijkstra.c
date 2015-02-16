//Librairies
#include "dijkstra.h"


//Fonction d'Initialisation
void initDijkstra(int Position_depart,int Position_final)
{
    //Ressources
    int i=0;

    //On remet le chemin � z�ro
    for(i=0 ; i<NB_NOEUD; i++)
    {
        CHEMIN[i].etat=FALSE;
    }


}

void dijkstra(int sommet, int destination)
{
    //variables locales
    int  marques[];
    int x,y,xmin;
    float min;
    int nb=0;
    int i;

    //Allocation marques
    marques=(int*)malloc(NB_NOEUD*sizeof(int));
    
    //initialisation du tableau de marquage � 0  et de longueur � INFINI
    for(i=0; i<NB_NOEUD; i++)
    {
        marques[i]=0;
        dijkstra.longueur[i]=INF;
    }

    //Initialisr longueur de s nombre de sommets marqu�s � 0
    dijkstra.longueur[sommet]=nb=0;

    //Tant que les sommmets ne sont pas ts marqu�s
    while(nb<NB_NOEUD)
    {
        //initialisation longueur minimale ? l'infini
        min=INF;
        //Pour tous les sommets X non marqu�s de longeur minimale
        //Stocker le sommet "XMIN" de longueur miniale
        for(x=0; x<NB_NOEUD; x++)
        {


            if(!marques[x]&&dijkstra.longueur[x]<min)
            {
                xmin=x;

                min=dijkstra.longueur[x];
            }
        }
        //Marquer le sommet de longueur minimale "XMIN" et incr�menter "nb"
        marques[xmin]=1;
        nb++;

        //Pour tous les sommets adjacents � "XMIN" et non marqu�s
        //Chercher la plus petite distance de y "XMIN"
        //Stocker le pr�d�cesseur "xmin" de y
        for(y=0; y<NB_NOEUD; y++)
        {
            if(MATRICE_NOEUD[xmin][y] && !marques[y]&& dijkstra.longueur[xmin]+MATRICE_NOEUD[xmin][y]<dijkstra.longueur[y]) {
                dijkstra.longueur[y]=dijkstra.longueur[xmin]+MATRICE_NOEUD[xmin][y];
                dijkstra.pred[y]=xmin;
            }

        }
    }
    //Lib�rer la m�moire du tableau de marquage
    free(marques);
}

/*void chemin(t_dijkstra* p)
{
    int i,j;
    for(i=0; i<p->ordre; i++)
    {

        if(i!=p->ordre)
        {
            printf("Plus court chemin pour aller de %d a %d:\n",p->s,i);
            j=i;

            while(j!=-1)
            {
                printf(" %d ",j);
                j=p->pred[j];

            }
            printf("\nDe distance %d\n\n",p->l[i]);
        }
    }
}*/
