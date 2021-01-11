#ifndef LCD_h
#define LCD_h

#include "Arduino.h"
#include "Print.h"
#include "LDC.h"

// commands
#define LCD_CLEARDISPLAY 0x01 //!< Clear display, set cursor position to zero
#define LCD_RETURNHOME 0x02   //!< Set cursor position to zero
#define LCD_ENTRYMODESET 0x04 //!< Sets the entry mode
#define LCD_DISPLAYCONTROL                                                     \
  0x08 //!< Controls the display; does stuff like turning it off and on
#define LCD_CURSORSHIFT 0x10 //!< Lets you move the cursor
#define LCD_FUNCTIONSET                                                        \
  0x20 //!< Used to send the function to set to the display
#define LCD_SETCGRAMADDR                                                       \
  0x40 //!< Used to set the CGRAM (character generator RAM) with characters
#define LCD_SETDDRAMADDR 0x80 //!< Used to set the DDRAM (Display Data RAM)

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00 //!< Used to set text to flow from right to left
#define LCD_ENTRYLEFT 0x02  //!< Uset to set text to flow from left to right
#define LCD_ENTRYSHIFTINCREMENT                                                \
  0x01 //!< Used to 'right justify' text from the cursor
#define LCD_ENTRYSHIFTDECREMENT                                                \
  0x00 //!< Used to 'left justify' text from the cursor

// flags for display on/off control
#define LCD_DISPLAYON 0x04  //!< Turns the display on
#define LCD_DISPLAYOFF 0x00 //!< Turns the display off
#define LCD_CURSORON 0x02   //!< Turns the cursor on
#define LCD_CURSOROFF 0x00  //!< Turns the cursor off
#define LCD_BLINKON 0x01    //!< Turns on the blinking cursor
#define LCD_BLINKOFF 0x00   //!< Turns off the blinking cursor

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08 //!< Flag for moving the display
#define LCD_CURSORMOVE 0x00  //!< Flag for moving the cursor
#define LCD_MOVERIGHT 0x04   //!< Flag for moving right
#define LCD_MOVELEFT 0x00    //!< Flag for moving left

// flags for function set
#define LCD_8BITMODE 0x10 //!< LCD 8 bit mode
#define LCD_4BITMODE 0x00 //!< LCD 4 bit mode
#define LCD_2LINE 0x08    //!< LCD 2 line mode
#define LCD_1LINE 0x00    //!< LCD 1 line mode
#define LCD_5x10DOTS 0x04 //!< 10 pixel high font mode
#define LCD_5x8DOTS 0x00  //!< 8 pixel high font mode

/*!
 * @brief Main LiquidCrystal class
 */
class Adafruit_LiquidCrystal : public Print {
public:
 
  Adafruit_LiquidCrystal(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1,
                         uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5,
                         uint8_t d6, uint8_t d7);
  
  Adafruit_LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0,
                         uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
                         uint8_t d5, uint8_t d6, uint8_t d7);
  
  Adafruit_LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0,
                         uint8_t d1, uint8_t d2, uint8_t d3);
  
  Adafruit_LiquidCrystal(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1,
                         uint8_t d2, uint8_t d3);

  
  Adafruit_LiquidCrystal(uint8_t i2cAddr);
  
  Adafruit_LiquidCrystal(uint8_t data, uint8_t clock, uint8_t latch);

  
  void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
            uint8_t d5, uint8_t d6, uint8_t d7);

  
  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

  
  void clear();
  
  void home();
  
  void noDisplay();
 
  void display();
  
  void noBlink();
  
  void blink();
  
  void noCursor();
  
  void cursor();
  
  void scrollDisplayLeft();
  
  void scrollDisplayRight();
  
  void leftToRight();
  
  void rightToLeft();
  
  void autoscroll();
  
  void noAutoscroll();

  
  void setBacklight(uint8_t status);

  
  void createChar(uint8_t, uint8_t[]);
  
  void setCursor(uint8_t, uint8_t);
#if ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void write(uint8_t);
#endif
  
  void command(uint8_t);

private:
  void send(uint8_t value, boolean mode);
  void write4bits(uint8_t);
  void write8bits(uint8_t);
  void pulseEnable();
  void _digitalWrite(uint8_t, uint8_t);
  void _pinMode(uint8_t, uint8_t);

  uint8_t _rs_pin;     // LOW: command.  HIGH: character.
  uint8_t _rw_pin;     // LOW: write to LCD.  HIGH: read from LCD.
  uint8_t _enable_pin; // activated by a HIGH pulse.
  uint8_t _data_pins[8];

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _initialized;

  uint8_t _numlines, _currline;

  uint8_t _SPIclock, _SPIdata, _SPIlatch;
  uint8_t _SPIbuff;

  uint8_t _i2cAddr;
  Adafruit_MCP23008 _i2c;
};

#endif
