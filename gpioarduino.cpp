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


bool Arduino::isActive() const 
{
	return	( isActiveHigh() && ( HIGH == digitalRead( pin() ) ) )
		||	( !isActiveHigh() && ( LOW == digitalRead( pin() ) ) );
}
void Arduino::activate() const 
{
	if( !isInput() )
		digitalWrite( pin(), isActiveHigh() ? HIGH : LOW );
}
void Arduino::deactivate() const 
{
	if( !isInput() )
		digitalWrite( pin(), isActiveHigh() ? LOW : HIGH );
}

}