#ifndef __gpiomcp23017_H__
#define __gpiomcp23017_H__

#if defined( GPIO_MCP23017 )
#include "gpiopin.h"
#include <Adafruit_MCP23017.h>

namespace Gpio
{

class MCP23017 : public Pin
{
	public:
		enum Pins
		{
			GPA0 = 0, GPA1, GPA2, GPA3, GPA4, GPA5, GPA6, GPA7,	//	Port A
			GPB0,	  GPB1, GPB2, GPB3, GPB4, GPB5, GPB6, GPB7,		//	Port B
		};

		MCP23017( uint8_t pin = 0, uint8_t mode = INPUT, bool isActiveHigh = true, int eepromOffset = 0 );

		void setInterface( void *intf );
		bool begin();
		
		bool isActive();
		void activate() const;
		void deactivate() const;

		inline Adafruit_MCP23017* mcp23017( Adafruit_MCP23017 *mcp23017 ) const;
		inline void setMCP23017( Adafruit_MCP23017 *mcp23017 );

	private:
		Adafruit_MCP23017 *m_mcp23017;
};

//	----- inline functions -----
Adafruit_MCP23017* MCP23017::mcp23017( Adafruit_MCP23017 *mcp23017 ) const
{
	return m_mcp23017;
}
void MCP23017::setMCP23017( Adafruit_MCP23017 *mcp23017 )
{	
	m_mcp23017 = mcp23017;
}

}

#endif
#endif