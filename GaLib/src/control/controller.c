#include "control/controller.h" 

#include "control/motors.h"
#include "debug/log.h"
#include "tools/math.h"
#include "io/adc.h"

/// Local variables
Controller controller;
                                             // Left to right
int sharpFrontChannels[] = {14, 13, 12, 10}; // SH5 SH4 Up
                                             // SH3 SH1 Down
int sharpBackChannels[] = {15, 11};          // SH6 SH2
int sharpFrontThreshold[] = {150, 150, 2000, 2000};
int sharpBackThreshold[] = {400, 400};
bool sharpFrontDisable = false;
bool sharpBackDisable = false;

/// Local functions prototypes
bool controllerUpdatePositionControl(float error_length, float error_angle);
bool controllerUpdateSpeedControl(float error_length, float error_angle);
bool controllerUpdateBraking(float error_length, float error_angle);
bool controllerUpdateCalibration(float error_length, float error_angle);

bool checkForEnnemy(float error_length, float error_angle) {
    int i;
    if(!sharpFrontDisable && error_length > 0.01f) {
        for(i = 0; i < sizeof(sharpFrontChannels)/sizeof(int); ++i) {
            if(adcGetChannel(sharpFrontChannels[i]) > sharpFrontThreshold[i]) {
                return true;
            }
        }
    }
    else if(!sharpBackDisable && error_length < 0.01f) {
        for(i = 0; i < sizeof(sharpBackChannels)/sizeof(int); ++i) {
            if(adcGetChannel(sharpBackChannels[i]) > sharpBackThreshold[i]) {
                return true;
            }
        }
    }
    return false;
}

/// Function definitions
void controllerUpdate(float error_length, float error_angle) {
    bool done = false;
    while (!done) {
        switch (controller.state) {
            case CS_PositionControl:
                done = controllerUpdatePositionControl(error_length, error_angle);
                break;
            case CS_SpeedControl:
                done = controllerUpdateSpeedControl(error_length, error_angle);
                break;
            case CS_Braking:
                done = controllerUpdateBraking(error_length, error_angle);
                break;
            case CS_Calibration:
                done = controllerUpdateCalibration(error_length, error_angle);
                break;
            default:
                logString("Error: invalid state in controller. Switching to Position Control!\n");
                controllerChangeState(CS_PositionControl);
                break;
        }
    }
    motorsApplyOrder(controller.order_length, controller.order_angle);
}

bool controllerUpdatePositionControl(float error_length, float error_angle) {
    // If far away from the objective, switch to speed control
    if(false) {// (ABS(error_length) > controller.threshold_lenght) {
        controllerChangeState(CS_SpeedControl);
        return false;
    }
    if(checkForEnnemy(error_length, error_angle)) {
        controllerChangeState(CS_Braking);
        return false;
    }
    // Initialise if we have to
    if (!controller.state_initialisation_done) {
        motorsUnbrake();
        controller.pid_length.accumulator = 0;
        controller.pid_length.last_error = error_length;
        controller.pid_angle.accumulator = 0;
        controller.pid_angle.last_error = error_angle;
        controller.state_initialisation_done = true;
        coef_angle = 0.3f;
    }
    controller.order_length = pidGetOrder(&controller.pid_length, error_length);
    controller.order_angle = pidGetOrder(&controller.pid_angle, error_angle);
    //logStringFormatted("Length {e: %f -> o: %f} / Angle {e: %f -> o: %f}\n", error_length, controller.order_length, error_angle, controller.order_angle);
    return true;
}

bool controllerUpdateSpeedControl(float error_length, float error_angle) {
    // If far close to the objective, switch to position
    if (ABS(error_length) < controller.threshold_length) {
        controllerChangeState(CS_PositionControl);
        return false;
    }
    if(checkForEnnemy(error_length, error_angle)) {
        controllerChangeState(CS_Braking);
        return false;
    }
    // Initialise if we have to
    if (!controller.state_initialisation_done) {
        motorsUnbrake();
        controller.pid_speed.accumulator = 0;
        controller.pid_speed.last_error = 0; // TODO: how to get this safely ?
        controller.pid_length.last_error = error_length; // used to calculate last speed
        controller.pid_angle.accumulator = 0;
        controller.pid_angle.last_error = error_angle;
        controller.state_initialisation_done = true;
        coef_angle = 0.3f;
    }
    controller.order_length = pidGetOrder(&controller.pid_speed, controller.speed_max_order - (controller.pid_length.last_error - error_length)); // TODO: normalize with time ?
    controller.pid_length.last_error = error_length;
    controller.order_angle = pidGetOrder(&controller.pid_angle, error_angle);
    return true;
}

bool controllerUpdateBraking(float error_length, float error_angle) {
    // Initialise if we have to
    if (!controller.state_initialisation_done) {
        motorsBrake();
        controller.state_initialisation_done = true;
        coef_angle = 0.3f;
    }
    if(!checkForEnnemy(error_length, error_angle)) {
        controllerChangeState(CS_PositionControl);
        return false;
    }
    controller.order_length = 0.f;
    controller.order_angle = 0.f;
    return true;
}

bool controllerUpdateCalibration(float error_length, float error_angle) {
    // Initialise if we have to
    if (!controller.state_initialisation_done) {
        motorsUnbrake();
        controller.pid_length.accumulator = 0.f;
        controller.pid_length.last_error = error_length;
        controller.state_initialisation_done = true;
        coef_angle = 0.0f;
    }
    controller.order_length = controller.calibration_order;
    controller.order_angle = 0.f;
    return true;
}

void controllerChangeState(ControllerState state) {
    controller.state = state;
    controller.state_initialisation_done = false;
    logString("Controller: state changed to ");
    switch (controller.state) {
        case CS_PositionControl:
            logString("Position Control\n");
            break;
        case CS_SpeedControl:
            logString("Speed Control\n");
            break;
        case CS_Braking:
            logString("Braking\n");
            break;
        case CS_Calibration:
            logString("Calibration\n");
            break;
        default:
            logString("Invalid State\n");
            break;
    }
}
