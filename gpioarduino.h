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
		
		bool isActive();
		void activate() const;
		void deactivate() const;
};

//	----- inline functions -----

}
#endif