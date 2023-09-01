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

  // void selector(uint8_t channel){
  //   digitalWrite(MUX_A, channel & 0x01);
  //   digitalWrite(MUX_B, (channel >> 1) & 0x01);
  //   digitalWrite(MUX_C, (channel >> 2) & 0x01);
  //   }

    void selector(byte step){
      int channel = step;
      switch (channel) {
        case 0: digitalWrite(MUX_A, 0); digitalWrite(MUX_B, 0); digitalWrite(MUX_C, 0); break;
        case 1: digitalWrite(MUX_A, 1); digitalWrite(MUX_B, 0); digitalWrite(MUX_C, 0); break;
        case 2: digitalWrite(MUX_A, 0); digitalWrite(MUX_B, 1); digitalWrite(MUX_C, 0); break;
        case 3: digitalWrite(MUX_A, 1); digitalWrite(MUX_B, 1); digitalWrite(MUX_C, 0); break;
        case 4: digitalWrite(MUX_A, 0); digitalWrite(MUX_B, 0); digitalWrite(MUX_C, 1); break;
        case 5: digitalWrite(MUX_A, 1); digitalWrite(MUX_B, 0); digitalWrite(MUX_C, 1); break;
        case 6: digitalWrite(MUX_A, 0); digitalWrite(MUX_B, 1); digitalWrite(MUX_C, 1); break;
        case 7: digitalWrite(MUX_A, 1); digitalWrite(MUX_B, 1); digitalWrite(MUX_C, 1); break;
      }
}

  void mute(){
    digitalWrite(MUX_INH, HIGH);
  }

  void unmute(){
    digitalWrite(MUX_INH, LOW);
  }

};

#endif