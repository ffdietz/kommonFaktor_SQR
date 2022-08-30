#include <Arduino.h>
#include <LiquidCrystal.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include "pinout.h"

LiquidCrystal lcd(LCD_RS, LCD_RW, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

ClickEncoder *encoder;
ClickEncoder::Button button;

// Input & Button Logic
const int numOfInputs = 4;
const int inputPins[numOfInputs] = {2, 3, 4};

int inputState[numOfInputs];

int lastInputState[numOfInputs] = {LOW, LOW, LOW, LOW};
bool inputFlags[numOfInputs] = {LOW, LOW, LOW, LOW};
long lastDebounceTime[numOfInputs] = {0, 0, 0, 0};

long debounceDelay = 10;

// LCD Menu Logic
const int numOfScreens = 10;
int currentScreen = 0;

int parameters[numOfScreens];

uint8_t menuCount = 0;
uint8_t first = 1;
uint8_t lfirst = 0;
uint8_t count = 0;
uint8_t line = 0;
volatile uint8_t current = 1;
uint8_t lCurrent = 0;
uint8_t i = 0;
uint8_t j = 0;
boolean again = true;
uint8_t maxLines = 10; // numOfScreens

uint8_t encoderCheck()
{
  switch (encoder->getValue())
  {
    case 0:
      button = encoder->getButton();
      switch (button)
      {
      case ClickEncoder::Clicked:
      case ClickEncoder::DoubleClicked:
        again = false;
        break;

      case ClickEncoder::Held:
        while (encoder->getButton() != ClickEncoder::Released)
          ;
        again = false;
        break;
      }
      break;

    case 1:
      if (current > 1)
      {
        current--;
        if (current < first)
          first--;
      }
      break;

    case -1:
      if (current < menuCount - 1)
      {
        current++;
        if (current > maxLines - 1)
          first = current - maxLines + 2;
      }
      break;
    }

  return current;
}

String screens[numOfScreens][2] =
{
  {"Motor Voltage",   " Volts"},
  {"Motor Current",   " Amps"},
  {"Motor Rated HP",  " HP"},
  {"Overload Temp.",  " degC"},
  {"Accel Time",      " Secs"},
  {"Restart Time",    " Mins"},
  {"Analog Curr.",    " mA"},
  {"Input Temp.",     " degC"},
  {"Run Time",        " Hours"},
  {"Start Times",     " times"}
};

void printScreen()
{
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(screens[currentScreen][0]);
  lcd.setCursor(0, 2);
  lcd.print(parameters[currentScreen]);
  lcd.print(screens[currentScreen][1]);
}

void parameterChange(int key)
{
  if (key == 0)
  {
    parameters[currentScreen]++;
  }
  else if (key == 1)
  {
    parameters[currentScreen]--;
  }
}

void inputAction(int input)
{
  if (input == 0)
  {
    if (currentScreen == 0)
    {
      currentScreen = numOfScreens - 1;
    }
    else
    {
      currentScreen--;
    }
  }
  else if (input == 1)
  {
    if (currentScreen == numOfScreens - 1)
    {
      currentScreen = 0;
    }
    else
    {
      currentScreen++;
    }
  }
  else if (input == 2)
  {
    parameterChange(0);
  }
  else if (input == 3)
  {
    parameterChange(1);
  }
}

void setInputFlags()
{
  for (int i = 0; i < numOfInputs; i++)
  {
    int reading = digitalRead(inputPins[i]);
    if (reading != lastInputState[i])
    {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay)
    {
      if (reading != inputState[i])
      {
        inputState[i] = reading;
        if (inputState[i] == HIGH)
        {
          inputFlags[i] = HIGH;
        }
      }
    }
    lastInputState[i] = reading;
  }
}

void resolveInputFlags()
{
  for (int i = 0; i < numOfInputs; i++)
  {
    if (inputFlags[i] == HIGH)
    {
      inputAction(i);
      inputFlags[i] = LOW;
      printScreen();
    }
  }
}

void timerIsr()
{
  encoder->service();
}


void menuStart()
{
  encoder = new ClickEncoder(ENCODER_A, ENCODER_B, ENCODER_SET, 2); // 4 pulses per option

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);

  for (int i = 0; i < numOfInputs; i++)
  {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  lcd.begin(LCD_CHARS, LCD_LINES);
  lcd.clear();
}

void menuRun()
{
  setInputFlags();
  resolveInputFlags();
  lcd.setCursor(0, 0);
  lcd.print(millis());
  
  lcd.setCursor(0, 4);
  lcd.print(encoderCheck());
}