#include "../../include/ai/ai.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "tools/math.h"
#include "tracking/tracker.h"
#include "io/pwm.h"
#include "debug/log.h"
#include "tools/timeout.h"


/*============================================================================*
 *                                 State Goto                                 *
 *============================================================================*/

static ai_state_t *
aiStateGotoEnter(ai_state_t *this)
{
   ai_data_position_t *data = (ai_data_position_t*) this->data;
   trackerSetObjective(data->x, data->y, data->angle);
//   timeoutSet(0x262, 0x5A00);//10s
   return NULL;
}

static ai_state_t *
aiStateGotoUpdate(ai_state_t *this)
{
   if(trackerIsPositionAtObjective()) {
        return this->next_on_success;
   }
//   if(timeoutCheck()) {
//        return this->next_on_failure;
//   }
   return NULL;
}

EAPI ai_state_t *
aiStateGoto(float x, float y, float angle)
{
   ai_state_t *state = aiNewState();
   state->enter = &aiStateGotoEnter;
   state->update = &aiStateGotoUpdate;
   ai_data_position_t *data = (ai_data_position_t*) malloc(sizeof(ai_data_position_t));
   data->x = (team_is_yellow) ? x : 3.0f - x;
   data->y = y;
   float tmp = PI - angle;
   data->angle = (team_is_yellow) ? angle : tmp;
   state->data = (void*) data;
   return state;
}

/*============================================================================*
 *                               Set Position                                 *
 *============================================================================*/

static ai_state_t *
aiStateSetPositionEnter(ai_state_t *this)
{
   ai_data_position_t *data = (ai_data_position_t*) this->data;
   trackerSetPosition(data->x, data->y, data->angle);
   return NULL;
}

EAPI ai_state_t *
aiStateSetPosition(float x, float y, float angle)
{
   ai_state_t *state = aiNewState();
   state->enter = &aiStateSetPositionEnter;
   ai_data_position_t *data = (ai_data_position_t*) malloc(sizeof(ai_data_position_t));
   data->x = (team_is_yellow) ? x : 3.0f - x;
   data->y = y;
   float tmp = PI - angle;
   data->angle = (team_is_yellow) ? angle : tmp;
   state->data = (void*) data;
   return state;
}


/*============================================================================*
 *                                    Throw                                   *
 *============================================================================*/

typedef struct
{
   bool is_left;
} ai_thrower_t;

static ai_state_t *
_throw_enter(ai_state_t *this)
{
   // TODO: switch 'left' to determine which thrower to use
   // TODO: when 'left' is false, it is obviously th right one to use
   ai_thrower_t *data = this->data;
//   pwmSet(0, 0);
   //setTimeout(0); // TODO
   return NULL;
}

static ai_state_t *
_throw_update(ai_state_t *this)
{
//   while (!ai_timeout_check())
//     return NULL;
   return this->next_on_success;
}

EAPI ai_state_t *
aiStateThrow(bool left)
{
   ai_state_t *state = aiNewState();
   ai_thrower_t *data = malloc(sizeof(ai_thrower_t));
   data->is_left = left;
   state->enter = &_throw_enter;
   state->update = &_throw_update;
   state->data = data;
   state->name = "Balls Thrower State";
   return state;
}

/*============================================================================*
 *                                Lateral Hook                                *
 *============================================================================*/

typedef struct
{
   bool is_left;
   bool pos_open;
} ai_lateral_hook_t;

static ai_state_t *
_lat_hook_enter(ai_state_t *this)
{
   ai_lateral_hook_t *data = this->data;
   // TODO
   // * data->is_left;
   // * data->pos_open

//   ai_timeout_set(0); // TODO
   return NULL;
}

static ai_state_t *
_lat_hook_update(ai_state_t *this)
{
//   while (!ai_timeout_check())
//     return NULL;
   return this->next_on_success;
}

EAPI ai_state_t *
aiStateLateralHook(bool left,
                   bool pos_open)
{
   ai_state_t *st = aiNewState();

   left = (team_is_yellow) ? left : !left;
   ai_lateral_hook_t *data = malloc(sizeof(ai_lateral_hook_t));
   data->is_left = left;
   data->pos_open = pos_open;
   st->enter = &_lat_hook_enter;
   st->update = &_lat_hook_update;
   st->name = "Lateral Hook";
   return st;
}

/*============================================================================*
 *                                     Arm                                    *
 *============================================================================*/

typedef struct
{
   float z;
   float t1;
   float t2;
} ai_arm_t;

static ai_state_t *
_arm_enter(ai_state_t *this)
{
   ai_arm_t *data = this->data;
   // data->z
   // data->t1
   // data->t2
   // TODO ELEVATOR
   //   dxl_write_word(ID, MOS, data->t1);
   //   dxl_write_word(ID, MOS, data->t2);
//   ai_timeout_set(0); // TODO
   return NULL;
}

static ai_state_t *
_arm_update(ai_state_t *this)
{
//   while (!ai_timeout_check()) //TODO
 //    return NULL; TODO
   return this->next_on_success;
}

EAPI ai_state_t *
aiStateArm(float z, float t1, float t2)
{
   ai_state_t *st = aiNewState();
   ai_arm_t *data = malloc(sizeof(ai_arm_t));

   data->z = z;
   data->t1 = t1;
   data->t2 = t2;
   st->data = data;
   st->enter = &_arm_enter;
   st->update = &_arm_update;
   st->name = "Moving Arm";

   return st;
}

