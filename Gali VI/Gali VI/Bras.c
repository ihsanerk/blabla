// Library
#include "Bras.h"

//	Variables

//	Fonctions
void brasInit ()
{
	//Atteindre la position initiale des 2 bras
	brasOuverture ();
	delay_ms(500);
	brasFermeture ();
}

void brasOuverture ()
{
	ax12Execute (BRAS_BAS_SEMI_RANGE, 5, TRUE);
	delay_ms(500);
	ax12Execute (BRAS_HAUT_LEVE, 4, TRUE);
	delay_ms(500);
	ax12Execute (BRAS_BAS_LEVE, 5, TRUE);
}

void brasFermeture ()
{
	ax12Execute (BRAS_BAS_SEMI_RANGE, 5, TRUE);
	delay_ms(500);
	ax12Execute (BRAS_HAUT_RANGE, 4, TRUE);
	delay_ms(500);
	ax12Execute (BRAS_BAS_RANGE, 5, TRUE);
}

void brasBaisses ()
{
	ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
	ax12Execute (BRAS_HAUT_BAISSE, 4, TRUE);
	delay_ms (1000);
}

void brasProcess (int32 droite, int32 gauche)
{
	if (millis%400 < 200)
	{
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		ax12Execute (BRAS_HAUT_LEVE, 4, TRUE);
	}
	else 
	{
		ax12Execute (BRAS_BAS_LEVE, 5, TRUE);
		ax12Execute (BRAS_HAUT_BAISSE, 4, TRUE);
	}
		
	// Bras du bas
	// Si on est dans la zone d'une de nos bougies
	/*if ( (droite == 1000) && (gauche == 1000) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -205750 ) && (gauche > - 138935) && (droite < -194626 ) && (gauche > -132696) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -191901 ) && (gauche > -129022) && (droite < -185901 ) && (gauche > -123022) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -162693 ) && (gauche > - 112391) && (droite < -156693 ) && (gauche > -106391) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -142459 ) && (gauche > - 99968) && (droite < -136459 ) && (gauche > -99368) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -124303 ) && (gauche > - 88490) && (droite < -118303 ) && (gauche > -82490) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -97559 ) && (gauche > - 73336) && (droite < -91559 ) && (gauche > -67336) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -69092 ) && (gauche > - 57337) && (droite < -63092 ) && (gauche > -51337) ) 
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -205750 ) && (gauche > - 55542) && (droite < -194626 ) && (gauche > -49542) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -36855 ) && (gauche > - 33644) && (droite < -30855 ) && (gauche > -27644) ) 
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
		
	else if ( (droite > -16251 ) && (gauche > - 17456) && (droite < -10251 ) && (gauche > -11456) )
		ax12Execute (BRAS_BAS_BAISSE, 5, TRUE);
	
	// Sinon relever le bras
	else ax12Execute (BRAS_BAS_LEVE, 5, TRUE);
	
	// Bras du haut
	// Si on est dans la zone d'une de nos bougies
	if  ( (droite > -191901 ) && (gauche > - 129022) && (droite < -185901 ) && (gauche > -123022) )
		ax12Execute (BRAS_HAUT_BAISSE, 4, TRUE);
			
	else if  ( (droite > -162693 ) && (gauche > - 112391) && (droite < -156693 ) && (gauche > -106391) )
		ax12Execute (BRAS_HAUT_BAISSE, 4, TRUE);
		
	else if  ( (droite > -124303 ) && (gauche > - 88490) && (droite < -118303 ) && (gauche > -82490) )
		ax12Execute (BRAS_HAUT_BAISSE, 4, TRUE);
		
	else if  ( (droite > -81430 ) && (gauche > - 64770) && (droite < -75430 ) && (gauche > -58770) )
		ax12Execute (BRAS_HAUT_BAISSE, 4, TRUE);
		
	else if  ( (droite > -55542 ) && (gauche > - 47347) && (droite < -49542 ) && (gauche > -41347) ) 
		ax12Execute (BRAS_HAUT_BAISSE, 4, TRUE);
		
	else if  ( (droite > -36855 ) && (gauche > - 33644) && (droite < -30855 ) && (gauche > -27644) )
		ax12Execute (BRAS_HAUT_BAISSE, 4, TRUE);

	// Sinon relever le bras
	else ax12Execute (BRAS_HAUT_LEVE, 4, TRUE);*/
}

