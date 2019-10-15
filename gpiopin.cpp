#include <Arduino.h>
#if defined( GPIO_EEPROM )
#	include <EEPROM.h>
#endif
#include "gpiopin.h"

namespace Gpio
{

//
//
Pin::Pin( uint8_t pin, uint8_t mode, bool activeHigh, int eepromOffset ) :
#if defined( GPIO_EEPROM )
	m_eepromOffset( eepromOffset ),
#endif
	m_pin( pin ),
	m_mask( 0 ),
	m_filter( 0 ),
	m_filterTO( 50 ),
	m_lastActiveState( false )
{
#if defined( GPIO_NAME )
	m_name[ 0 ] = 0;
#endif
	setMode( mode );
	activeHigh ? setActiveHigh() : setActiveLow();
}

//
//
void Pin::setInterface( void */*intf*/ )
{
	// EMPTY FUNCTION
}

#if defined( GPIO_EEPROM )
//
//
void Pin::loadFromEeprom()
{
	int offset = m_eepromOffset;
	//	pin number
	EEPROM.get( offset, m_pin );
	offset += sizeof( m_pin );
	//	mask
	EEPROM.get( offset, m_mask );
	offset += sizeof( m_mask );
#if defined( GPIO_NAME )
	//	name
	EEPROM.get( offset, m_name );
	//offset += sizeof( m_name );
#endif
}

//
//
void Pin::saveToEeprom() const
{
	int offset = m_eepromOffset;
	//	pin number
	EEPROM.put( offset, m_pin );
	offset += sizeof( m_pin );
	//	mask
	EEPROM.put( offset, m_mask );
	offset += sizeof( m_mask );
#if defined( GPIO_NAME )
	//	name
	EEPROM.put( offset, m_name );
	//offset += sizeof( m_name );
#endif
}
#endif

//
//
void Pin::setMode( uint8_t mode ) 
{
	m_mask &= ~(  Pin::Input |  Pin::PullUp );
	if( OUTPUT != mode )
	{
		m_mask |= Pin::Input;
		if( INPUT_PULLUP == mode )
			m_mask |= Pin::PullUp;
	}
}

//
//
bool Pin::filterActiveState( bool isActive )
{
	if( !( m_mask & Pin::Filtered ) )
		return isActive;

	//	need filtering ?
	if( isActive && ( m_lastActiveState != isActive ) )
	{	
		//	start filtering ?
		if( 0 == m_filter )
			m_filter = millis();

		//	Accept new state
		if( ( millis() - m_filter ) >= m_filterTO )
			m_lastActiveState = isActive;

		return m_lastActiveState;
	}

	//	Filter is done
	//	for Edge trigerring force to false
	if( isActive && ( m_mask & Pin::EdgeTrigger ) )
		return false;

	//	raz
	m_lastActiveState = isActive;
	m_filter = 0;
	return m_lastActiveState;
}

}