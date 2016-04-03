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
   \file       statemachine.c
   \version    0000
   \authors    marco@bacchi.at
   \date       2013

   \brief      Statemachine for testing purposes - implementation

   \details    This statemachine is for testing purposes. It defines three states
               and some testing transitions between the states. It also makes use of a guard
               condition and covers exit/entry actions, transition effects and internal transitions.

               \image html  sm_test_statemachine.png "Statemachine for testing purposes"
               \image latex sm_test_statemachine.png "Statemachine for testing purposes"  width=10cm

               __Changelist__

               Revision|Date    |Name  |Change
               --------|--------|------|-------------------------------------------------
               0000    |00.00.00|bacmar|Detailed Change Text
*/

#include"statemachine.h"
#include<stdbool.h>

#define DEBUG 1

#if DEBUG
   #include<stdio.h>
   #define DBG(...) printf(__VA_ARGS__)
#else
   #define DBG(...)
#endif

bool guard = false; /*!< Guard condition variable as used in UML state chart */

/*!
    \brief     State A entry function
    \details   Every state in a UML state chart can have an optional entry action, which is executed upon
               entry to a state. Entry actions are associated with states, not transitions. Regardless
               of how a state is entered, its entry action will be executed.

   \param      event    Triggering event
   \param      data     Data associated with the event

*/
void A_entry(event_t event, void* data)
{
   DBG("A Entry\n");
}

/*!
   \brief      State A transitions function
   \details    Switching from one state to another is called state transition, and the event that causes
               it is called the triggering event, or simply the trigger. This function has to be
               implemented by the state machine designer for each state of the state machine.

   \param      event    Triggering event
   \param      data     Data associated with the event

   \returns    New state in case of external transition. Same state as before in case of
               self transition. NULL in case of internal or no transition.
*/
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

/*!
    \brief     State A exit function
    \details   Every state in a UML state chart can have an optional exit action, which is executed upon
               exit from a state. Exit actions are associated with states, not transitions. Regardless
               of how a state is left, its exit action will be executed.

   \param      event    Triggering event
   \param      data     Data associated with the event

*/
void A_exit(event_t event, void* data)
{
   DBG("A Exit\n");
}




void BeC_transition_effect(event_t event, void* data)
{
   DBG("BeC Transition Effect\n");
}


/*!
   \brief      State B transitions function
   \details    Switching from one state to another is called state transition, and the event that causes
               it is called the triggering event, or simply the trigger. This function has to be
               implemented by the state machine designer for each state of the state machine.

   \param      event    Triggering event
   \param      data     Data associated with the event

   \returns    New state in case of external transition. Same state as before in case of
               self transition. NULL in case of internal or no transition.
*/
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

/*!
    \brief     State B exit function
    \details   Every state in a UML state chart can have an optional exit action, which is executed upon
               exit from a state. Exit actions are associated with states, not transitions. Regardless
               of how a state is left, its exit action will be executed.

   \param      event    Triggering event
   \param      data     Data associated with the event

*/
void B_exit(event_t event, void* data)
{
   DBG("B Exit\n");
}



/*!
    \brief     State C entry function
    \details   Every state in a UML state chart can have an optional entry action, which is executed upon
               entry to a state. Entry actions are associated with states, not transitions. Regardless
               of how a state is entered, its entry action will be executed.

   \param      event    Triggering event
   \param      data     Data associated with the event

*/
void C_entry(event_t event, void* data)
{
   DBG("C Entry\n");
}


/*!
   \brief      State C transitions function
   \details    Switching from one state to another is called state transition, and the event that causes
               it is called the triggering event, or simply the trigger. This function has to be
               implemented by the state machine designer for each state of the state machine.

   \param      event    Triggering event
   \param      data     Data associated with the event

   \returns    New state in case of external transition. Same state as before in case of
               self transition. NULL in case of internal or no transition.
*/
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




/*! Statemachine states table */
const sm_state_t statemachine_states[]= {
      {A_entry,      A_transitions,       A_exit},          /*!< State A table entry */
      {NULL,         B_transitions,       B_exit},          /*!< State B table entry */
      {C_entry,      C_transitions,       NULL}             /*!< State C table entry */
};

/*! Number of state entries in the state table */
const size_t statemachine_state_count = sizeof(statemachine_states)/sizeof(statemachine_states[0]);


