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
		enum TriggerMode
		{
			Level,
			Edge,
		};

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

		inline TriggerMode triggerMode() const;
		inline void setTriggerMode( TriggerMode mode );

		virtual bool isActive() = 0;
		virtual void activate() const = 0;
		virtual void deactivate() const = 0;
		inline void toggle();

		inline bool isFiltered() const;
		inline void setFilter( bool enable, uint16_t filterTO = 0 );

#if defined( GPIO_NAME )
		inline const char* name() const;
		inline void setName( const char *name );
#endif

	protected:
		bool filterActiveState( bool isActive );

	private:
#if defined( GPIO_EEPROM )
		int m_eepromOffset;
#endif
		uint8_t m_pin;
		uint8_t m_mask;
		uint32_t m_filter;
		uint16_t m_filterTO;
		bool m_lastActiveState;
#if defined( GPIO_NAME )
		char m_name[ GPIO_NAME_SIZE ];
#endif		

		enum MaskBit
		{
			Input = 1 << 0,			
			PullUp = 1 << 1,	
			ActiveHigh = 1 << 2,	
			Filtered = 1 << 4,
			EdgeTrigger = 1 << 5
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
void Pin::toggle()  
{
	isActive() ? deactivate() : activate() ;
}
bool Pin::isFiltered() const
{
	return ( m_mask & Pin::Filtered );
}
void Pin::setFilter( bool enable, uint16_t filterTO ) 
{
	if( enable )
		m_mask |= Pin::Filtered;
	else
		m_mask &= ~Pin::Filtered;

	if( filterTO )
		m_filterTO = filterTO;
}
Pin::TriggerMode Pin::triggerMode() const
{
	return ( m_mask & Pin::EdgeTrigger ) ? Pin::Edge : Pin::Level ;
}
void Pin::setTriggerMode( TriggerMode mode )
{
	if( Pin::Edge == mode )
		m_mask |= Pin::EdgeTrigger;
	else
		m_mask &= ~Pin::EdgeTrigger;
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