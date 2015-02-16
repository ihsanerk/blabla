#ifndef CONTROLEUR_H_INCLUDED
#define CONTROLEUR_H_INCLUDED

//Librairies
#include  "moteur.h"
#include  "debugger.h"
#include  "math.h"

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
extern float position_x;
extern float position_y;
extern float position_angle;

//Prototypes des fonctions
void SetPositionObjectif(float x, float y, float angle);
void SetPositionCurrent(float x, float y, float angle);
void UpdatePosition();
BOOL PositionParRapportObjectif();
float NormaliserAngle(float angle);

void afficher_position();
void afficher_objectif();
void afficher_Gali();

#endif // CONTROLEUR_H_INCLUDED
