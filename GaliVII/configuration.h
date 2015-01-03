#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// Microcontroller MIPs (FCY)
#define FXTAL   8000000
#define PLL     8
#define FOSC    ((FXTAL)*(PLL))
#define FCY     ((FOSC)/(2)) //	32000000

#define BAUD 9600
#define FINAL_BAUD (((FCY/16)/BAUD)-1)

#define PWMPRE		1
#define FPWM		20000
#define PTP     (FOSC / (FPWM * PWMPRE));

#define LOG_XBEE

#include <stdint.h>

// Prototypes
void pinConfigure();
void oscillatorInit();
void timersInit();
void timerStart();
void timerStop();
void configurationInit();
void configurationReload();
void configurationSave();

enum conf {
    CONF_OK,
    MOTOR_PID_LENGTH_P,
    MOTOR_PID_LENGTH_I,
    MOTOR_PID_LENGTH_D,
    MOTOR_PID_ANGLE_P,
    MOTOR_PID_ANGLE_I,
    MOTOR_PID_ANGLE_D,
    MOTOR_PID_SPEED_P,
    MOTOR_PID_SPEED_I,
    MOTOR_PID_SPEED_D,
    ENCODER_LEFT_MPT,
    ENCODER_LEFT_RPT,
    ENCODER_RIGHT_MPT,
    ENCODER_RIGHT_RPT,
    CONF_N
};
typedef enum conf conf;

#define CONF_OK_VALUE (1.337f)

#endif // CONFIGURATION_H