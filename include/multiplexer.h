#ifndef MUX_H
#define MUX_H

class Multiplexer {
  public:
    Multiplexer(){}

    void begin(){
      pinMode(MUX_A, OUTPUT);
      pinMode(MUX_B, OUTPUT);
      pinMode(MUX_C, OUTPUT);
    }

  void selector(uint8_t channel){
      digitalWrite(MUX_A, channel     & 1);
      digitalWrite(MUX_B, channel / 2 & 1);
      digitalWrite(MUX_C, channel / 4 & 1);
    }

};

#endif