#ifndef __gpiolist_H__
#define __gpiolist_H__

#include <stdint.h>
#include "gpiopin.h"

namespace Gpio
{

class ListBase
{
	public:
		virtual uint8_t size() const = 0;
		virtual Pin* operator[]( uint8_t idx ) = 0;
#if defined( GPIO_NAME )
		virtual Pin* operator[]( const char *name ) = 0;
#endif
#if defined( GPIO_EEPROM )
		virtual void loadFromEeprom() = 0;
		virtual void saveToEeprom() const = 0;
		virtual uint16_t eepromSize() const = 0;
#endif
		virtual void setInterface( void *intf ) = 0;
		virtual bool begin() = 0;
		virtual void toggle() = 0;
		virtual void activate() = 0;
		virtual void deactivate() = 0;
		virtual void setMode( uint8_t mode ) = 0;
		virtual void setActiveHigh() = 0;
		virtual void setActiveLow() = 0;
};

template< uint8_t m_size, class GPIO >
class List : public ListBase
{
	public:
		inline uint8_t size() const;
		inline Pin* operator[]( uint8_t idx );
#if defined( GPIO_NAME )
		inline Pin* operator[]( const char *name );
#endif
#if defined( GPIO_EEPROM )
		void loadFromEeprom();
		void saveToEeprom() const;
		uint16_t eepromSize() const;
#endif
		void setInterface( void *intf );
		bool begin();
		void toggle();
		void activate();
		void deactivate();
		void setMode( uint8_t mode );
		void setActiveHigh();
		void setActiveLow();
	protected:
		GPIO m_pins[ m_size ];
};

//	----- functions -----
#if defined( GPIO_EEPROM )
template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::loadFromEeprom()
{
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].loadFromEeprom();
	}
}

template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::saveToEeprom() const
{
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].saveToEeprom();
	}
}

template< uint8_t m_size, class GPIO >
uint16_t List< m_size, GPIO >::eepromSize() const
{
	uint16_t size = 0;
	for( uint8_t i = 0; i < m_size; i++ )
	{
		size += m_pins[ i ].eepromSize();
	}
	return size;
}
#endif

template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::setInterface( void *intf )
{
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].setInterface( intf );
	}
}

template< uint8_t m_size, class GPIO >
bool List< m_size, GPIO >::begin() {
	bool result = true;
	for( uint8_t i = 0; i < m_size; i++ )
	{
		if( !m_pins[ i ].begin() )
			result = false;
	}
	return result;
}

template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::toggle() {
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].toggle();
	}
}

template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::activate() {
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].activate();
	}
}

template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::deactivate() 
{
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].deactivate();
	}
}

template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::setMode( uint8_t mode ) 
{
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].setMode( mode );
	}
}

template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::setActiveHigh() 
{
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].setActiveHigh();
	}	
}

template< uint8_t m_size, class GPIO >
void List< m_size, GPIO >::setActiveLow() 
{
	for( uint8_t i = 0; i < m_size; i++ )
	{
		m_pins[ i ].setActiveLow();
	}	
}

//	----- inline functions -----
template< uint8_t m_size, class GPIO >
inline uint8_t List< m_size, GPIO >::size() const
 {
	return m_size;
}

template< uint8_t m_size, class GPIO >
inline Pin* List< m_size, GPIO >::operator[]( uint8_t idx ) 
{
	if( idx < m_size )
		return dynamic_cast< Pin* >( &m_pins[ idx ] );

	return nullptr;
}

#if defined( GPIO_NAME )
template< uint8_t m_size, class GPIO >
inline Pin* List< m_size, GPIO >::operator[]( const char *name ) 
{
	Pin* pin = nullptr;
	if( name )
	{
		for( uint8_t i = 0; ( i < m_size ) && ( nullptr == pin ); i++ )
		{
			if( !strcmp( m_pins[ i ].name(), name ) )
				pin = dynamic_cast< Pin* >( &m_pins[ i ] );
		}
	}

	return pin;
}
#endif

}

#endif