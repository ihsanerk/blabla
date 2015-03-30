//Libraries
#include "Asservissement.h"

//Variables
Asservissement angle    ;
Asservissement distance ;
Asservissement   roueDroite      ;
Asservissement   roueGauche      ;	


void asservissementInit()
{
	//Initialisation asservissements
	asservissementPolInit ();
	asservissementCircuInit();
	
	//Initialise les moteurs
	moteurInit ();
}

void asservissementPolInit()
{
	//Initialisation de "angle"
	angle.coefDerive                = CDA;
	angle.coefDeriveNeg             = CDA;
	angle.coefProportionnel         = CPA;
	angle.coefPropNeg               = CPA;
	angle.ordre                     = 0;
	angle.oldOrdre					= 0;
	angle.erreur					= 0;
	angle.erreurTolerance           = AT;
    angle.variation                 = 0;
	angle.variationSomme 			= 0;
	angle.enable					= TRUE;

    //Initialisation de "distance"
	distance.coefDerive             = CD;
	distance.coefDeriveNeg          = CD;
	distance.coefProportionnel      = CP;
	distance.coefPropNeg            = CP;
	distance.ordre                  = 0;
	distance.oldOrdre				= 0;
	distance.erreur					= 0;
	distance.erreurTolerance        = DT;
    distance.variation              = 0;
	distance.variationSomme 		= 0;
	distance.enable					= TRUE;
	
    //Initialisation des  valeurs max
	distance.VMax                   = VMAX;
	distance.Vmin                   = VMIN;

	angle.VMax                      = VAMAX;
	angle.Vmin                      = VAMIN;

	angle.coefAcceleration          = AA;
	distance.coefAcceleration       = DA;
}

void asservissementCircuInit()
{
	//Initialisation de la roue gauche
	roueGauche.coefDerive             = CD;
	roueGauche.coefDeriveNeg          = CD;
	roueGauche.coefProportionnel      = CP;
	roueGauche.coefPropNeg            = CP;
	roueGauche.ordre                  = 0;
	roueGauche.oldOrdre				= 0;
	roueGauche.erreur				  = 0;
	roueGauche.erreurTolerance        = DT;
    roueGauche.variation              = 0;
	roueGauche.enable				  = TRUE;

    //Initialisation de la roue droite
	roueDroite.coefDerive             = CD;
	roueDroite.coefDeriveNeg          = CD;
	roueDroite.coefProportionnel      = CP;
	roueDroite.coefPropNeg            = CP;
	roueDroite.ordre                  = 0;
	roueDroite.oldOrdre				= 0;
	roueDroite.erreur				  = 0;
	roueDroite.erreurTolerance        = DT;
    roueDroite.variation              = 0;
	roueDroite.enable				  = TRUE;
	
    //Initialisation des  valeurs max
	roueGauche.VMax                  = VMAX/2;
	roueGauche.Vmin                  = VMIN;
	roueDroite.VMax                  = VMAX/2;
	roueDroite.Vmin                  = VMIN;
	
	roueGauche.coefAcceleration		= DA;
	roueDroite.coefAcceleration		= DA;
}

//Procédure calculant la nouvelle consigne
inline void pid(Asservissement * ass, bool ralentir)
{
	//Si l'erreur est inférieure au seuil de tolérance l'ordre a été atteint
	if((ABS(ass->erreur)) < (ass->erreurTolerance) )
		ass->ordre = 0;

	//Sinon continuer d'exécuter l'ordre en cours
	else
	{
		//Calculer le nouvel ordre
		ass->ordre = ((ass->erreur *ass->coefProportionnel) / 100) + ((ass->coefDerive * ass->variation) / 100);
		
		//Seuillage
		limite(ass, ralentir);
   }
}

//Calcule le décalage par rapport à la consigne à atteindre
inline void polaire()
{
    //Variation de chaque roue depuis le dernier check
    codeurGauche.variation    = codeurGauche.newCodeur - codeurGauche.oldCodeur ;
    codeurDroit.variation     = codeurDroit.newCodeur - codeurDroit.oldCodeur   ;
	
	// Mise à niveau (à mettre en commentaire si nécessaire
	codeurDroit.variation = ((int32)(codeurDroit.variation * 101500) / 100000);
	//101430 droite,  gauche 101520
	
    //Mise a jour valeurs asservissement
    distance.variation = (codeurDroit.variation  + codeurGauche.variation);
    angle.variation    =  codeurDroit.variation - codeurGauche.variation;

	//Mettre à jour les anciennes valeurs
	codeurGauche.oldCodeur     = codeurGauche.newCodeur  ;
	codeurDroit.oldCodeur      = codeurDroit.newCodeur   ;

	//Mettre à jour l'erreur restante (donc le décalage par rapport à la consigne à atteindre)
	distance.erreur    -= distance.variation    ;
	angle.erreur       -= angle.variation       ;
	
	// Somme des variations
	angle.variationSomme += angle.variation;
	distance.variationSomme += distance.variation;
}

//Seuillage
void limite(Asservissement * ass, bool ralentir)
{
	//Variable temporaire permettant de gérer l'accélération
	int32 acceleration  = (ABS(ass->oldOrdre)+(ABS(ass->oldOrdre)*ass->coefAcceleration)/100);
	
	// Déceleration manuelle pour les ordres d'avance
	if (ralentir && (ABS(ass->erreur) < ((int32)150*IMP_M)/1000)) 
	{
		acceleration = MAX( ABS(ass->Vmin) + 150, (ABS(ass->oldOrdre)-(ABS(ass->oldOrdre))/200));
		acceleration = MIN (ABS(ass->oldOrdre)+(ABS(ass->oldOrdre)*ass->coefAcceleration)/100 , acceleration);
	}
		
	//Si la consigne n'a pas été atteinte
	if(ass->ordre != 0)
	{
	    ass->ordre = SIGN(ass->ordre) * MIN( ABS(ass->ordre), acceleration);//Limiter l'accélération

		ass->ordre = SIGN(ass->ordre) * MAX( ABS(ass->ordre), ass->Vmin );//La consigne doit être supérieur à Vmin

		ass->ordre = SIGN(ass->ordre) * MIN( ABS(ass->ordre), ass->VMax );//La consigne doit être supérieur à VMax

		ass->oldOrdre = ass->ordre;//La nouvelle consigne devient l'ancienne
	}
}

