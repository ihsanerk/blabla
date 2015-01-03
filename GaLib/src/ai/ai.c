#include "../../include/ai/ai.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <xc.h>

#include "tools/math.h"
#include "tracking/tracker.h"
#include "io/pwm.h"
#include "debug/log.h"
#include "io/bus.h"
#include "control/controller.h"
#include "tools/timeout.h"
#include "io/adc.h"


//#define NO_AI_DEBUG



// Types


bool team_is_yellow;

ai_plan_t aiPlanStartingPlacement();
float normalizeAngle(float angle);
ai_plan_t aiPlanStartingPlacementRed();

// Global variables
static bool ai_state_current_is_initialized;
static ai_state_t *ai_state_current = NULL;

ai_state_t* aiStateLoopEnter(ai_state_t *this) {
    ai_data_counter *data = (ai_data_counter*) this->data;
    data->value = 0;
    return NULL;
}

ai_state_t* aiStateSetAngleAbsoluteEnter(ai_state_t *this) {
    isAngleAbsolute = true;
    return NULL;
}

ai_state_t* aiStateSetAngleRelativeEnter(ai_state_t *this) {
    isAngleAbsolute = false;
    return NULL;
}

ai_state_t* aiStateLoopUpdate(ai_state_t *this) {
    ai_data_counter *data = (ai_data_counter*) this->data;
    data->value++;
    if(data->value == data->n) {
        data->value = 0;
        return this->next_on_success;
    }
    else {
        return this->next_on_failure;
    }
}

ai_state_t* aiStateLoop(unsigned int n) {
    ai_state_t *s = aiNewState();
    s->enter = &aiStateLoopEnter;
    s->update = &aiStateLoopUpdate;
    ai_data_counter *data = (ai_data_counter*) malloc(sizeof(ai_data_counter));
    data->n = n;
    s->data = (void*) data;
    return s;
}

// Dummy Update function
ai_state_t* aiStateDummyUpdate(ai_state_t *this) {
    return this->next_on_success;
}

bool ai_button_pushed = false;
ai_state_t* aiStateWaitButtonUpdate(ai_state_t *this) {
    if(ai_button_pushed) {
        ai_button_pushed = false;
        return this->next_on_success;
    }
    else {
        return NULL;
    }
}

ai_state_t* aiStateWaitForJackUpdate(ai_state_t *this) {
    if(PORTFbits.RF8) {
        IEC0bits.T3IE = 1; // Enable interrupt
        T3CONbits.TON = 1; // Enable timer 2
        IFS0bits.T3IF = 0; // Clear flag

        IEC3bits.T7IE = 1;
        T6CONbits.TON = 1;
        IFS3bits.T7IF = 0;
        return this->next_on_success;
    }
    else {
        return NULL;
    }
}

ai_state_t* aiStateLogPositionExit(ai_state_t *this) {
    trackerLogPosition();
    return NULL;
}

// Create and destroy States
ai_state_t* aiNewState(void) {
    ai_state_t *state = (ai_state_t*) malloc(sizeof(ai_state_t));
    state->enter = NULL;
    state->update = &aiStateDummyUpdate; // By default, return next_on_success
    state->exit = NULL;
    state->next_on_success = NULL;
    state->next_on_failure = NULL;
    state->name = NULL;
    state->data = NULL;
    return state;
}

void aiDeleteState(ai_state_t *state) {
    free(state);
}

typedef enum {
    HOLD, THROW1, THROW3
} ai_throwspear_pos_t;
typedef struct {
    bool left;
    ai_throwspear_pos_t pos;
} ai_data_throwspear_t;

ai_state_t* aiStateThrowSpearEnter(ai_state_t *this) {
    ai_data_throwspear_t *data = (ai_data_throwspear_t*) this->data;
    if(data->left) {
        switch(data->pos) {
            case HOLD:
                pwmSet(5, 30); // 45
                break;
            case THROW1:
                pwmSet(5, 28);
                break;
            case THROW3:
                pwmSet(5, 64);
                break;
        }
    }
    else {
        switch(data->pos) {
            case HOLD:
                pwmSet(4, 45);
                break;
            case THROW1:
                pwmSet(4, 62);
                break;
            case THROW3:
                pwmSet(4, 28);
                break;
        }
    }
    return NULL;
}

