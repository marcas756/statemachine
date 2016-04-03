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
   \file       main.c
   \version    0000
   \authors    marco@bacchi.at
   \date       2013

   \brief      Main entry point of application

   \details    Test Application for testing purposes during development. Has to be replaced with a
               unittest

               __Changelist__

               Revision|Date    |Name  |Change
               --------|--------|------|-------------------------------------------------
               0000    |00.00.00|bacmar|Detailed Change Text

*/

#include <stdio.h>
#include <stdlib.h>
#include "statemachine.h"

/*!
   \brief      Main entry point
   \details    Initializes a designed and implemented statemachine with its initial state.
               Gets input from keyboard and forwards it as event to the statemachine.
               Valid events are from a to e.


   \returns    EXIT_SUCCESS in case of success. Otherwise EXIT_FAILURE.

*/
int main(void) {
	sm_t mysm;
	sm_state_t* current;

	current = sm_init(&mysm, &statemachine_states[A]);

	printf("Initial state : %c\n",'A'+(char)sm_state_id(statemachine_states,current));


	while(1)
	{
	   char c;
	   printf("Enter Event: ");
	   c = getchar();
	   getchar(); /* skip new line character */
	   current = sm_send(&mysm,c-'a',NULL);
	   printf("Current state : %c\n",'A'+(char)sm_state_id(statemachine_states,current));

	}



	return EXIT_SUCCESS;
}
