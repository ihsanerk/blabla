#include "configuration.h"

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#include "../GaLib/include/control/controller.h"
#include "../GaLib/include/control/motors.h"
#include "../GaLib/include/control/encoders.h"
#include "../GaLib/include/debug/leds.h"
#include "../GaLib/include/debug/log.h"
#include "../GaLib/include/io/adc.h"
#include "../GaLib/include/io/config_flash.h"
#include "../GaLib/include/io/pwm.h"
#include "../GaLib/include/io/bus.h"
#include "../GaLib/include/io/dxl_hal.h"

unsigned long long int conf_fcy;

void pinConfigure() {
    // Disable ADC
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELG = 0;

    // Encoders (right:E1, left:E2)
    RPINR14bits.QEA1R = 81;
    RPINR14bits.QEB1R = 126;
    RPINR16bits.QEA2R = 124;
    RPINR16bits.QEB2R = 125;

    // Motors (right:M2, left:M1)
    bitInit(&motors_dir_l, &LATC, 3);
    bitInit(&motors_dir_r, &LATE, 6);
    bitInit(&motors_brake_l, &LATC, 2);
    bitInit(&motors_brake_r, &LATE, 5);
    motors_pwm_l = &PDC6;
    motors_pwm_r = &PDC4;
    bitInit(&motors_dir_l_tris, &TRISC, 3);
    bitInit(&motors_dir_r_tris, &TRISE, 6);
    bitInit(&motors_brake_l_tris, &TRISC, 2);
    bitInit(&motors_brake_r_tris, &TRISE, 5);
    bitInit(&motors_pwm_l_tris, &TRISC, 4);
    bitInit(&motors_pwm_r_tris, &TRISE, 7);

    // Leds
    bitInit(&led0, &LATD, 6);
    bitInit(&led1, &LATD, 5);
    bitInit(&led2, &LATD, 4);
    bitInit(&led3, &LATD, 13);
    bitInit(&led4, &LATD, 12);
    bitInit(&led5, &LATD, 3);
    bitInit(&led6, &LATD, 2);
    bitInit(&led7, &LATD, 1);
    bitInit(&led0_tris, &TRISD, 6);
    bitInit(&led1_tris, &TRISD, 5);
    bitInit(&led2_tris, &TRISD, 4);
    bitInit(&led3_tris, &TRISD, 13);
    bitInit(&led4_tris, &TRISD, 12);
    bitInit(&led5_tris, &TRISD, 3);
    bitInit(&led6_tris, &TRISD, 2);
    bitInit(&led7_tris, &TRISD, 1);

    // SPI1
//    RPINR20bits.SDI1R = 100; // MOSI
//    RPINR20bits.SCK1R = 79; // CLK
//    RPINR21bits.SS1R = 36; // SS
//    RPOR9bits.RP101R = 5; // MISO

    // UART1: RS-485 Bus
    RPINR18bits.U1RXR = 109; // Rx
    RPOR11bits.RP108R = 1; // Tx
    bitInit(&bus_txen_tris, &LATA, 1);
    bitInit(&bus_txen_tris, &TRISA, 1);

    // UART2: AX-12 & MX-28
    RPINR19bits.U2RXR = 98; // RX
    RPOR8bits.RP99R = 3; // TX
    bitInit(&dxl_txen, &PORTD, 11);
    bitInit(&dxl_rxen, &PORTD, 0);
    bitInit(&dxl_txen_tris, &TRISD, 11);
    bitInit(&dxl_rxen_tris, &TRISD, 0);

    // UART3: Log
    RPINR27bits.U3RXR = 62;
    RPOR15bits.RP127R = 27; // Remapped to PIN1

    // UART4: Turret
    
    // Switches: Start RD7 & Color RF0
    TRISDbits.TRISD7 = 1;
    TRISFbits.TRISF0 = 1;

    // µSwitches: RF8 (SW11), RA10 (SW21), RA9 (SW22), RB8 (SW23), RB9 (SW24)
    //            RB1 (SW31), RB0 (SW51), RA0 (SW61), RE8 (SW62)
    TRISFbits.TRISF8 = 1;
    TRISAbits.TRISA10 = 1;
    TRISAbits.TRISA9 = 1;
    TRISBbits.TRISB8 = 1;
    TRISBbits.TRISB9 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB0 = 1;
    TRISAbits.TRISA0 = 1;
    TRISEbits.TRISE8 = 1;

    // Strategy Switches: RA6, RG0, RG1, RF1
    TRISAbits.TRISA6 = 1;
    TRISGbits.TRISG0 = 1;
    TRISGbits.TRISG1 = 1;
    TRISFbits.TRISF1 = 1;

    // Jack: RF8
    TRISFbits.TRISF8 = 1;

    // Servo PWM: RA5, RA4, RA3, RA2
    //  S3 S4
    //  S5 ??
    int i;
    for(i = 0; i < 4; ++i) {
//        bitInit(&pwm_bits[i], &LATA, 5 - i);
//        bitInit(&pwm_tris[i], &TRISA, 5 - i);
//        pwm_enable[i] = false; // TODO: re-enable if needed
//        pwmSet(i, 90);
    }
    // Throwers: RA14, RA15 (Right, Left) (S8, S7)
    bitInit(&pwm_bits[4], &LATA, 14);
    bitInit(&pwm_tris[4], &TRISA, 14);
    pwm_enable[4] = true;
    pwmSet(4, 45);
    bitInit(&pwm_bits[5], &LATA, 15);
    bitInit(&pwm_tris[5], &TRISA, 15);
    pwm_enable[5] = true;
    pwmSet(5, 30); // 45

    // Sharp ADC: AN10 -> AN15 (RB10 -> RB15) 
    for(i = 10; i <= 15; ++i) {
        adc_enable[i] = true;
        // TODO: check if TRIS is needed for ADC pins
        ANSELB |= (1 << i);
    }
    
    // Motor ADC: AN5 (RB5), AN21 (RE9)
    adc_enable[5] = true;
    adc_enable[21] = true;
    ANSELB |= (1 << 5);
    ANSELE |= (1 << 9);
}