ai_state_t* aiStateThrowSpear(bool left, ai_throwspear_pos_t pos) {
    ai_data_throwspear_t *data = malloc(sizeof(ai_data_throwspear_t));
    data->left = left;
    data->pos = pos;
    
    ai_state_t *s = aiNewState();
    s->data = data;
    s->enter = &aiStateThrowSpearEnter;

    return s;
}

ai_state_t* aiStateSendPacketEnter(ai_state_t *this) {
    bus_packet_t *packet = (bus_packet_t*) this->data;
    logStringFormatted("Packet: %u, %u, %u, %u\n", packet->address, packet->action, packet->param1, packet->param2);
    busSentPacket(packet);
    return NULL;
}

ai_state_t* aiStateSendPacket(uint8_t address, uint8_t action, uint8_t param1, uint8_t param2) {
    ai_state_t* state = aiNewState();

    bus_packet_t *packet = (bus_packet_t*) malloc(sizeof(bus_packet_t));
    packet->address = address;
    packet->action = action;
    packet->param1 = param1;
    packet->param2 = param2;
    state->data = packet;
    state->enter = &aiStateSendPacketEnter;

    return state;
}

ai_state_t* aiStatePoserFrequeEnter(ai_state_t *this) {
    controllerChangeState(CS_Calibration);
    timeoutSet(0x3D, 0x0900);
    return NULL;
}

ai_state_t* aiStatePoserFrequeUpdate(ai_state_t *this) {
    if(timeoutCheck()) {
        // Go forward
        controllerChangeState(CS_PositionControl);
        return this->next_on_success;
    }
    return NULL;
}

ai_state_t* aiStatePoserFreque(void) {
    ai_state_t* state;
    state = aiNewState();
    state->enter = &aiStatePoserFrequeEnter;
    state->update = &aiStatePoserFrequeUpdate;
    return state;
}

ai_state_t* aiStateTimeoutEnter(ai_state_t *this) {
    timeoutSet(0x3D, 0x0900);
    return NULL;
}

ai_state_t* aiStateTimeoutUpdate(ai_state_t *this) {
    if(timeoutCheck()) {
        return this->next_on_success;
    }
    else {
        return NULL;
    }
}

typedef struct {
    float reset_pos;
    float reset_angle;
    bool axisX;
} ai_data_calibration_t;

ai_state_t* aiStateCalibrationEnter(ai_state_t *this) {
    controllerChangeState(CS_Calibration);
    timeoutSet(0x3D, 0x0900);
//    unsigned int *data = this->data;
//    *data = 0;
    return NULL;
}

extern float position_x, position_y, position_angle;
ai_state_t* aiStateCalibrationUpdate(ai_state_t *this) {
    ai_data_calibration_t *data = (ai_data_calibration_t*) this->data;
    if(timeoutCheck()) {
        // Reset position
        if(data->axisX) {
            position_x = data->reset_pos;
        }
        else {
            position_y = data->reset_pos;
        }
        position_angle = data->reset_angle;
        // Go forward
        controllerChangeState(CS_PositionControl);
        return this->next_on_success;
    }
//    unsigned int *data = this->data;
//    if(adcGetChannel(5) > 1000 && adcGetChannel(21) > 1000) {
//        (*data)++;
//        if(*data > 10000) {
//            controllerChangeState(CS_PositionControl);
//            return this->next_on_success;
//        }
//    }
//    else {
//        *data = 0;
//    }
    return NULL;
}

ai_state_t* aiStateCalibration(bool axisX, float reset_pos, float reset_angle) {
    ai_state_t* state;
    state = aiNewState();
    state->enter = &aiStateCalibrationEnter;
    state->update = &aiStateCalibrationUpdate;
    ai_data_calibration_t *data = malloc(sizeof(ai_data_calibration_t));
    data->axisX = axisX;
    if(!team_is_yellow && axisX) {
        data->reset_pos = 3.0f - reset_pos;
        data->reset_angle = PI - reset_angle;
    }
    else {
        data->reset_pos = reset_pos;
        data->reset_angle = reset_angle;
    }
    state->data = data;
    return state;
}

