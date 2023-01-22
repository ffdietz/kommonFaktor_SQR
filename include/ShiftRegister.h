#ifndef shiftRegister_h
#define shiftRegister_h

class ShiftRegister
{
  public:
  ShiftRegister();
  void bitPrint(byte data);
  void bitLatch();
  void update();
  void setPositionOut();
  uint8_t getPosition();
  void bitShifter();



  private:
  byte position;
  byte position_out;
  byte shifter;
  void clearRegister();
}

#endif
