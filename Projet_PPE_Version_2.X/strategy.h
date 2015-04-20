/* 
 * File:   strategy.h
 * Author: user
 *
 * Created on 20 avril 2015, 14:52
 */

#ifndef STRATEGY_H
#define	STRATEGY_H


#include "math.h"
#include "debugger.h"
#include "DetectionSharp.h"

#define MAXACTION 14
#define INFINI 998

int allselected(int *selected);
int* shortpath(int cost[][MAXACTION],int *preced,int *distance);
void strategy();

#endif	/* STRATEGY_H */

