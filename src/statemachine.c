
#include"statemachine.h"
#include<stdbool.h>

#define DEBUG 1

#if DEBUG
   #include<stdio.h>
   #define DBG(...) printf(__VA_ARGS__)
#else
   #define DBG(...)
#endif

bool guard = false;

/* STATE A HANDLERS */
/* ################################################################# */

void A_entry(event_t event, void* data)
{
   DBG("A Entry\n");
}

const sm_state_t* A_transitions(event_t event, void* data)
{
   switch(event)
   {
      case a:
         /* external transition */
         return &statemachine_states[C];

      case d:
         /* external transition with guard condition + internal transition */
         DBG("A Internal\n");

         if(guard)
            return &statemachine_states[B];

         return &statemachine_states[C];
   }

   return NULL; /* Event not handled, no transition */
}

void A_exit(event_t event, void* data)
{
   DBG("A Exit\n");
}



/* STATE B HANDLERS */
/* ################################################################# */

void BeC_transition_effect(event_t event, void* data)
{
   DBG("BeC Transition Effect\n");
}

const sm_state_t* B_transitions(event_t event, void* data)
{
   switch(event)
   {
      case c:
         /* external transition */
         return &statemachine_states[A];

      case e:
         /* external action with transition action */
         sm_transition_effect = BeC_transition_effect;
         return &statemachine_states[C];
   }

   return NULL; /* Event not handled, no transition */
}

void B_exit(event_t event, void* data)
{
   DBG("B Exit\n");
}

/* STATE A HANDLERS */
/* ################################################################# */

void C_entry(event_t event, void* data)
{
   DBG("C Entry\n");
}

const sm_state_t* C_transitions(event_t event, void* data)
{
   switch(event)
   {
      case a:
         /* internal transition */
         DBG("C Internal\n");
         return NULL;

      case b:
         /* external transition */
         return &statemachine_states[B];
   }

   return NULL; /* Event not handled, no transition */
}


const sm_state_t statemachine_states[]= {
      {A_entry,      A_transitions,       A_exit},
      {NULL,         B_transitions,       B_exit},
      {C_entry,      C_transitions,       NULL}
};

const size_t statemachine_state_count = sizeof(statemachine_states)/sizeof(statemachine_states[0]);