ai_plan_t aiPlanRegisterPositions(void) {
    ai_plan_t plan;
    ai_state_t *s, *sloop;

    ai_plan_t calibration = aiPlanStartingPlacement();
    plan.entry = calibration.entry;

    calibration.exit->next_on_success = aiNewState();
    s = calibration.exit->next_on_success;
    s->name = "AI Register Position";
    sloop = s;
    s->update = &aiStateWaitButtonUpdate;
    s->exit = &aiStateLogPositionExit;

    s->next_on_success = aiNewState();
    s = s->next_on_success;
    s->next_on_success = sloop;
    plan.exit = s;

    return plan;
}

ai_plan_t aiPlanRegisterPositionsRed(void) {
    ai_plan_t plan;
    ai_state_t *s, *sloop;

//    ai_plan_t calibration = aiPlanStartingPlacementRed();
//    plan.entry = calibration.entry;

//    calibration.exit->next_on_success = aiNewState();
//    s = calibration.exit->next_on_success;

    s = aiNewState();
    plan.entry = s;
    s->name = "AI Register Position";
    sloop = s;
    s->update = &aiStateWaitButtonUpdate;
    s->exit = &aiStateLogPositionExit;

    s->next_on_success = aiNewState();
    s = s->next_on_success;
    s->next_on_success = sloop;
    plan.exit = s;

    return plan;
}

ai_plan_t
aiPlanMammooth(void)
{
   ai_plan_t plan, mp, fp;
   ai_state_t *s;

   s = aiStateSetPosition(0.2f, 0.15f, PI/2.0f);
   s->name = "AI Init";
   plan.entry = s;

   /* Move to a point XXX - change coords */
   s->next_on_success = aiStateGoto(0.2f, 0.6f, 1.1f * PI / 3.0f);
   s = s->next_on_success;
   s->name = "Step 1";

   /* Hit a fire XXX - change coords */
   s->next_on_success = aiStateGoto(0.4f, 1.1f, 7.0f * PI / 4.0f);
   s = s->next_on_success;
   s->name = "Step 2";

   /* Kill both mammooths XXX - you may need to change the order of the slaughter
    * 1st: true : MM1 then MM2 (false: the opposite)
    * 2nd: true : use left thrower first
    * 3rd: true : both mammooths */
   mp = aiTwoMammoothsPlan(true, true, true);
   s->next_on_success = mp.entry;
   s = s->next_on_success;
   s->name = "Step 3";

   // Error here, mp.entry is modified instead of mp.exit
   fp = aiPlanFresco();
   s->next_on_success = fp.entry;
   s = s->next_on_success ;
   s->name = "Step 4";

   // TODO failure handlers??

   // TODO plan.exit
   return plan;
}

ai_plan_t aiPlanSimpleRed(void) {
    ai_plan_t plan;
    ai_state_t *state;
    state = aiStateSetPosition(0.0f, 0.0f, PI/2.0f);
    state->name = "AI Sequence Simple Red";
    plan.entry = state;

    state->next_on_success = aiStateGoto(0.019789f, 0.254041f, 2.563273f);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->update = &aiStateWaitForJackUpdate;

    state->next_on_success = aiStateGoto(-0.409394f, 0.431202f, 3.014771f);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(-1.285239f, 0.477532f, 1.443974f);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(-1.337583f, 0.081267f, 1.437124f);
    state = state->next_on_success;

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Freque";

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque bis";

    state->next_on_success = aiStateGoto(-1.289399f, 0.417316f, 1.432883f);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->name = "AI sequence finished.\n";
    plan.exit = state;

    return plan;
}

ai_plan_t aiPlanSimpleYellow(void) {
    ai_plan_t plan;
    ai_state_t *state;

    state = aiStateSetPosition(0.0f, 0.0f, PI/2.0f);
    state->name = "AI Sequence Simple Yellow";
    plan.entry = state;

    state->next_on_success = aiStateGoto(0.005406f, 0.273317f, 0.585762f);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->update = &aiStateWaitForJackUpdate;

    state->next_on_success = aiStateGoto(0.301466f, 0.472720f, 0.019139f);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(1.258933f, 0.368081f, 1.522195f);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(1.233214f, /*0.045449f*/0.001f, 1.479606f);
    state = state->next_on_success;

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Freque";

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque bis";
    
    state->next_on_success = aiStateGoto(1.268223f, 0.418336f, 1.470202f);
    state = state->next_on_success;

    return plan;
}

