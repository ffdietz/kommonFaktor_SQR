#ifndef shiftRegister_h
#define shiftRegister_h

class ShiftReg
{
  public:
  ShiftReg();
  void begin();

  void read();
  void out(int value);
  byte output;
  byte check = 1;
  int j;

};

#endif
