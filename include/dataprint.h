#ifndef controller_h
#define controller_h


#include "coordinates.h"

class DataPrint {
  public:
    DataPrint(char lab, Coordinates labpost, char val, Coordinates valpos);
    static const char * label;
    static const char * value;
    static const Coordinates labelPosition;
    static const Coordinates valuePosition;

  private:

};
#endif