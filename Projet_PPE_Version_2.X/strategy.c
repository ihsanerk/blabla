
#include <stdio.h>
#include "strategy.h"

int allselected(int *selected)
{
  int i;
  for(i=0;i<MAXACTION;i++)
    if(selected[i]==0)
      return 0;
  return 1;
}

int* shortpath(int cost[][MAXACTION],int *preced,int *distance)
{

  int* shortpath;
  int selected[MAXACTION]={0};
  int current=0,i,j,k,dc,smalldist,newdist;

  for(i=0;i<MAXACTION;i++)
    distance[i]=INFINI;

  selected[current]=1;
  distance[0]=0;
  current=0;

  while(!allselected(selected))
  {
    smalldist=INFINI;
    dc=distance[current];
    for(i=0;i<MAXACTION;i++)
    {
      if(selected[i]==0)
      {
        newdist=dc+cost[current][i];
        if(newdist<distance[i])
        {
          distance[i]=newdist;
          preced[i]=current;
        }
        if(distance[i]<smalldist)
        {
          smalldist=distance[i];
          k=i;
        }
      }
    }
    current=k;
    //savegarder le chemin dans une variable
    printf("point : %d\n", current);
    for (j=0; j<MAXACTION ; j++)
    {
        if(shortpath[j]==NULL)
            shortpath[j] = current;
    }
    selected[current]=1;
   }
   return shortpath ;
}

void strategy()
{
    int * dijkstra;
  int cost[MAXACTION][MAXACTION]=
  {
{0,400,200,700,500,100,150,170,INFINI,600,590,180,181,182},
{400,0,600,650,INFINI,800,INFINI,900,450,950,INFINI,INFINI,INFINI,INFINI},
{200,600,0,100,150,610,615,620,510,505,500,450,451,452},
{700,650,100,0,120,615,620,625,525,725,700,690,691,692},
{500,490,150,120,0,700,725,750,550,650,600,670,671,672},
{100,800,610,615,700,0,105,110,150,200,170,850,851,852},
{150,INFINI,615,620,725,105,0,100,200,700,690,500,501,502},
{170,900,620,625,750,110,100,0,120,500,490,400,401,402},
{INFINI,450,510,525,550,150,200,120,0,3,502,503,504,505},
{600,950,505,725,650,200,700,500,3,0,2,900,901,902},
{590,INFINI,500,700,600,170,690,490,502,2,0,13,12,10},
{180,INFINI,450,690,670,850,500,400,503,900,13,0,100,150},
{181,INFINI,451,691,671,851,501,401,504,901,12,100,0,50},
{182,INFINI,452,692,672,852,502,402,505,902,10,150,50,0}
};

  int preced[MAXACTION]={0},distance[MAXACTION];
  int maximum = 950; //maximum du tableau

  BOOL doCalcul = FALSE;
  BOOL EnnemyDetected = FALSE;
  int target,i,j ;

  BOOL sens = TRUE;
 
    if (dijkstra == NULL)
      {
          dijkstra=shortpath(cost,preced,distance);
      }

  while(1)
  {

    if(doCalcul)
    {
        dijkstra = shortpath(cost, preced, distance);
    }
    for (i=0; i <MAXACTION ; i++)
    {
            target = dijkstra [i];
            EnnemyDetected = detectionSharpProcess(sens);
            if (EnnemyDetected == FALSE)
            {
               //go to target à ajouter mais que de qlq cm
                switch (target)
                {
                    case 0 : //algo poser plots ou gobelet
                                break;
                    case 1 : //algoPrendreGobelet
                                break;
                    case 2 : //algoPrendrePlot
                                break;
                    case 3 : //algoPrendrePlot
                                break;
                    case 4 : //algoPrendrePlot
                                break;
                    case 5 : //algoPrendrePlot
                                break;
                    case 6 : //algoPrendrePlot
                                break;
                    case 7 : //algoPrendrePlot
                                break;
                    case 8 : //algoPoserPlots
                                break;
                    case 9 : //algoClapets
                                break;
                    case 10 ://algoClapets
                                break;
                    case 11 ://algoPrendreGoblet
                                break;
                    case 12 ://algoPoserPlots
                                break;
                    case 13 ://algoPoserPlots
                                break;
                }
            }
            else
            {
                maximum++;
                cost[i][j]= maximum;
                cost[j][i]= maximum;
            }


        
    }

  }
}
