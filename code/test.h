#ifndef TEST
#define TEST

#include "constant.h"
#include "variable.h"
#include "Arduino.h"

class Test
{
  public :
    Test();
    
    void signal_test(void);
};

extern Test test;

#endif //TEST