#include "Temporizador.h"

/******* PUBLIC FUNCTIONS RELATED WITH SLAVES AND BASIC BOARDS        ************************/


Temporizador::Temporizador(void (*_timeoutCallback)())
{
  counter 				      = 0;
  timeoutCallback = _timeoutCallback;
}

void Temporizador::set(uint32_t _counter){
	counter 		= millis()+_counter;
	if (counter <millis()){
		counter = 0xFFFFFFFF;
	}
}
void Temporizador::loop(){
	if (counter == 0){
		return;
	}
	if(counter <= millis()){
		counter = 0;
		timeoutCallback();
	}
}