///
//    state->next_on_success = aiStateGoto(0.715264f, 0.519700f, 1.268439f);
//    state = state->next_on_success;
//
//    state->next_on_success = aiStateGoto(0.715505f, 0.511759f, 1.826659f);
//    state = state->next_on_success;

///
//    state->next_on_success = aiStateGoto(0.450261f, 0.583936f, -0.058258f);
//    state = state->next_on_success;
//
//    state->next_on_success = aiStateGoto(1.425334f, 0.511332f, 1.430772f);
//    state = state->next_on_success;
//
//    state->next_on_success = aiStateGoto(1.375746f, 0.138070f, 1.422165f);
//    state = state->next_on_success;
//
//    state->next_on_success = aiStateGoto(1.452062f, 0.532545f, -0.213104f);
//    state = state->next_on_success;
//
//    state->next_on_success = aiStateGoto(0.818071f, 0.553485f, 0.813509f);
//    state = state->next_on_success;
//
//    state->next_on_success = aiStateGoto(0.815457f, 0.551058f, 1.444365f);
//    state = state->next_on_success;


ai_plan_t aiPlanThrowYellow(void) {
    ai_plan_t plan;
    ai_state_t *state;
    state = aiNewState();
    state->name = "AI Sequence Throw Yellow";
    plan.entry = state;

    // Hold both throwers
    state->next_on_success = aiStateThrowSpear(true, HOLD);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(false, HOLD);
    state = state->next_on_success;
    
    ai_plan_t calibration = aiPlanStartingPlacement();
    state->next_on_success = calibration.entry;

    calibration.exit->next_on_success = aiNewState();
    state = calibration.exit->next_on_success;;
    state->update = &aiStateWaitForJackUpdate;
    state->name = "Waiting for Jack!";

    // Fresques
    state->next_on_success = aiStateGoto(0.450261f, 0.583936f, -0.058258f);
    state = state->next_on_success;
    state->name = "Go";

    state->next_on_success = aiStateGoto(1.425334f, 0.511332f, 1.430772f);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateGoto(1.375746f, 0.138070f, 1.422165f);
    state = state->next_on_success;

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque";

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque";

    state->next_on_success = aiStateGoto(1.375746f, 0.30f, 1.422165f);
    state = state->next_on_success;

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque";

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque";

    // Spears
    state->next_on_success = aiStateGoto(1.452062f, 0.532545f, -0.213104f);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(0.768071f, 0.550485f, 0.935681f);
    state = state->next_on_success;
    state->name = "Spears";

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateThrowSpear(!team_is_yellow, THROW3);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(team_is_yellow, HOLD);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateThrowSpear(!team_is_yellow, THROW1);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(team_is_yellow, HOLD);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(0.765457f, 0.551058f, 1.618896f);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateThrowSpear(team_is_yellow, THROW3);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(!team_is_yellow, HOLD);
    state = state->next_on_success;
    
    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateThrowSpear(team_is_yellow, THROW1);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(!team_is_yellow, HOLD);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateGoto(0.40f, 0.70f, PI/2.0f);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(0.40f, 1.50f, PI/2.0f);
    state = state->next_on_success;
    
    // Fire!!!
    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateGoto(0.35f, 0.70f, PI/-2.0f);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(0.35f, 1.50f, PI/-2.0f);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->name = "AI sequence finished.\n";
    plan.exit = state;

    return plan;
}