void oscillatorInit() {
    // The settings below set up the oscillator and PLL for 40 MIPS as
    // follows:
    //               Crystal Frequency * (PLLFBD+2)
    //       Fcy =  ----------------------------
    //                       2 * N1 * N2

    PLLFBD = 30; // PLLDIV = 38, M  = 40
    CLKDIVbits.PLLPOST = 0; // PLLPOST = 0, N1 =  2
    CLKDIVbits.PLLPRE = 0; // PLLPRE  = 0, N2 =  2
    CLKDIVbits.DOZEN = 0; // Fcy = Fosc/2
    OSCCONbits.CLKLOCK = 0; // Enable clock settings to change
    OSCCONbits.LPOSCEN = 0; // Disable secondary oscillator

    OSCCONbits.NOSC = 0b011; // New config XT PLL
    OSCCONbits.OSWEN = 1; // Activate new config

    conf_fcy = FCY;
    
    // WARNING : infinite loop !
    while (OSCCONbits.COSC != 0b011)
        ; // Wait until config is set
}

void timersInit() {
    // --- Timer 3 : Control frequency ---
    T3CONbits.TON = 0; // Disable timer
    T3CONbits.TCKPS = 0b01; // Prescaler : 8
    T3CONbits.TCS = 0; // Internal clock
    T3CONbits.TGATE = 0; // Timer mode
    TMR3 = 0x00; // Clear Timer register
    PR3 = 4000; // 1000Hz

    IPC2bits.T3IP = 0b101; // Priority : 5

    // --- Timers 6 et 7 (32 bits) : Stop at 90s ---
    /*
            PRESCALER 256
            FOVERFLOW 0.011111111 Hz (90 secondes)
            FCY 32 000 000
            PR	11 250 000 ( 1010 1011 1010 1001 0101 0000 )
     */
    T6CONbits.TON = 0; // Disable timer
    T7CONbits.TON = 0; // Disable timer

    // Timer 6
    T6CONbits.TCKPS = 0b11; // Prescaler : 256
    T6CONbits.T32 = 1; // 32 bits
    T6CONbits.TCS = 0; // Internal clock
    T6CONbits.TGATE = 0; // Timer mode
    TMR6 = 0x00; // Clear Timer register
    PR6 = 43344; // Period value (LSB) 1010 1001 0101 0000

    // Timer 7
    T7CONbits.TCS = 0; // Internal clock
    T7CONbits.TGATE = 0; // Timer mode
    TMR7 = 0x00; // Clear Timer register
    PR7 = 171; // Period value (MSB) 1010 1011

    // Interruption
    _T7IP = 0b111; // Priority : 7 (Highest)
}

