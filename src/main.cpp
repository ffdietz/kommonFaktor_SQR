#include "shared.h"
#include "global.h"

PDQ_ST7735 tft;   // Creates LCD object 

void setup() 
{ 
  Serial.begin(115200);  
  tft.begin();
}

void loop()
{
}
