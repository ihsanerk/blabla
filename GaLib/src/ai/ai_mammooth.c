#include "../../include/ai/ai.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "tracking/tracker.h"
#include "io/pwm.h"
#include "debug/log.h"


//static bool _mm1_done = false;
//static bool _mm2_done = false;

#define MAMMOOTH_1_POSX     ((float)    0)
#define MAMMOOTH_1_POSY     ((float)    0)
#define MAMMOOTH_ANGLE_L    ((float)    0)
#define MAMMOOTH_ANGLE_R    ((float)    0)
#define MAMMOOTH_2_POSX     ((float)    0)
#define MAMMOOTH_2_POSY     ((float)    0)

EAPI ai_plan_t
aiOneMammoothPlan(bool mm1)
{
   ai_plan_t plan;
   ai_state_t *m1, *m2, *end, *st;
   float x, y;

   if (mm1)
     {
        x = MAMMOOTH_1_POSX;
        y = MAMMOOTH_1_POSY;
     }
   else
     {
        x = MAMMOOTH_2_POSX;
        y = MAMMOOTH_2_POSY;
     }

   /* MM1 */
   m1 = aiStateGoto(x, y, MAMMOOTH_ANGLE_L);
   m1->name = "Mammooth 1 Goto";

   /* MM2 */
   m2 = aiStateGoto(x, y, MAMMOOTH_ANGLE_R);
   m2->name = "Mammooth 2 Goto";

   /* End */
   end = aiNewState();
   end->name = "Mammooths Sequence finished\n";
   plan.exit = end;

   /* Start with MM1 fallback to MM2 */
   plan.entry = m1;
   m1->next_on_failure = m2;

   /* [MM1] Throw. Fail -> MM2, OK -> MM2 */
   m1->next_on_success = aiStateThrow(true); // XXX : MAYBE THE OPPOSITE!!
   st = m1->next_on_success;
   st->name = "Mammooth 1 Throw (1st)";
   st->next_on_failure = st->next_on_success = m2;

   /* [MM2] Throw. Fail -> end, OK -> end */
   m2->next_on_success = aiStateThrow(false); // XXX : MAYBE THE OPPOSITE!!
   st = m2->next_on_success;
   st->name = "Mammooth 1 Throw (2nd)";
   st->next_on_failure = st->next_on_success = end;

   return plan;
}

EAPI ai_plan_t
aiTwoMammoothsPlan(bool mm1,
                   bool thrower_is_left,
                   bool both)
{
   ai_plan_t plan;
   ai_state_t *m1, *m2, *end, *st;
   float x1, y1, a1, x2, y2, a2;

   thrower_is_left = (team_is_yellow) ? thrower_is_left : !thrower_is_left;

   if (mm1)
     {
        x1 = MAMMOOTH_1_POSX;  x2 = MAMMOOTH_2_POSX;
        y1 = MAMMOOTH_1_POSY;  y2 = MAMMOOTH_2_POSY;
        if (thrower_is_left)
          {
             a1 = MAMMOOTH_ANGLE_L;
             a2 = MAMMOOTH_ANGLE_R;
          }
        else
          {
             a1 = MAMMOOTH_ANGLE_R;
             a2 = MAMMOOTH_ANGLE_L;
          }
     }
   else
     {
        x1 = MAMMOOTH_2_POSX;  x2 = MAMMOOTH_1_POSX;
        y1 = MAMMOOTH_2_POSY;  y2 = MAMMOOTH_1_POSY;
        if (thrower_is_left)
          {
             a1 = MAMMOOTH_ANGLE_R;
             a2 = MAMMOOTH_ANGLE_L;
          }
        else
          {
             a1 = MAMMOOTH_ANGLE_L;
             a2 = MAMMOOTH_ANGLE_R;
          }
     }

   /* MM1 */
   m1 = aiStateGoto(x1, y1, a1);
   m1->name = "Mammooth 1 Goto";

   /* MM2 */
   m2 = aiStateGoto(x2, y2, a2);
   m2->name = "Mammooth 2 Goto";

   /* End */
   end = aiNewState();
   end->name = "Mammooths Sequence finished\n";
   plan.exit = end;

   /* Start with MM1 fallback to MM2 */
   plan.entry = m1;
   m1->next_on_failure = (both) ? m2 : end;

   /* [MM1] Throw. Fail -> MM2, OK -> MM2 */
   m1->next_on_success = aiStateThrow(thrower_is_left);
   st = m1->next_on_success;
   st->name = "Mammooth 1 Throw";
   st->next_on_failure = st->next_on_success = (both) ? m2 : end;

   /* [MM2] Throw. Fail -> end, OK -> end */
   m2->next_on_success = aiStateThrow(!thrower_is_left);
   st = m2->next_on_success;
   st->name = "Mammooth 2 Throw";
   st->next_on_failure = st->next_on_success = end;

   return plan;
}

