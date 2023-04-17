#ifndef shiftRegister_h
#define shiftRegister_h

class ShiftReg
{
  public:
  ShiftReg();
  void begin();

  void read();
  void out(int value);
  byte output = B00000000;
  byte check = 1 << 0;
};

#endif
