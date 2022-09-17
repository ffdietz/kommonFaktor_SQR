#ifndef SHARED__H_
#define SHARED__H_

#include <Arduino.h>

#include "global.h"
#include "controller.h"
#include "coordinates.h"

struct  Label
{
  static const char *title;
  static const char *bpm;
  static const char *pause;
  static const char *step;
  static const char *stepStateTitle;
  static const char *clockOptionTitle;

  static const Coordinates titlePos;
  static const Coordinates bpmPos;
  static const Coordinates pausePos;
  static const Coordinates stepPos;
  static const Coordinates stepStatesPos;
};

const char *Label::title = " STEP SEQUENCER ";
const char *Label::pause = "  PAUSE  ";
const char *Label::bpm = "BPM:";
const char *Label::step = "STEP:";
const char *Label::stepStateTitle = "  ACTIVE STEPS  ";
const char *Label::clockOptionTitle = " CLOCK OPTIONS  ";

const Coordinates Label::titlePos   = {0, 0};
const Coordinates Label::bpmPos     = {0, 1};
const Coordinates Label::pausePos   = {0, 1};
const Coordinates Label::stepPos    = {10, 1};
const Coordinates Label::stepStatesPos = {0, 0};

#endif