//Gestion de l'asservissement du robot
void asservissementPolaire(bool avance)
{
	//On obtiens les valeurs des codeurs
	valeurCodeurs();

	//On convertit ces valeurs en polaire (angle + distance)
	polaire();

	//Appliquer le PID	
	if (angle.enable)
	{
		if (!avance) pid(&angle, TRUE);
		else pid(&angle, FALSE);
	}
	if (distance.enable)
	{
		if (avance) pid(&distance, TRUE);
		else pid(&distance, FALSE);
	}
	
	//Envoyer la consigne au moteur
	applicationAssPosMoteurs(distance.ordre, angle.ordre);
}

void asservissementCirculaire ()
{
    //On obtiens les valeurs des codeurs
    valeurCodeurs();
	
	//On calcule la nouvelle erreur
	circulaire ();

    //Appliquer le PID
    limite(&roueGauche, FALSE);
    limite(&roueDroite, FALSE);

    //Envoyer la consigne au moteur
    applicationAssCirMoteurs(roueGauche.ordre, roueDroite.ordre);
}
		
inline void circulaire ()
{
	//Variation de chaque roue depuis le dernier check
	codeurGauche.variation    = codeurGauche.newCodeur - codeurGauche.oldCodeur ;
	codeurDroit.variation     = codeurDroit.newCodeur - codeurDroit.oldCodeur   ;

	// Mise à niveau (à mettre en commentaire si nécessaire
	if (codeurDroit.variation > 0) codeurDroit.variation = (((int32)codeurDroit.variation * 100000) / 98000);
	else codeurDroit.variation = (((int32)codeurDroit.variation * 100000) / 99999);
	
	if (codeurGauche.variation < 0) codeurGauche.variation = (((int32)codeurGauche.variation * 100000) / 100995);
	
	//Mettre à jour les anciennes valeurs pour update position
	codeurGauche.oldCodeur     = codeurGauche.newCodeur  ;
	codeurDroit.oldCodeur      = codeurDroit.newCodeur   ;
	
	// Somme des variations
	angle.variationSomme += angle.variation;
	distance.variationSomme += distance.variation;

	//Mettre à jour l'erreur restante (donc le décalage par rapport à la consigne à atteindre)
	roueGauche.erreur    -= codeurGauche.variation    ;
	roueDroite.erreur    -= codeurDroit.variation     ;
	
	//Calculer la nouvelle consigne
	if(ABS(roueGauche.erreur) > ABS(roueDroite.erreur))
	{
		roueGauche.ordre = SIGN(roueGauche.erreur)*roueGauche.VMax;
		if (SIGN(roueDroite.erreur) == team) roueDroite.ordre = SIGN(roueDroite.erreur)*(roueDroite.VMax*ABS(roueDroite.erreur)) / ABS(roueGauche.erreur); 
		else roueDroite.ordre = 0;
	}
	
	else
	{		
		roueDroite.ordre = SIGN(roueDroite.erreur)*roueDroite.VMax; 
		if (SIGN(roueGauche.erreur) == team)  roueGauche.ordre = SIGN(roueGauche.erreur)*(roueGauche.VMax*ABS(roueGauche.erreur)) / ABS(roueDroite.erreur);
		else roueGauche.ordre = 0;
	}
}			

void erreursReInit ()
{
	//Variation de chaque roue depuis le dernier check
	codeurGauche.variation    = codeurGauche.newCodeur - codeurGauche.oldCodeur ;
	codeurDroit.variation     = codeurDroit.newCodeur - codeurDroit.oldCodeur   ;

	//Mise a jour valeurs asservissement
	distance.variation = codeurDroit.variation  + codeurGauche.variation;
	angle.variation    = codeurGauche.variation - codeurDroit.variation;

	//Mettre à jour les anciennes valeurs
	codeurGauche.oldCodeur     = codeurGauche.newCodeur  ;
	codeurDroit.oldCodeur      = codeurDroit.newCodeur   ;
	
	// Somme des variations
	angle.variationSomme += angle.variation;
	distance.variationSomme += distance.variation;

	//Réinitialiser les erreurs
	distance.erreur    = 0   ;
	angle.erreur       = 0   ;
}

void erreurMemory ()
{
	//Variation de chaque roue depuis le dernier check
	codeurGauche.variation    = codeurGauche.newCodeur - codeurGauche.oldCodeur ;
	codeurDroit.variation     = codeurDroit.newCodeur - codeurDroit.oldCodeur   ;

	//Mise a jour valeurs asservissement
	distance.variation = codeurDroit.variation  + codeurGauche.variation;
	angle.variation    = codeurGauche.variation - codeurDroit.variation;

	//Mettre à jour les anciennes valeurs
	codeurGauche.oldCodeur     = codeurGauche.newCodeur  ;
	codeurDroit.oldCodeur      = codeurDroit.newCodeur   ;
	
	//Mettre à jour l'erreur restante (donc le décalage par rapport à la consigne à atteindre)
	distance.erreur    -= distance.variation    ;
	angle.erreur       -= angle.variation       ;
	
	// Somme des variations
	angle.variationSomme += angle.variation;
	distance.variationSomme += distance.variation;
}