ai_plan_t aiPlanThrowRed(void) {
    ai_plan_t plan;
    ai_state_t *state;
    state = aiNewState();
    state->name = "AI Sequence Throw Red";
    plan.entry = state;

    // Hold both throwers
    state->next_on_success = aiStateThrowSpear(true, HOLD);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(false, HOLD);
    state = state->next_on_success;

    ai_plan_t calibration = aiPlanStartingPlacementRed();
    state->next_on_success = calibration.entry;

    calibration.exit->next_on_success = aiNewState();
    state = calibration.exit->next_on_success;;
    state->update = &aiStateWaitForJackUpdate;
    state->name = "Waiting for Jack!";

    // Fresques
    state->next_on_success = aiStateGoto(3.0f-0.450261f, 0.583936f, PI+0.058258f);
    state = state->next_on_success;
    state->name = "Go";

    state->next_on_success = aiStateGoto(3.0f-1.425334f, 0.511332f, PI-1.430772f);//PI/2.0f);//
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateGoto(3.0f-1.375746f, 0.138070, PI-1.430772f);
    state = state->next_on_success;

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque";

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque";

    state->next_on_success = aiStateGoto(1.375746f, 0.30f, PI-1.430772f);
    state = state->next_on_success;

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque";

    state->next_on_success = aiStatePoserFreque();
    state = state->next_on_success;
    state->name = "Fresque";

    // Spears
    state->next_on_success = aiStateGoto(3.0f-1.452062f, 0.532545f, PI+0.213104f-0.20f);// -2.9284886535897932384626433832795f);//
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(3.0f-0.768071f, 0.550485f, PI-0.935681f-0.15f);//PI-0.935681f);
    state = state->next_on_success;
    state->name = "Spears";

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateThrowSpear(true, THROW3);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(false, HOLD);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateThrowSpear(true, THROW1);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(false, HOLD);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(3.0f-0.765457f, 0.551058f, PI-1.618896f-0.2617f);//PI-1.618896f
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateThrowSpear(false, THROW3);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(true, HOLD);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateThrowSpear(false, THROW1);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(true, HOLD);
    state = state->next_on_success;


    // Fire!!!
    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->enter = &aiStateTimeoutEnter;
    state->update = &aiStateTimeoutUpdate;

    state->next_on_success = aiStateGoto(3.0f-0.35f, 0.70f, PI/2.0f);
    state = state->next_on_success;

    state->next_on_success = aiStateGoto(3.0f-0.35f, 1.50f, PI/2.0f);
    state = state->next_on_success;

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->name = "AI sequence finished.\n";
    plan.exit = state;

    return plan;
}

ai_plan_t aiPlanGo() {
    ai_plan_t plan;
    ai_state_t *state;

    plan.entry = aiStateSetPosition(0.0f, 0.0f, 0.0f);
    state = plan.entry;
    
    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->update = &aiStateWaitForJackUpdate;
    state->name = "Waiting for Jack!";

    state->next_on_success = aiStateGoto(0.80f, 0.0f, 0.0f);
    plan.exit = state;

    return plan;
}
ai_plan_t aiPlanStartingPlacement() {
    ai_plan_t plan;
    ai_state_t *s;

    float start_x = 0.20f;
    float start_y = 0.425f;
    float start_angle = 0.585762f; // 2.555830f

    // Init position
    s = aiStateSetPosition(0.0f, 0.0f, PI/2.0f); //-1.0f * PI/2.0f
    s->name = "AI Starting Placement";
    plan.entry = s;

    s->next_on_success = aiStateGoto(0.0f, 0.0f, PI/2.0f); //-1.0f * PI/2.0f
    s = s->next_on_success;

    // Calibration Y
    s->next_on_success = aiStateCalibration(false, 0.15353f, PI/2.0f); //-1.0f * PI/2.0f
    s = s->next_on_success;
    s->name = "Calib Y";

    s->next_on_success = aiStateGoto(0.0f, start_y, 0.0f); //-1.0f * PI
    s = s->next_on_success;

    s->next_on_success = aiNewState();
    s = s->next_on_success;
    s->enter = &aiStateTimeoutEnter;
    s->update = &aiStateTimeoutUpdate;

    // Calibration X
    s->next_on_success = aiStateCalibration(true, 0.15353f, 0.0f); //-1.0f * PI/2.0f
    s = s->next_on_success;
    s->name = "Calib X";
    
    s->next_on_success = aiStateGoto(0.18f, start_y, 0.0f);
    s = s->next_on_success;

    s->next_on_success = aiStateGoto(start_x, start_y, start_angle);
    s = s->next_on_success;
    plan.exit = s;

    return plan;
}

