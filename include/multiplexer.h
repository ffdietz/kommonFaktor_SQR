#ifndef MUX_H
#define MUX_H

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
      digitalWrite(MUX_A, channel     & 1);
      digitalWrite(MUX_B, channel / 2 & 1);
      digitalWrite(MUX_C, channel / 4 & 1);
    }

  void mute(){
    digitalWrite(MUX_INH, HIGH);
  }

  void unmute(){
    digitalWrite(MUX_INH, LOW);
  }

};

#endif