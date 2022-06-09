#include <Arduino.h>
#include <SPI.h> 

#include <avdweb_Switch.h>

#define SHR_LATCH 10  //to 74HC595 ST_CP [PIN 12]
#define SHR_CLOCK 13  //to 74HC595 SH_CP [PIN 11]
#define SHR_DATA  11  //to 74HC595 DS [PIN 14]

byte Input, Output, Check=1;
int j;

void pin_read()
{
  // for(j=0; j<50; j++) delayMicroseconds(1000);

  Check=1;

  for(j=0; j<8; j++)
  {
    SPI.transfer(Check);
    SPI.transfer(Output);
    digitalWrite(SHR_LATCH, HIGH);
    digitalWrite(SHR_LATCH, LOW);
    // delayMicroseconds(500);
    if(digitalRead(2)==HIGH) bitWrite(Output, j, 1);
    else bitWrite(Output, j, 0);

    Check = Check<<1;
  }

  SPI.transfer(255);
  SPI.transfer(Output);
  digitalWrite(SHR_LATCH, HIGH);
  digitalWrite(SHR_LATCH, LOW);
  Serial.println(Output);
}


void button_init()
{
  DDRD |= (1 << SHR_LATCH);
  DDRD |= (1 << SHR_CLOCK);
  DDRD |= (1 << SHR_DATA);
  pinMode(2, INPUT);//Input from buttons

  // pinMode(13, OUTPUT);//clock
  // pinMode(11, OUTPUT);//data
  // pinMode(10, OUTPUT);//latch

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.begin();
  SPI.transfer(255);
  SPI.transfer(0);
  digitalWrite(10, HIGH);
  digitalWrite(10, LOW);
  Serial.begin(115200);
  attachInterrupt(0, pin_read, RISING); 
}

void button_update()
{

}

// DISEÑAR LA RUTINA DEL SHIFTREGISTER SIN SPI
// NO NECESITA TANTA VELOCIDAD
// PROBAR SIN INTERRUPTOR AL PIN DE LECTURA