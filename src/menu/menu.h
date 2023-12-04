#ifndef MENU_H_
#define MENU_H_
#include <Arduino.h>

class Menu {
  public:
    Menu();

    void clear();
    void begin();
    void print();
    void escape();
    void pause(bool paused);
    bool isSetMode();

    uint8_t setFnIndex(uint8_t menu, uint8_t submenu);
    void selectIndex(int variation);
    bool selectFunction;
    bool setFunction;

    using funcPointer = void(*)();
    funcPointer functionSelected;
    funcPointer menuFn[7];

    struct menuIndexSelector {
      uint8_t menu;
      uint8_t subMenu;
    } indexSelector;

    const char* PAUSE = "PAUSED";

    const uint8_t MENU_LENGTH[7] = { 
      6, //ROOT
      1, //BPM
      1, //CURRENT STEP
      1, //SEQUENCE
      1, //CLOCK
      1, //RESET
      1, //CUSTOM SEQUENCE
    };

    const char* MENU[7] = { 
      "MUX_SQR", 
      "BPM ", 
      "CURRENT STEP ", 
      "PROGRESSION ", 
      "CLOCK FACTOR", 
      "RESET STEPS ", 
      "STEPS SEQUENCE"
    };

    const char* SUBMENU[9] = { 
      "ASCEND", "DESCEND", "RANDOM", "CUSTOM", 
      "IN", "OUT", 
      "ALL ON", "ALL OFF", "RETURN", 
    };

    const char* FACTOR[13] = { 
      "/64", "/32", "/16", "/8", "/4", "/2", 
      "1", "*2", "*4", "*8", "*16", "*32", "*64" 
    };
};

#endif