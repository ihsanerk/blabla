#ifndef AI_INCLUDED
#define AI_INCLUDED

// Backup sequence in case anything goes wrong
void aiInit(void);
void aiUpdate(void);

#include <stdbool.h>

extern bool team_is_yellow;
extern bool ai_button_pushed;
/* Might go in a private header */

#ifndef EAPI
# define EAPI extern
#endif

struct ai_state;
typedef struct ai_state* (*ai_function_t)(struct ai_state *);


struct ai_state {
    ai_function_t enter;
    ai_function_t update;
    ai_function_t exit;
    struct ai_state *next_on_success;
    struct ai_state *next_on_failure;
    char *name;
    void *data;
};
typedef struct ai_state ai_state_t;


typedef struct {
    float x, y, angle;
} ai_data_position_t;

typedef struct {
    unsigned int value;
    unsigned int n;
} ai_data_counter;

typedef struct {
    ai_state_t *entry;
    ai_state_t *exit;
} ai_plan_t;

ai_state_t* aiNewState(void);

EAPI ai_state_t *aiStateGoto(float x, float y, float angle);
EAPI ai_state_t *aiStateSetPosition(float x, float y, float angle);
EAPI ai_state_t *aiStateThrow(bool left);
EAPI ai_state_t *aiStateLateralHook(bool left, bool pos_open);

EAPI ai_plan_t aiPlanFresco(void);
EAPI ai_plan_t aiOneMammoothPlan(bool mm1);
EAPI ai_plan_t aiTwoMammoothsPlan(bool mm1, bool thrower_is_left, bool both);

#endif // AI_INCLUDED
