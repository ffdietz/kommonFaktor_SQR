#ifndef MENU_H_
#define MENU_H_

#include "display/display.h"

class Menu {
  public:
    Menu();

    bool isSetMode();
    void clear();
    void begin();
    void print();
    void pause(bool paused);
    void selectMenuIndex(int variation);
    uint8_t setFnIndex(uint8_t menu, uint8_t submenu);
    bool setMenuFunction;

    using funcPointer = void(*)();
    funcPointer menuFunction;
    funcPointer menuFn[6];

    struct menuIndexSelector {
        uint8_t menu;
        uint8_t subMenu;
    } indexSelector;

    const char * MN000 = "MUX_SQR";
    const char * MN100 = "BPM ";
    const char * MN200 = "STEP ";
    const char * MN300 = "SEQUENCE ";
    const char * MN301 = "ASCEND";
    const char * MN302 = "DESCEND";
    const char * MN303 = "RANDOM";
    const char * MN304 = "CUSTOM";
    const char * MN305 = "RESET";
    const char * MN400 = "CLOCK ";
    const char * MN401 = "IN";
    const char * MN402 = "OUT";
    const char * MN500 = "STEPS ";

    const char* MENU[6] = { 
      MN000, 
      MN100, 
      MN200, 
      MN300, 
      MN400, 
      MN500 
    };

    const char* SUBMENU[7] = { 
      MN301, 
      MN302, 
      MN303, 
      MN304, 
      MN305, 
      MN401, 
      MN402 
    };

    const uint8_t MENU_LENGTH[6] = { 
      6, 
      1, 
      1, 
      1, 
      1, 
      1 
    };

    const char* FACTOR[13] = { 
      "/64", "/32", "/16", "/8", "/4", "/2", 
      "1", "*2", "*4", "*8", "*16", "*32", "*64" 
    };
};

#endif