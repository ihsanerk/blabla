#include "pid.h"

float pidGetOrder(PID *pid, float error) {
    //Ressources
    float order;

    //On additionne les erreurs
    pid->accumulator += error;

    //Si l'erreur est supérieur au seuil de tolérance
    if(ABS(error)<ABS(100))
    {
        order=0;
    }
    else
    {
        order = error * pid->param_P + (pid->last_error - error) * pid->param_D + pid->accumulator * pid->param_I;
        pid->last_error = error;

    }
    //Si on dépasse la valeur maximum de l'ordre
    if (order > 1.0f)  order = 1.0f;
    if (order < -1.0f) order = -1.0f;

    return order;
}
