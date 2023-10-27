#include "menu.h"
#include "global.h"
#include "menu_function.h"

Menu::Menu() 
{
  menuFn[0] = fn101;
  menuFn[1] = fn201;
  menuFn[2] = fn301;
  menuFn[3] = fn401;
  menuFn[4] = fn501;
  menuFn[5] = fn502;
  
  setFunction = false;
  selectFunction = false;
}

void Menu::begin() 
{
  indexSelector.menu = 1;
  indexSelector.subMenu = 1;

  functionSelected = *menuFn[0];

  clear();
}

void Menu::clear() 
{
  display.clear();
}

void Menu::pause(bool paused)
{
  static bool isChanged = false;

  if(paused){
     display.print("PAUSED", 10, 0);
     isChanged = true;
  }
  else if (!paused && isChanged) {
    display.print("      ", 10, 0);
    isChanged = false;
  }
}

bool Menu::isSetMode() 
{
  return setFunction;
}

uint8_t Menu::setFnIndex(uint8_t menu, uint8_t submenu) 
{
  uint8_t indexOutput = 0;
  for (byte i = 0; i < (menu - 1); i++) {
      indexOutput += MENU_LENGTH[i + 1];
  }
  indexOutput += submenu - 1;

  return indexOutput;
}

void Menu::selectMenuIndex(int variation)
{
  if(setFunction){
    indexSelector.subMenu = constrain(
      indexSelector.subMenu + variation, 
      1, 
      MENU_LENGTH[indexSelector.menu] - 1
    );
  }
  else {
    indexSelector.menu = constrain(
      indexSelector.menu + variation, 
      1, 
      MENU_LENGTH[0]
    );
  }

  functionSelected = *menuFn[setFnIndex(indexSelector.menu, indexSelector.subMenu)];
}

void Menu::print()
{
  if(!setFunction)
  {
    display.print(MENU[0], 0, 0);
    display.print(MENU[indexSelector.menu], 0, 1);
  } else {
    display.print(MENU[indexSelector.menu], 0, 0);
  };

  functionSelected();
}

void Menu:: escape()
{
  selectFunction = false;
  setFunction = false;
  clear();
}