ai_plan_t aiPlanStartingPlacementRed() {
    ai_plan_t plan;
    ai_state_t *s;

    float start_x = 3.0f-0.20f;
    float start_y = 0.425f;
    float start_angle = PI-0.585762f; // 2.555830f

    // Init position
    s = aiStateSetPosition(0.0f, 0.0f, PI/2.0f); //-1.0f * PI/2.0f
    s->name = "AI Starting Placement";
    plan.entry = s;

    s->next_on_success = aiStateGoto(0.0f, 0.0f, PI/2.0f); //-1.0f * PI/2.0f
    s = s->next_on_success;

    // Calibration Y
    s->next_on_success = aiStateCalibration(false, 0.15353f, PI/2.0f); //-1.0f * PI/2.0f
    s = s->next_on_success;
    s->name = "Calib Y";

    s->next_on_success = aiStateGoto(0.0f, start_y, PI); //-1.0f * PI
    s = s->next_on_success;

    s->next_on_success = aiNewState();
    s = s->next_on_success;
    s->enter = &aiStateTimeoutEnter;
    s->update = &aiStateTimeoutUpdate;

    // Calibration X
    s->next_on_success = aiStateCalibration(true, 3.0f-0.15353f, PI); //-1.0f * PI/2.0f
    s = s->next_on_success;
    s->name = "Calib X";

    s->next_on_success = aiStateGoto(3.0f-0.18f, start_y, PI);
    s = s->next_on_success;

    s->next_on_success = aiStateGoto(start_x, start_y, start_angle);
    s = s->next_on_success;
    plan.exit = s;

    return plan;
}

ai_plan_t aiPlanSetCoefAngle() {
    ai_plan_t plan;
    ai_state_t *s, *sloop;

    // Init position
    s = aiStateSetPosition(0.0f, 0.0f, 0.0f);
    plan.entry = s;

    // Set angle absolute
    s->next_on_success = aiNewState();
    s = s->next_on_success;
    s->enter = &aiStateSetAngleAbsoluteEnter;

    // Start of loop
    // Do 5 full turns
    s->next_on_success = aiStateGoto(0.0f, 0.0f, 10.0f*PI);
    s = s->next_on_success;
    sloop = s;

//    // Start of loop
//    // Half a turn
//    s->next_on_success = aiStateGoto(0.0f, 0.0f, PI);
//    s = s->next_on_success;
//    sloop = s;
//
//    // Other half a turn
//    s->next_on_success = aiStateGoto(0.0f, 0.0f, 0.0f);
//    s = s->next_on_success;
//
//    // Loop 5 times
//    s->next_on_success = aiStateLoop(5);
//    s = s->next_on_success;
//    s->next_on_failure = sloop;
    
    // Wait for button push
    s->next_on_success = aiNewState();
    s = s->next_on_success;
    s->update = &aiStateWaitButtonUpdate;

    // End of loop
    s->next_on_success = sloop;
    plan.exit = s;
    
    return plan;
}

ai_plan_t aiPlanSetCoefLenght() {
    ai_plan_t plan;
    ai_state_t *s, *sloop;

    // Init position
    s = aiStateSetPosition(0.0f, 0.0f, 0.0f);
    plan.entry = s;

    // Start of loop
    // Go straight for 50cm
    s->next_on_success = aiStateGoto(0.5f, 0.0f, 0.0f);
    s = s->next_on_success;
    sloop = s;

    // Wait for button push
    s->next_on_success = aiNewState();
    s = s->next_on_success;
    s->update = &aiStateWaitButtonUpdate;

    // Turn around
    s->next_on_success = aiStateGoto(0.5f, 0.0f, PI);
    s = s->next_on_success;

    // Go straight for 50cm
    s->next_on_success = aiStateGoto(0.0f, 0.0f, PI);
    s = s->next_on_success;

    // Turn around
    s->next_on_success = aiStateGoto(0.0f, 0.0f, 0.0f);
    s = s->next_on_success;

    // Wait for button push
    s->next_on_success = aiNewState();
    s = s->next_on_success;
    s->update = &aiStateWaitButtonUpdate;

    // End of loop
    s->next_on_success = sloop;
    plan.exit = s;

    return plan;
}

