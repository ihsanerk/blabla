#include "control/pid.h"

float pidGetOrder(PID *pid, float error) {
    float order;
    pid->accumulator += error;
    order = error * pid->param_P + (pid->last_error - error) * pid->param_D + pid->accumulator * pid->param_I;
    pid->last_error = error;
    if (order > 1.0f)
        order = 1.0f;
    else if (order < -1.0f)
        order = -1.0f;
    return order;
}
