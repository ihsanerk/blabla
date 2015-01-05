#ifndef PWM_H
#define PWM_H

#include "bits.h"

// 50Hz PWM to control up to 8 HS-311 servomotors
// (Uses Timer 4)

void pwmInit();
void pwmStop();
void pwmSet(unsigned char servo, unsigned int degree);

// Configuration
#define PWM_MAX 8
extern bitPtr pwm_bits[PWM_MAX];
extern bitPtr pwm_tris[PWM_MAX];
extern bool pwm_enable[PWM_MAX];

#endif // PWM_H
