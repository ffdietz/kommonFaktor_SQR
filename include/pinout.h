#include <Arduino.h>

// #define PROTOTYPE_BOARD_PINOUT
#define METRIC_BOARD_PINOUT

#ifdef PROTOTYPE_BOARD_PINOUT
  #define SHIFT_REG_SCK         13  // to 74HC595 SH_CP [PIN 11]
  #define SHIFT_REG_MOSI        11  // to 74HC595 DS    [PIN 14]
  #define SHIFT_REG_LATCH_LCD   10  // to 74HC595 ST_CP [PIN 12]
  #define SHIFT_REG_LATCH_BTNS  8   // to 74HC595 ST_CP [PIN 12]

  #define ENCODER_A       2
  #define ENCODER_B       3
  #define ENCODER_SET     4

  #define MUX_A           5
  #define MUX_B           6
  #define MUX_C           7

  #define CLOCK_OUT       9
  #define CLOCK_IN        12

  #define PAUSE_BUTTON    A0
  #define STEP_CTRL_INPUT A1 

  #define LCD_CHARS 16
  #define LCD_LINES 2

  #define ENCODER_MIN -1000
  #define ENCODER_MAX 1000

#elif defined(METRIC_BOARD_PINOUT)
  #define REGISTER_SCK         13            // to 74HC595 SH_CP [PIN 11]
  #define REGISTER_MOSI        11           // to 74HC595 DS    [PIN 14]
  #define REGISTER_LATCH_LCD   10      // to 74HC595 ST_CP [PIN 12]
  #define REGISTER_LATCH_BTNS  A3 // to 74HC595 ST_CP [PIN 12]

  #define ENCODER_A     3
  #define ENCODER_B     2
  #define ENCODER_SET   A7

  #define MUX_A         A0
  #define MUX_B         10
  #define MUX_C         12
  #define MUX_INH       A5
  

  #define CLOCK_OUT     A2
  #define CLOCK_IN      A6

  #define PAUSE_BUTTON  A1
  #define BTNS_INPUT    A4
  
  #define LCD_RS        4
  #define LCD_EN        5
  #define LCD_D4        6
  #define LCD_D5        7
  #define LCD_D6        8
  #define LCD_D7        9

  #define LCD_CHARS 16
  #define LCD_LINES 2

  #define ENCODER_MIN -1000
  #define ENCODER_MAX 1000


#endif