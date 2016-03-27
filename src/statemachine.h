/*
 * statemachine.h
 *
 *  Created on: 24. März 2016
 *      Author: blackdigi
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_
#include "sm.h"
#include "stddef.h"

typedef enum {
   a,b,c,d,e
}statemachine_event_t;

typedef enum {
   A,B,C
}statemachine_states_t;

extern const sm_state_t statemachine_states[];
extern const size_t statemachine_state_count;

#endif /* STATEMACHINE_H_ */
