#ifndef Temporizador_h
#define Temporizador_h
/* 
Title: Temporizador (a counter or timer )
Author: Bernardo Lpez Daz
Description: 
The class Temporizador defines the methods that implement the operation of a timer.
The loop method is invoked within the generic loop to update the counters.
The set method allows you to initialize a counter at a given value.
When you create an object of this class you have to pass the function to be called when the timer ends the account.
Once the account is finished, the timer does not restart.
*/
// includes files
#include "Arduino.h"

class Temporizador
{
  
  	public:
    	Temporizador(void (*_timeoutCallback)());
    	void set( uint32_t _counter);
    	void loop();

	private:
		uint32_t counter;
		void (*timeoutCallback)();
};

#endif
