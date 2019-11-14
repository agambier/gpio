#ifndef __gpioarduino_H__
#define __gpioarduino_H__

#include "gpiopin.h"

namespace Gpio
{

class Arduino : public Pin
{
	public:
		Arduino( uint8_t pin = 0, uint8_t mode = INPUT, bool isActiveHigh = true, int eepromOffset = 0 );

		bool begin();
	protected:
		uint8_t read();
		void write( uint8_t state );
};

//	----- inline functions -----

}
#endif