void timerStart() {
    IEC0bits.T3IE = 1; // Enable interrupt
    T3CONbits.TON = 1; // Enable timer 2
    IFS0bits.T3IF = 0; // Clear flag
}

void timerStop() {
    IEC0bits.T3IE = 0; // Disable interrupt
    T3CONbits.TON = 0; // Disable timer 2
    IFS0bits.T3IF = 0; // Clear flag
}

union void32_t {
    uint32_t u;
    int32_t i;
    float f;
};
typedef union void32_t void32_t;

void configurationInit() {
    // Try to load previous configuration in flash, or else set to default
    configInit();
    if (!configuration[CONF_OK]) {
        configuration[MOTOR_PID_LENGTH_P] = 15.0f;
        configuration[MOTOR_PID_LENGTH_I] = 0.f;
        configuration[MOTOR_PID_LENGTH_D] = 0.f;
        configuration[MOTOR_PID_ANGLE_P] = 5.0f;
        configuration[MOTOR_PID_ANGLE_I] = 0.f;
        configuration[MOTOR_PID_ANGLE_D] = 0.f;
        configuration[MOTOR_PID_SPEED_P] = 0.f;
        configuration[MOTOR_PID_SPEED_I] = 0.f;
        configuration[MOTOR_PID_SPEED_D] = 0.f;
        configuration[CONF_OK] = CONF_OK_VALUE;
        configSaveToFlash();
    }

    /// Initialisation
    // Controller
    Controller controller_conf = {0};
    controller_conf.state = CS_PositionControl;
    controller_conf.state_initialisation_done = false;
    controller_conf.threshold_length = 30.f;
    controller_conf.calibration_order = -0.4f;
    controller_conf.speed_max_order = 1.f;

    controller = controller_conf;

    // Motors
    motors_PTP = PTP;
    pwm_max = 3000;
    // Minimum pwm for the robot to stay still at equilibrium with low P parameter
    pwm_min = 250;
    coef_angle = 0.3f;

    // Encoders
    const Encoder encoder_right_conf = {0, 0, 0, 0.817e-5f, 0.840e-4f};
    const Encoder encoder_left_conf = {0, 0, 0, 0.817e-5f, 0.840e-4f}; // 0.9963872e-4f
    encoder_right = encoder_right_conf;
    encoder_left = encoder_left_conf;

    configurationReload();
}

void configurationReload() {
    // Load parameters
    controller.pid_length.param_P = configuration[MOTOR_PID_LENGTH_P];
    controller.pid_length.param_I = configuration[MOTOR_PID_LENGTH_I];
    controller.pid_length.param_D = configuration[MOTOR_PID_LENGTH_D];
    controller.pid_angle.param_P = configuration[MOTOR_PID_ANGLE_P];
    controller.pid_angle.param_I = configuration[MOTOR_PID_ANGLE_I];
    controller.pid_angle.param_D = configuration[MOTOR_PID_ANGLE_D];
    controller.pid_speed.param_P = configuration[MOTOR_PID_SPEED_P];
    controller.pid_speed.param_I = configuration[MOTOR_PID_SPEED_I];
    controller.pid_speed.param_D = configuration[MOTOR_PID_SPEED_D];
}

void configurationSave() {
    configuration[MOTOR_PID_LENGTH_P] = controller.pid_length.param_P;
    configuration[MOTOR_PID_LENGTH_I] = controller.pid_length.param_I;
    configuration[MOTOR_PID_LENGTH_D] = controller.pid_length.param_D;
    configuration[MOTOR_PID_ANGLE_P] = controller.pid_angle.param_P;
    configuration[MOTOR_PID_ANGLE_I] = controller.pid_angle.param_I;
    configuration[MOTOR_PID_ANGLE_D] = controller.pid_angle.param_D;
    configuration[MOTOR_PID_SPEED_P] = controller.pid_speed.param_P;
    configuration[MOTOR_PID_SPEED_I] = controller.pid_speed.param_I;
    configuration[MOTOR_PID_SPEED_D] = controller.pid_speed.param_D;
    configuration[CONF_OK] = CONF_OK_VALUE;
    configSaveToFlash();
}
