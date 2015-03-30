#ifndef ASSERVISSEMENT_H_INCLUDED
#define ASSERVISSEMENT_H_INCLUDED

//Libraries
#include "Definitions.h"
#include "Moteur.h"
#include "Coefs.h"

//Pines

//Structures
typedef struct _Asservissement
{
    int32 variation         ;		//Variation entre les valeurs actuelles et les anciainnes
	int32 variationSomme	;
    int32 ordre             ;		//Consigne donnéau robot à la fin du threas
	int32 erreur			;
    int32 oldOrdre          ;		//Précédente consigne du robot
    int32 erreurTolerance    ;		//Tolerance par rapport à l'erreur

    int32 coefDerive        ;
    int32 coefDeriveNeg     ;		//Lorsque le robot va en marche arrière
    int32 coefProportionnel ;
    int32 coefPropNeg       ;		//Lorsque le robot va en marche arrière

    int32 VMax              ;		//Vitesse max
    int32 Vmin              ;		//Vitesse min

	bool enable				;
    int32 coefAcceleration  ;

}Asservissement;


//Prototypes
void 					asservissementPolInit();
void					asservissementCircuInit();
void 					asservissementInit();

inline void             polaire();						
inline void				circulaire ();
inline void             pid(Asservissement * ass, bool ralentir);		//Calcule la nouvelle consigne
void                    limite(Asservissement * ass, bool ralentir);	//Seuillage

void 					asservissementPolaire(bool avance);
void 					asservissementCirculaire ();
void 					erreursReInit ();
void 					erreurMemory ();
void 					sommeVariations ();

//Variables
extern Asservissement   angle           ;				//Angle pour l'asserivssement polaire
extern Asservissement   distance        ;				//Distance pour l'asserivssement polaire

extern Asservissement   roueDroite      ;				//Pour asservissement circulaire
extern Asservissement   roueGauche      ;				

#endif // ASSERVISSEMENT_H_INCLUDED
