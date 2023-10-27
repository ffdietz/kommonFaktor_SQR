#ifndef MUX_H_
#define MUX_H_

class Multiplexer {
  public:
    Multiplexer(){}

    void begin(){
      pinMode(MUX_A, OUTPUT);
      pinMode(MUX_B, OUTPUT);
      pinMode(MUX_C, OUTPUT);

      pinMode(MUX_INH, OUTPUT);
    }

  void selector(uint8_t channel){
    digitalWrite(MUX_A, channel & 0x01);
    digitalWrite(MUX_B, (channel >> 1) & 0x01);
    digitalWrite(MUX_C, (channel >> 2) & 0x01);
    }

  void mute(){
    digitalWrite(MUX_INH, HIGH);
  }

  void unmute(){
    digitalWrite(MUX_INH, LOW);
  }

};

#endif