#include <Arduino.h>
#include "gpioarduino.h"

namespace Gpio
{

//
//
Arduino::Arduino( uint8_t pin, uint8_t mode, bool activeHigh, int eepromOffset ) :
	Pin( pin, mode, activeHigh, eepromOffset ) 
{
	
}

//
//
bool Arduino::begin()
{
	pinMode( pin(), isInput() ? ( isPulledUp() ? INPUT_PULLUP : INPUT ) : OUTPUT );
	deactivate();	// only if ouput
	return true;
}

uint8_t Arduino::read()
{
	return digitalRead( pin() );
}

void Arduino::write( uint8_t state )
{
	digitalWrite( pin(), state );
}

}