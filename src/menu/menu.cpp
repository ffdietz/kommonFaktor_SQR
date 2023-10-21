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
  
  setMenuFunction = false;
}

bool Menu::isSetMode() 
{
  return setMenuFunction;
}

void Menu::clear() 
{
  display.clear();
}

void Menu::begin() 
{
  indexSelector.menu = 1;
  indexSelector.subMenu = 1;

  menuFunction = *menuFn[0];

  clear();
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
  if(setMenuFunction){
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

  menuFunction = *menuFn[setFnIndex(indexSelector.menu, indexSelector.subMenu)];
}

void Menu::print()
{
  if(!setMenuFunction)
  {
    display.print(MENU[0], 0, 0);
    display.print(MENU[indexSelector.menu], 0, 1);
  } else {
    display.print(MENU[indexSelector.menu], 0, 0);
  };

  menuFunction();
}

void Menu::pause(bool paused)
{
  if(paused) display.print("PAUSED", 10, 0);
  else display.print("      ", 10, 0);
}
