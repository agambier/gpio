#include <Arduino.h>
#include <gpiolist.h>
#include <gpioarduino.h>
#include <gpiomcp23017.h>

//#define TEST_MCP23017

#if !defined( TEST_MCP23017 )
//	Define a list of 2 GPIOs handled by the CPU
Gpio::List< 2, Gpio::Arduino > g_gpios;
#else
//	Define a list of 2 GPIOs handled by a MCP23017
Gpio::List< 2, Gpio::MCP23017 > g_gpios;
//	Define the MCP23017 interface
Adafruit_MCP23017 g_mcp23017;
#endif

void setup() {
	//	Initialize serial port
	Serial.begin( 115200 );
	Serial.println();
	Serial.println( "GPIO Library" );

	Gpio::Pin *gpio;
	//	Initialize GPIO #0
	//		Output - Active High
	gpio = g_gpios[ 0 ];
	gpio->setMode( OUTPUT );
	gpio->setActiveHigh();
#if !defined( TEST_MCP23017 )	
	gpio->setPin( 2 ); // D2
#else
	gpio->setPin( Gpio::MCP23017::GPB0 );	//	Pin GPB0
#endif

	//	Initialize GPIO #1
	//		Input - Active High - Pulled Up
	//		NOTICE: To support INPUT-PULLUP with MCP23017
	//				Use Adafruit MCP213017 fork (https://github.com/agambier/Adafruit-MCP23017-Arduino-Library/commit/2941ef52f8bec86288490fad6afd46b8215a300f)
	gpio = g_gpios[ 1 ];
	gpio->setMode( INPUT_PULLUP );
	gpio->setActiveHigh();
#if !defined( TEST_MCP23017 )	
	gpio->setPin( 3 ); // D3
#else
	gpio->setPin( Gpio::MCP23017::GPA7 );	//	Pin GPA7
#endif

	//	Initialize all GPIOs
#if defined( TEST_MCP23017 )	
	g_mcp23017.begin( 0x00 );
	g_gpios.setInterface( &g_mcp23017 );
#endif
	g_gpios.begin();

	//	Ready !
	Serial.println( "Ready !" );
}

void loop() {
	if( g_gpios[ 1 ]->isActive() )
	{
		Serial.println( "is active" );
		g_gpios[ 0 ]->activate();
	}
	else
	{
		Serial.println( "is not active" );
		g_gpios[ 0 ]->deactivate();
	}
	delay( 1000 );
}