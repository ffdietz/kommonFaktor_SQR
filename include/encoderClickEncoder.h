// #include <ClickEncoder.h>
// #include <TimerOne.h>
// #include "pinout.h"

// ClickEncoder *encoder;
// ClickEncoder::Button button;

// // Input & Button Logic
// const int numOfInputs = 4;
// const int inputPins[numOfInputs] = {A1, A2, A0};

// int inputState[numOfInputs];

// bool inputFlags[numOfInputs] = {LOW, LOW, LOW, LOW};
// int lastInputState[numOfInputs] = {LOW, LOW, LOW, LOW};
// long lastDebounceTime[numOfInputs] = {0, 0, 0, 0};
// long debounceDelay = 10;

// uint8_t current = 1;
// uint8_t menuCount = 0;
// uint8_t first = 1;
// uint8_t lfirst = 0;
// uint8_t count = 0;
// uint8_t line = 0;
// uint8_t lCurrent = 0;
// uint8_t i = 0;
// uint8_t j = 0;
// boolean again = true;
// uint8_t maxLines = 10; // numOfScreens

// uint8_t encoderCheck()
// {
//   switch (encoder->getValue())
//   {
//   case 0:
//     button = encoder->getButton();
//     switch (button)
//     {
//     case ClickEncoder::Clicked:
//     case ClickEncoder::DoubleClicked:
//       again = false;
//       break;

//     case ClickEncoder::Held:
//       while (encoder->getButton() != ClickEncoder::Released)
//         ;
//       again = false;
//       break;
//     }
//     break;

//   case 1:
//     if (current > 1)
//     {
//       current--;
//     }
//     break;

//   case -1:
//     if (current < menuCount - 1)
//     {
//       current++;
//     }
//     break;
//   }

//   return current;
// }

// void parameterChange(int key)
// {
//   if (key == 0)
//   {
//     parameters[currentScreen]++;
//   }
//   else if (key == 1)
//   {
//     parameters[currentScreen]--;
//   }
// }

// void inputAction(int input)
// {
//   if (input == 0)
//   {
//     if (currentScreen == 0)
//     {
//       currentScreen = numOfScreens - 1;
//     }
//     else
//     {
//       currentScreen--;
//     }
//   }
//   else if (input == 1)
//   {
//     if (currentScreen == numOfScreens - 1)
//     {
//       currentScreen = 0;
//     }
//     else
//     {
//       currentScreen++;
//     }
//   }
//   else if (input == 2)
//   {
//     parameterChange(0);
//   }
//   else if (input == 3)
//   {
//     parameterChange(1);
//   }
// }

// void setInputFlags()
// {
//   for (int i = 0; i < numOfInputs; i++)
//   {
//     int reading = digitalRead(inputPins[i]);
    
//     if (reading != lastInputState[i]) lastDebounceTime[i] = millis();

//     if ((millis() - lastDebounceTime[i]) > debounceDelay)
//     {
//       if (reading != inputState[i])
//       {
//         inputState[i] = reading;
//         if (inputState[i] == HIGH)
//         {
//           inputFlags[i] = HIGH;
//         }
//       }
//     }
//     lastInputState[i] = reading;
//   }
// }

// void resolveInputFlags()
// {
//   for (int i = 0; i < numOfInputs; i++)
//   {
//     if (inputFlags[i] == HIGH)
//     {
//       inputAction(i);
//       inputFlags[i] = LOW;
//       // printScreen();
//     }
//   }
// }

// void timerIsr()
// {
//   encoder->service();
// }

// void encoder_begin()
// {
//   encoder = new ClickEncoder(ENCODER_A, ENCODER_B, ENCODER_SET, 2); // 4 pulses per option

//   Timer1.initialize(1000);
//   Timer1.attachInterrupt(timerIsr);
// }

// int16_t lastValue = -1, encoderValue = 0;


// void encoder_run()
// {
//   encoderValue += encoder->getValue();
//   // encoderValue = encoderCheck();

//   if (encoderValue != lastValue)
//   {
//     lastValue = encoderValue;
//     Serial.print("Encoder Value: ");
//     Serial.println(encoderValue);
//   }
// }