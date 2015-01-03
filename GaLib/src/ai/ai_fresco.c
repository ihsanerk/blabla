#include "../../include/ai/ai.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "tracking/tracker.h"
#include "io/pwm.h"
#include "debug/log.h"


#define WALL_X1             ((float)    0)
#define WALL_Y1             ((float)    0)
#define WALL_ANGLE          ((float)    0)
#define WALL_X2             ((float)    0)
#define WALL_Y2             ((float)    0)

EAPI ai_plan_t
aiPlanFresco(void)
{
   ai_plan_t plan;
   ai_state_t *st;
   ai_state_t *end;

   end = aiNewState();
   end->name = "Fresco Sequence Finished\n";
   plan.exit = end;

   st = aiStateGoto(WALL_X1, WALL_Y1, WALL_ANGLE);
   plan.entry = st;
   st->name = "Fresco Navpoint Goto";
   st->next_on_failure = end;

   st->next_on_success = aiStateGoto(WALL_X2, WALL_Y2, WALL_ANGLE);
   st = st->next_on_success;
   st->name = "Fresco Move Backwards";
   st->next_on_success = st->next_on_failure = end;

   return plan;
}

