#include "menu.h"
#include "global.h"
#include "menuFunctions.h"

Menu::Menu() 
{
  menuFn[0] = fn101;
  menuFn[1] = fn201;
  menuFn[2] = fn301;
  menuFn[3] = fn401;
  menuFn[4] = fn501;
  menuFn[5] = fn601;
}

void Menu::begin() 
{
  indexSelector.menu = 1;
  indexSelector.subMenu = 1;

  functionSelected = *menuFn[0];

  selectFunction = false;
  setFunction = false;

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
    display.pause(15, 0);
    isChanged = true;
  }
  else if (!paused && isChanged) {
    display.print(" ", 15, 0);
    isChanged = false;
  }
}

bool Menu::isSetMode() 
{
  return selectFunction;
}

uint8_t Menu::setFnIndex(uint8_t menu, uint8_t submenu) 
{
  uint8_t indexOutput = 0;
  for(byte i = 0; i < menu - 1; i++) {
    indexOutput += MENU_LENGTH[i + 1];
  }
  indexOutput += submenu - 1;

  return indexOutput;
}

void Menu::selectIndex(int variation)
{
  if(selectFunction){
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
  if(!selectFunction)
  {
    display.print(MENU[0], 0, 0);
    display.print(MENU[indexSelector.menu], 0, 1);
  } else {
    display.print(MENU[indexSelector.menu], 0, 0);
  }
}

void Menu::escape()
{
  setFunction = false;
  selectFunction = false;
  clear();
}
