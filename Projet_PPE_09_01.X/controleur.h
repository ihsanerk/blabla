#ifndef CONTROLEUR_H_INCLUDED
#define CONTROLEUR_H_INCLUDED

//Librairies
#include  "moteur.h"

//Structure de position
typedef struct _Position
{
	float 	x; //En mm
	float 	y;
	float 	angle;//Angle en milliËme de radian (PI = 3141)

}Position;

//Variables
extern Position Gali_current;
extern Position Gali_objectif;

//Prototypes des fonctions
void SetPositionObjectif(float x, float y, float angle);
void SetPositionCurrent(float x, float y, float angle);
void UpdatePosition();
BOOL PositionParRapportObjectif();
float NormaliserAngle(float angle);


#endif // CONTROLEUR_H_INCLUDED
