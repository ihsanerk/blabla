#ifndef _COEF_H
#define _COEF_H

//Constantes
#define CPA         20			//Coefficient proportionel pour l'angle 
#define CDA        	-300		//Coefficient d�riv� pour l'angle				
#define AT          100			//Angle tol�rance 							
#define AA          10			//Angle acc�l�ration 	

#define CP          20			//Coefficient proportionel					
#define CD          -595		//Coefficient d�riv�						
#define DT          100			//Distance tol�rance 
#define DA          10			//Distance acc�l�ration

#define VAMAX       1000		//Vitesse angulaire maximale (max physique 1600) 
#define VAMIN       300			//Vitesse angulaire minimale 

#define VMAX       	800			//Vitesse maximale (max physique 1600)
#define VMIN        250			//Vitesse minimale			

#define IMP_M       204805		//Impulsions par metre : moiti� du r�el (test� sur 1M20 pour 3mm)
#define IMP_T       217237		//Impulsions par tour (pr�cis jusqu'� 100 tours, 3d d'erreur) pas assez

#endif
