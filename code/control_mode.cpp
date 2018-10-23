#include "control_mode.h"
#include "Arduino.h"

/********************************************************************************
 ********************                                    ************************
 ********************      module du control de mode     ************************
 ********************                                    ************************
 *******************************************************************************/
  Mode::Mode()
  {

  }

  void Mode::mode_set_up(int mode_index)
  {
    ctrl_mode |= mode_index;
  }

  void Mode::mode_cancel(int mode_index)
  {
    ctrl_mode &= ~((int)(mode_index));
  }

  //this function returns 'true' when the mode is applied
  bool Mode::mode_if_used(int mode_index)
  {
    return ((ctrl_mode | mode_index) == mode_index)?true:false;
  }