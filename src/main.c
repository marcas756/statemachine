/*
 ============================================================================
 Name        : sm.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "statemachine.h"

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
