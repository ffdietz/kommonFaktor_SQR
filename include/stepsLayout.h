#ifndef STEPSLAYOUT_H
#define STEPSLAYOUT_H
#include <Arduino.h>
#include "configDraw.h"

// struct StepsLayout{
//   // all tiles are one of these values
//   static enum {
//     wall = 0,
//     dot = 1,         // small item
//     powerPellet = 2, // large item/powerup
//     barePath = 3,
//     nonPlayArea = 4 // same color as bare path (e.g. inside ghost box)
//   } mapStates;

//   // initialize with a clean layout
//   StepsLayout() {
//     initialLayout(uint8_t totalSteps);
//   }

//   // 2D map of tiles
//   uint8_t mapLayout[X_BOUND] = {};

//   // set all map tiles to their default state specified by blankMap
//   void initialLayout(uint8_t totalSteps) {
//       for (int8_t r = 0; r < totalSteps; ++r){
//         mapLayout[r] = 1;
//       }
//   }
// };


#endif