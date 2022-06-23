#ifndef GLOBAL_H
#define GLOBAL_H
#include <Arduino.h>

#include "controller.h"
#include "sequence.h"
#include "game.h"

// globals for player controls, game map, and overall game state
Controller control;
Sequence sequence(8);

// Game game(3);

#endif