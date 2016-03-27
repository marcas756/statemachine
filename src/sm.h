/*
 * sm.h
 *
 *  Created on: 24. M�rz 2016
 *      Author: blackdigi
 */

#ifndef SM_H_
#define SM_H_



#define SM_EVENT_INIT (~((event_t)0))
#define SM_EVENT_EXIT (SM_EVENT_INIT-1)

typedef unsigned int event_t;
typedef struct sm_state_t sm_state_t ;
typedef void(*sm_entry_action_fp)(event_t event, void* data);
typedef const sm_state_t*(*sm_transitions_fp)(event_t event, void* data);
typedef void(*sm_exit_action_fp)(event_t event, void* data);
typedef void(*sm_transition_effect_fp)(event_t event, void* data);

extern sm_transition_effect_fp sm_transition_effect;

struct sm_state_t {
   sm_entry_action_fp entry_action;
   sm_transitions_fp transitions;
   sm_exit_action_fp exit_action;
};

typedef struct {
   sm_state_t *state;
   void *data;
}sm_t;

#define sm_state_id(base_ptr,state_ptr) \
   ((state_ptr)-(base_ptr))

sm_state_t* sm_init(sm_t* sm, const sm_state_t* state);
void sm_terminate(sm_t *sm);
sm_state_t* sm_send(sm_t* sm, event_t event, void* data);

#endif /* SM_H_ */
