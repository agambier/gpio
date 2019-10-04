#ifndef __gpiopin_H__
#define __gpiopin_H__

#include <Arduino.h>
#include <stdint.h>

namespace Gpio
{

#define GPIO_NAME_SIZE		16
class Pin
{
	public:
		Pin( uint8_t pin, uint8_t mode, bool isActiveHigh, int eepromOffset );

		virtual void setInterface( void *intf );
		virtual bool begin() = 0;
		
#if defined( GPIO_EEPROM )
		inline void setEepromOffset( int eepromOffset );
		inline int eepromOffset() const;
		void loadFromEeprom();
		void saveToEeprom() const;
		inline uint8_t eepromSize() const;
#endif

		inline void setPin( uint8_t pin );
		inline uint8_t pin() const;
	
		void setMode( uint8_t mode );
		inline bool isInput() const;
		inline bool isPulledUp() const;
		
		inline void setActiveLow();
		inline void setActiveHigh();
		inline bool isActiveHigh() const;

		virtual bool isActive() const = 0;
		virtual void activate() const = 0;
		virtual void deactivate() const = 0;
		inline void toggle() const;

#if defined( GPIO_NAME )
		inline const char* name() const;
		inline void setName( const char *name );
#endif

	private:
#if defined( GPIO_EEPROM )
		int m_eepromOffset;
#endif
		uint8_t m_pin;
		uint8_t m_mask;
#if defined( GPIO_NAME )
		char m_name[ GPIO_NAME_SIZE ];
#endif		

		enum MaskBit
		{
			Input = 0x01,			//	b'00000001'
			PullUp = 0x02,			//	b'00000010'
			ActiveHigh = 0x04		//	b'00000100'
		};
};

//	----- inline functions -----
#if defined( GPIO_EEPROM )
void Pin::setEepromOffset( int eepromOffset ) 
{
	m_eepromOffset = eepromOffset;
}
int Pin::eepromOffset() const 
{
	return m_eepromOffset;
}
uint8_t Pin::eepromSize() const 
{
	return	  sizeof( m_pin ) 
#if defined( GPIO_NAME )
	 		+ sizeof( m_name )
#endif
			+ sizeof( m_mask );
}
#endif
void Pin::setPin( uint8_t pin ) 
{
	m_pin = pin;
}
uint8_t Pin::pin() const 
{
	return m_pin;
}
bool Pin::isInput() const 
{
	return ( m_mask & Pin::Input );
}
bool Pin::isPulledUp() const 
{
	return ( m_mask & Pin::PullUp );
}
void Pin::setActiveHigh()
{
	m_mask |= Pin::ActiveHigh;
}
bool Pin::isActiveHigh() const 
{
	return ( m_mask & Pin::ActiveHigh );
}
void Pin::setActiveLow()
{
	m_mask &= ( ~Pin::ActiveHigh );
}
void Pin::toggle() const 
{
	isActive() ? deactivate() : activate() ;
}
#if defined( GPIO_NAME )
const char* Pin::name() const {
	return m_name;
}
void Pin::setName( const char *name ) {
	strncpy( m_name, name, GPIO_NAME_SIZE );
	m_name[ GPIO_NAME_SIZE - 1 ] = 0;
}
#endif

}
#endif