#ifndef MATHS
#define MATHS

#include "constant.h"
#include "variable.h"
#include "Arduino.h"

class Maths
{
  public :
    Maths();

    int incrementation_modulo(int number, int modulo);

    int decrementation_modulo(int number, int modulo);

    void regression_lineaire_3pts(long* x, long* y, long* pente, long* offset);
};

extern Maths maths;

#endif //MATHS