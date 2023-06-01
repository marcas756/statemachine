/*! \copyright
               Copyright (c) 2013, marco@bacchi.at
               All rights reserved.

               Redistribution and use in source and binary forms, with or without
               modification, are permitted provided that the following conditions
               are met:
               1. Redistributions of source code must retain the above copyright
                notice, this list of conditions and the following disclaimer.
               2. Redistributions in binary form must reproduce the above copyright
                notice, this list of conditions and the following disclaimer in the
                documentation and/or other materials provided with the distribution.
               3. The name of the author may not be used to endorse or promote
                products derived from this software without specific prior
                written permission.

               THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
               OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
               WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
               ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
               DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
               DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
               GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
               INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
               WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
               NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
               SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*!
   \file       sm.c
   \version    0000
   \authors    marco@bacchi.at
   \date       2013

   \brief      General UML state machine implementation

   \details    UML state machine, also known as UML state chart, is a significantly
               enhanced realization of the mathematical concept of a finite automaton
               in computer science applications as expressed in the Unified Modeling
               Language (UML) notation. (wikipedia)\n\n

               The concepts behind it are about organizing the way a device, computer
               program, or other (often technical) process works such that an entity or
               each of its sub-entities is always in exactly one of a number of possible
               states and where there are well-defined conditional transitions between
               these states. (wikipedia)\n\n

               This module and its interface provides the general implementation part for
               any state machine written for this implementation.

               This implementation supports:\n\n

               - finite flat state machines
               - guard conditions for transitions
               - state entry and exit actions
               - do actions by starting/stopping (proto)threads in entry/exit action respectively
               - transition effects (actions directly associated with a specific transition)

               Limitations of this implementation: \n\n

               - not interrupt/thread safe
               - hierarchical state machines not supported
               - execution time overhead due to generalization in comparison to quick and dirty FSMs
               - transition fork/join not supported
               - history states not supported
               - sending events in entry/exit/transition/effect functions not allowed (due to recursion)

               References: ISBN 3-8273-1486-0   Das UML-Benutzerhandbuch

               __Changelog__

               Revision|Date    |Name  |Change
               --------|--------|------|-------------------------------------------------
               0000    |00.00.00|bacmar|Detailed Change Text


*/



#include "sm.h"
#include <stddef.h>

/*!
   \brief      Action to carry out in case of a specific transition
   \details    You can associate a transition with an effect, which is an optional activity
               performed when a specific transition fires. The associated function may only be set
               within a transition function. It will be reset to NULL again after state transition.
               Transition effects will not work for internal state transitions.

   \remark     Move to sm instance in future (for future thread safe version) or to transition function as parameter
 */
sm_transition_effect_fp sm_transition_effect = NULL;



/*!
   \brief      Initialize a statemachine with a provided initial state
   \details    Initializes the statemachine with a provided state.
               The Initial State from the UML Statechart Diagram is the state of an object before any transitions.
               The Initial State from the UML Statechart Diagram marks the entry point and the initial statemachine state.
               The notation for the Initial State is a small solid filled circle. There can only be one Initial State on a diagram.
               Invoking this function transits from initial pseudo state to the initial statemachine state.


   \param[in,out]    sm       State machine instance
   \param[in]        state    State to initialize the state machine with.
                              Has to be a valid state of the state machines state table.


   \returns    State of the state machine after initial transition.
               NULL if initialization failed

   \ingroup SmInterface
*/
sm_state_t* sm_init(sm_t* sm, const sm_state_t* state)
{
   if(!sm || !state) return NULL;


   /* invoke the initial states entry action */
   if(state->entry_action)
      state->entry_action(SM_EVENT_INIT,NULL);

   /* perform transition */
   sm->state = (sm_state_t*)state;

   return (sm_state_t*)state;
}

/*!
   \brief      Terminates the statemachine
   \details    This function is meant to be used to terminate a statemachine. Usually a statemachine terminates itself by entering
               a pseudo final state.

   \param[in,out]    sm       State machine instance

   \ingroup SmInterface
*/
void sm_terminate(sm_t *sm)
{
   if(!sm || !sm->state) return;

   if(sm->state->exit_action)
      sm->state->exit_action(SM_EVENT_EXIT,NULL);

   sm->state = NULL;
}

/*!
   \brief      Sends an event to a statemachine.
   \details


   \param[in,out]    sm       State machine instance
   \param[in]        event    Event to be sent to the state machine
   \param[in,out]    data     Data associated with the event


   \returns    State of the state machine after transition.
               NULL if transition failed.


   \ingroup SmInterface
*/
sm_state_t* sm_send(sm_t* sm, event_t event, void* data)
{
   sm_state_t* target = NULL;
   sm_state_t* source;

   if(!sm || !sm->state) return NULL;

   source = sm->state;

   sm_transition_effect = NULL;

   /* prepare transition from source to target state*/
   if(source->transitions)
      target = (sm_state_t*)source->transitions(event,data);

   /* external or self transition */
   if(target)
   {
      /* invoke exit action of source state, if any */
      if(source->exit_action)
         source->exit_action(event,data);

      /* invoke transition effect, if any */
      if(sm_transition_effect)
      {
         sm_transition_effect(event,data);
         sm_transition_effect = NULL;
      }

      /* perform transition  */
      sm->state = target;

      /* invoke entry action of target state, if any */
      if(target->entry_action)
         target->entry_action(event,data);

      return target;
   }

   /* none or internal transition */
   return source;
}


