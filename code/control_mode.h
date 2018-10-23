#ifndef MODE
#define MODE

#include "variable.h"
#include "constant.h"
#include "Arduino.h"

class Mode
{
  public :
    Mode();
    
    void mode_set_up(int mode_index);

    void mode_cancel(int mode_index);

    bool mode_if_used(int mode_index);
};

extern Mode mode;

#endif //MODE