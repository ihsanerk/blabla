#ifndef _COEF_H
#define _COEF_H

//Constantes
#define CPA         20			//Coefficient proportionel pour l'angle 
#define CDA        	-300		//Coefficient dérivé pour l'angle				
#define AT          100			//Angle tolérance 							
#define AA          10			//Angle accélération 	

#define CP          20			//Coefficient proportionel					
#define CD          -595		//Coefficient dérivé						
#define DT          100			//Distance tolérance 
#define DA          10			//Distance accélération

#define VAMAX       1000		//Vitesse angulaire maximale (max physique 1600) 
#define VAMIN       300			//Vitesse angulaire minimale 

#define VMAX       	800			//Vitesse maximale (max physique 1600)
#define VMIN        250			//Vitesse minimale			

#define IMP_M       204805		//Impulsions par metre : moitié du réel (testé sur 1M20 pour 3mm)
#define IMP_T       217237		//Impulsions par tour (précis jusqu'à 100 tours, 3d d'erreur) pas assez

#endif
