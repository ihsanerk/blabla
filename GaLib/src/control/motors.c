#include "control/motors.h"

#include <xc.h>

#include "tools/math.h"
#include "debug/log.h"

uint16_t pwm_max, pwm_min;
float coef_angle;

// Pins
bitPtr motors_dir_r;
bitPtr motors_dir_l;
bitPtr motors_brake_r;
bitPtr motors_brake_l;
regPtr motors_pwm_r;
regPtr motors_pwm_l;
bitPtr motors_dir_l_tris;
bitPtr motors_dir_r_tris;
bitPtr motors_brake_l_tris;
bitPtr motors_brake_r_tris;
bitPtr motors_pwm_l_tris;
bitPtr motors_pwm_r_tris;
unsigned int motors_PTP;

// Global variables

void motorsInit() {
    // Configure pins in output
    bitSet(motors_dir_r_tris, 0);
    bitSet(motors_dir_l_tris, 0);
    bitSet(motors_brake_r_tris, 0);
    bitSet(motors_brake_l_tris, 0);
    bitSet(motors_pwm_r_tris, 0);
    bitSet(motors_pwm_l_tris, 0);

    // Init braking
    motorsUnbrake();

    // PTCON & PTPER
    PTCON = 0x0000; // Free Running, no pre/postscale
    PTPER = motors_PTP; // PWM frequency (1600 => Fpwm = 20kHz)

    // PWCON6
    PWMCON6bits.FLTIEN = 0;
    PWMCON6bits.CLIEN = 0;
    PWMCON6bits.TRGIEN = 0;
    PWMCON6bits.ITB = 0;
    PWMCON6bits.MDCS = 0;
    PWMCON6bits.DTC = 0b10;
    PWMCON6bits.MTBS = 0;
    PWMCON6bits.XPRES = 0;
    PWMCON6bits.IUE = 0;

    // PWCON4
    PWMCON4bits.IUE = 1; // Immediate update of PWM enabled

    // IOCON6
    IOCON6bits.PENH = 1;
    IOCON6bits.PENL = 0;
    IOCON6bits.POLH = 0;
    IOCON6bits.PMOD = 0b11;
    IOCON6bits.OVRENL = 0;
    IOCON6bits.SWAP = 0;
    IOCON6bits.OSYNC = 1;

    // IOCON4
    IOCON4bits.PENH = 1;
    IOCON4bits.PENL = 0;
    IOCON4bits.POLH = 0;
    IOCON4bits.PMOD = 0b11;
    IOCON4bits.OVRENL = 0;
    IOCON4bits.SWAP = 0;
    IOCON4bits.OSYNC = 1;

    // PWM duty cycle initialisation
    *motors_pwm_l = 0;
    *motors_pwm_r = 0;
    bitSet(motors_dir_l, 0);
    bitSet(motors_dir_r, 0);

    // Enable PWM
    PTCONbits.PTEN = 1;
}

void motorsFreeRunning(void) {
    motorsUnbrake();
    // Disable PWM
    *motors_pwm_l = 0;
    *motors_pwm_r = 0;
}

void motorsApplyOrder(float order_lenght, float order_angle) {
    // Motors orders
    float order_left = (1.f - coef_angle) * order_lenght - coef_angle * order_angle;
    float order_right = (1.f - coef_angle) * order_lenght + coef_angle * order_angle;

    int16_t pwm_left_abs, pwm_right_abs;
    // PWM values
    if(order_left != 0.0f)
        pwm_left_abs = (pwm_max - pwm_min) * ABS(order_left) + pwm_min;
    else
        pwm_left_abs = 0;
    if(order_right != 0)
        pwm_right_abs = (pwm_max - pwm_min) * ABS(order_right) + pwm_min;
    else
        pwm_right_abs = 0;

    // Directions
    bool pwm_left_dir = DIRECTION(-1.0f * order_left);
    bool pwm_right_dir = DIRECTION(order_right);
    bitSet(motors_dir_l, pwm_left_dir);
    bitSet(motors_dir_r, pwm_right_dir);

    // Absolute values
    *motors_pwm_l = ABS(pwm_left_abs);
    *motors_pwm_r = ABS(pwm_right_abs);

//    logStringFormatted("Left o:%f, p:%d / Right o:%f, p:%d\n", order_left, pwm_left_abs, order_right, pwm_right_abs);
}

void motorsBrake() {
    bitSet(motors_brake_l, 1);
    bitSet(motors_brake_r, 1);
}

void motorsUnbrake() {
    bitSet(motors_brake_l, 0);
    bitSet(motors_brake_r, 0);
}
