#ifndef CONFIGURATION
#define CONFIGURATION

#include "constant.h"
#include "variable.h"
#include "Arduino.h"

class Configuration 
{
  public : 
    Configuration();

    void configuration_feature(void);

    void configuration_on_default(void);

    int configuration_shift_index_potentiometre(int index_max);
};

extern Configuration configu;

#endif //CONFIGURATION