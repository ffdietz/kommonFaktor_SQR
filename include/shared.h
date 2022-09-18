#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>

#include "global.h"
#include "controller.h"
#include "coordinates.h"

struct MenuField
{
  uint8_t x;
  uint8_t y;
  const char *label;
};

struct MenuLayout
{
  static const MenuField title;
  static const MenuField bpm;
  static const MenuField pause;
  static const MenuField step;
  static const MenuField stepStatesTitle;
  static const MenuField clockOptionTitle;

  void screen1();
  void screen2();
  void screen3();
};

const MenuField MenuLayout::title = {0, 0, " STEP SEQUENCER "};
const MenuField MenuLayout::pause = {0, 1, "  PAUSE  "};
const MenuField MenuLayout::bpm   = {0, 1, "BPM:"};
const MenuField MenuLayout::step  = {10, 1, "STEP:"};
const MenuField MenuLayout::stepStatesTitle  = {0, 1, "ACTIVE STEPS"};
const MenuField MenuLayout::clockOptionTitle = {0, 0, "CLOCK OPTIONS"};

#endif

// struct Label
// {
//   static const char *title;
//   static const char *bpm;
//   static const char *pause;
//   static const char *step;
//   static const char *stepStateTitle;
//   static const char *clockOptionTitle;
//   static const char *localClear1;
//   static const char *localClear2;
//   static const char *localClear3;
//   static const char *localClear4;

//   static const Coordinates titlePos;
//   static const Coordinates bpmPos;
//   static const Coordinates pausePos;
//   static const Coordinates stepPos;
//   static const Coordinates stepStatesPos;
// };

// const char *Label::title
// const char *Label::bpm =
// const char *Label::pause
// const char *Label::step
// const char *Label::stepStateTitle
// const char *Label::clockOptionTitle
// const char *Label::localClear1 = " ";
// const char *Label::localClear2 = "  ";
// const char *Label::localClear3 = "   ";
// const char *Label::localClear4 = "    ";

// const Coordinates Label::bpmPos
// const Coordinates Label::pausePos
// const Coordinates Label::stepPos
// const Coordinates Label::stepStatesPos