ai_plan_t aiPlanThrowerRefill(void) {
    ai_plan_t plan;
    ai_state_t *state;

    state = aiStateSetPosition(0.0f, 0.0f, PI/2.0f);
    state->name = "AI Refilling spears throwers";
    plan.entry = state;

    state->next_on_success = aiStateThrowSpear(true, THROW3);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(false, HOLD);
    state = state->next_on_success;
    state->name = "Refill 3 left";

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->update = &aiStateWaitButtonUpdate;

    state->next_on_success = aiStateThrowSpear(true, HOLD);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(false, THROW3);
    state = state->next_on_success;
    state->name = "Refill 3 right";

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->update = &aiStateWaitButtonUpdate;
    
    state->next_on_success = aiStateThrowSpear(true, HOLD);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(false, THROW1);
    state = state->next_on_success;
    state->name = "Refill 1 right";

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->update = &aiStateWaitButtonUpdate;

    state->next_on_success = aiStateThrowSpear(true, HOLD);
    state = state->next_on_success;
    state->next_on_success = aiStateThrowSpear(false, HOLD);
    state = state->next_on_success;
    state->name = "All hold";

    state->next_on_success = aiNewState();
    state = state->next_on_success;
    state->update = &aiStateWaitButtonUpdate;

    plan.exit = state;

    return plan;
}

void aiInit(void) {
     // Create plan
     ai_plan_t plan;
     unsigned char setup = 0;
     team_is_yellow = !PORTFbits.RF0;
     setup += 1 * PORTAbits.RA6;
     setup += 2 * PORTGbits.RG0;
     setup += 4 * PORTGbits.RG1;
     setup += 8 * PORTFbits.RF1;
     logStringFormatted("AI Plan %u selected\n", setup);
     switch(setup) {
         case 1:
             plan = aiPlanSetCoefAngle();
             break;
         case 2:
             plan = aiPlanSetCoefLenght();
             break;
         case 3:
             plan = aiPlanThrowRed();
             break;
         case 4:
             plan = aiPlanThrowYellow();
             break;
         case 5:
             plan = aiPlanThrowerRefill();
             break;
         case 6:
             plan = aiPlanStartingPlacement();
             break;
         case 7:
             plan = aiPlanRegisterPositionsRed();
             break;
         case 8:
             plan = aiPlanGo();
             break;
         case 0:
         default:
             logString("Default plan selected\n");
             plan = aiPlanRegisterPositions();
     }
     ai_state_current = plan.entry;
     ai_state_current_is_initialized = false;
     if(team_is_yellow) {
         logString("Yellow");
     }
     else {
         logString("Red");
     }
     logString(" team selected.\n");
}

ai_state_t* aiCallFunction(ai_state_t *this, ai_function_t f) {
     ai_state_t *ret = NULL;
     if(this == NULL) {
          logString("Fatal error in aiCallFunction !");
          return NULL;
     }
     if(f != NULL) {
          ret = f(this);
          // Check if a change of state is needed
          if(ret != NULL) {
               if (this->exit != NULL)
                 this->exit(this);
          }
     }
     return ret;
}

void aiUpdate(void) {
     ai_state_t *ret = NULL;

     // Check if the current state exists
     if(ai_state_current == NULL) {
          logString("Fatal error in aiUpdate: no current state !");
          return;
     }

     // If needed, initialize the state
     if(!ai_state_current_is_initialized) {
          ai_state_current_is_initialized = true;

#ifndef NO_AI_DEBUG
          // Print debug name
          if(ai_state_current->name != NULL) {
               logString(ai_state_current->name);
               logString("\n");
          }
#endif // NO_AI_DEBUG

          // Initialize
          ret = aiCallFunction(ai_state_current, ai_state_current->enter);
          // Change to the new state if it is returned
          if(ret != NULL) {
               ai_state_current = ret;
               ai_state_current_is_initialized = false;
               return;
          }
     }
     // Update current state
     ret = aiCallFunction(ai_state_current, ai_state_current->update);
     // Change to the new state if it is returned
     if(ret != NULL) {
          ai_state_current = ret;
          ai_state_current_is_initialized = false;
          return;
     }
}

extern bool sharpFrontDisable, sharpBackDisable;
ai_state_t* aiStateDetectionEnableEnter(ai_state_t *this) {
    sharpFrontDisable = false;
    sharpFrontDisable = false;
    return NULL;
}
ai_state_t* aiStateDetectionDisableEnter(ai_state_t *this) {
    sharpBackDisable = true;
    sharpBackDisable = true;
    return NULL;
}
