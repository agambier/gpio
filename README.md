# GPIO Arduino Library

This is a C++ library to handle GPIOs on Arduino boards and Arduino compatible ones.

**Features**

- GPIO list support
- Ease of use to change from one GPIO kind to another

**Supported hardware**

- CPU internal GPIOs
- MCP23017 I2C I/O expander

**Dependencies**

When using MCP23017 I/O expander [Adafruit MCP23017 Arduino Library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library) is required.

To support INPUT_PULLUP with MCP23017 use [Adafruit MCP23017 fork](https://github.com/agambier/Adafruit-MCP23017-Arduino-Library/commit/2941ef52f8bec86288490fad6afd46b8215a300f) (until pull request of this feature has been accepted).

**License**

This library is under MIT Licenses (see [LICENSE](LICENSE)).