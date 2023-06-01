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
   \file       statemachine.h
   \version    0000
   \authors    marco@bacchi.at
   \date       2013

   \brief      Statemachine for testing purposes - interface

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

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "sm.h"
#include "stddef.h"

/*!
    \brief     Enumeration of events
    \details
*/
typedef enum {
   a,    /*!< Special event used for transiting from state A to state C */
   b,    /*!< Same as event a, but this time for transition from state C to state B */
   c,    /*!< Event used for transition from state B to A */
   d,    /*!< Event used to demonstrate a trnsition with an external guard condition */
   e     /*!< Event used to demonstrate an extrnal transition with a transition effect */
}statemachine_event_t;

/*!
    \brief     Enumeration of states
    \details   Enumeration of states of the state machine. This enumeration
               has to match with the entries in the state table!
*/
typedef enum {
   A,    /*!< State with entry/exit action, an internal transition, and external transition and an external contition with guard condition */
   B,    /*!< State with exit action, an external tranistion and another external transition with a transition effect */
   C     /*!< State with entry action, internal tranition and eternal transition */
}statemachine_states_t;


extern const sm_state_t statemachine_states[];
extern const size_t statemachine_state_count;

#endif /* STATEMACHINE_H_ */
