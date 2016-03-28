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
   \file       sm.h
   \version    0000
   \authors    marco@bacchi.at
   \date       2013

   \brief      General UML state machine interface

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
*/

#ifndef SM_H_
#define SM_H_



#define SM_EVENT_INIT (~((event_t)0))
#define SM_EVENT_EXIT (SM_EVENT_INIT-1)

/*!
   An event is something that happens that affects the system.
   An event can have associated parameters, allowing the event instance to convey not only the occurrence
   of some interesting incident but also quantitative information regarding that occurrence. The associated
   parameters can be forwarded to the state machine via the data pointer of the sm_send function
*/
typedef unsigned int event_t;

/*!
   Forward declaration of sm_state structure
*/
typedef struct sm_state_t sm_state_t ;


/*!
    \brief     Callback function type for entry actions
    \details   Every state in a UML state chart can have an optional entry action, which is executed upon
               entry to a state. Entry actions are associated with states, not transitions. Regardless
               of how a state is entered, its entry action will be executed.

   \param      event    Triggering event
   \param      data     Data associated with the event

*/
typedef void(*sm_entry_action_fp)(event_t event, void* data);

/*!
    \brief     Callback function type for exit actions
    \details   Every state in a UML state chart can have an optional exit action, which is executed upon
               exit from a state. Exit actions are associated with states, not transitions. Regardless
               of how a state is left, its exit action will be executed.

   \param      event    Triggering event
   \param      data     Data associated with the event

*/
typedef void(*sm_exit_action_fp)(event_t event, void* data);


/*!
   \brief      Callback function type for transitions
   \details    Switching from one state to another is called state transition, and the event that causes
               it is called the triggering event, or simply the trigger. This function has to be
               implemented by the state machine designer for each state of the state machine.

   \param      event    Triggering event
   \param      data     Data associated with the event

   \returns    New state in case of external transition. Same state as before in case of
               self transition. NULL in case of internal or no transition.
*/
typedef const sm_state_t*(*sm_transitions_fp)(event_t event, void* data);

/*!
   \brief      Callback function type for transition effects
   \details    Switching from one state to another is called state transition.
               An effect specifies an optional behavior to be performed when the transition fires.
               The transition effect has to be set in the transition function and is invoked after
               exit of the source state and before entry of the target state.

   \param      event    Triggering event
   \param      data     Data associated with the event
*/
typedef void(*sm_transition_effect_fp)(event_t event, void* data);


/*!
    \brief     Callback function type for transition effects
    \details   Specifies an optional behavior to be performed when the transition fires.

 */
extern sm_transition_effect_fp sm_transition_effect; /*!< global variable for the transition effect */

/*!
   A state captures the relevant aspects of the system's history very efficiently.
   The state of an object is always determined by its attributes and associations. States in state chart
   diagrams represent a set of those value combinations, in which an object behaves the same in response
   to events.
*/
struct sm_state_t {
   sm_entry_action_fp entry_action;    /* entry action to be performed if the state gets entered */
   sm_transitions_fp transitions;      /* external,internal and self transitions of the state */
   sm_exit_action_fp exit_action;      /* xit action to be performed if the state gets exited */
};

/*!
    \brief     Statemachine declaration
    \details   Holds the current state and data associated with the statemachine.
*/
typedef struct {
   sm_state_t *state;      /*!< Current state of the statemachine */
   void *data;             /*!< (Object-) Data associated with the statemachine */
}sm_t;



#define sm_state_id(base_ptr,state_ptr) \
   ((state_ptr)-(base_ptr))



sm_state_t* sm_init(sm_t* sm, const sm_state_t* state);
void sm_terminate(sm_t *sm);
sm_state_t* sm_send(sm_t* sm, event_t event, void* data);

#endif /* SM_H_ */
