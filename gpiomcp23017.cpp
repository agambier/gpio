#if defined( GPIO_MCP23017 )
#include "gpiomcp23017.h"

namespace Gpio
{

//
//
MCP23017::MCP23017( uint8_t pin, uint8_t mode, bool activeHigh, int eepromOffset ) :
	Pin( pin, mode, activeHigh, eepromOffset ),
	m_mcp23017( nullptr )
{
}

//
//
void MCP23017::setInterface( void *intf )
{
	m_mcp23017 = reinterpret_cast< Adafruit_MCP23017*>( intf );
}

//
//
bool MCP23017::begin()
{
	if( nullptr == m_mcp23017 )
		return false;

	m_mcp23017->pinMode( pin(), isInput() ? ( isPulledUp() ? INPUT_PULLUP : INPUT ) : OUTPUT );
	deactivate();	// only if ouput
	return true;
}

//
//
uint8_t MCP23017::read()
{
	if( nullptr == m_mcp23017 )
		return GPIO_UNDEFINED_STATE;

	return  m_mcp23017->digitalRead( pin() );
}

void MCP23017::write( uint8_t state )
{
	if( m_mcp23017 )
		m_mcp23017->digitalWrite( pin(), state );
}

}
#endif