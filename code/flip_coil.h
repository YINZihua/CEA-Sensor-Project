#ifndef FLIP_COIL
#define FLIP_COIL

#include "constant.h"
#include "variable.h"
#include "Arduino.h"

class Pulse
{
  public :
    Pulse();

    void init_timer(void);

    void init_timer_17kHz(void);
};

extern Pulse pulse;

#endif //FLIP_COIL