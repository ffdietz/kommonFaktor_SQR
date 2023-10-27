#ifndef MENU_H_
#define MENU_H_
#include <Arduino.h>

class Menu {
  public:
    Menu();
    bool isSetMode();
    void clear();
    void begin();
    void print();
    void escape();
    void pause(bool paused);

    uint8_t setFnIndex(uint8_t menu, uint8_t submenu);
    void selectMenuIndex(int variation);
    bool setFunction;
    bool selectFunction;

    using funcPointer = void(*)();
    funcPointer functionSelected;
    funcPointer menuFn[6];

    struct menuIndexSelector {
      uint8_t menu;
      uint8_t subMenu;
    } indexSelector;

    const char* PAUSE = "PAUSED";

    const char* MENU[6] = { 
      "MUX_SQR", 
      "BPM ", 
      "CURRENT STEP ", 
      "SEQUENCE ", 
      "CLOCK FACTOR", 
      "RESET STEPS " 
    };

    const char* SUBMENU[9] = { 
      "ASCEND", "DESCEND", "RANDOM", "CUSTOM", 
      "IN", "OUT", 
      "ALL ON", "ALL OFF", "RETURN", 
    };

    const uint8_t MENU_LENGTH[6] = { 
      5, //ROOT
      1, //BPM
      1, //CURRENT STEP
      1, //SEQUENCE
      1, //CLOCK
      1, //RESET
    };

    const char* FACTOR[13] = { 
      "/64", "/32", "/16", "/8", "/4", "/2", 
      "1", "*2", "*4", "*8", "*16", "*32", "*64" 
    };
};

#endif