#ifndef LIAISON_SERIE
#define LIAISON_SERIE

#include "constant.h"
#include "variable.h"
#include "Arduino.h"

class RS232 
{
  public : 
    RS232();

    void serial_config(void);

    void serial_config_on_default(void);

    void serial_config_baudrate(void);

    void serial_config_activation(void);

    void serial_send_set_up(void);

    void serial_send_cancel(void);

    long serial_data_ratio_setting(void);

    void serial_streaming(void);

    void serial_data_starting(void);

    void serial_data_ending(void);

    void serial_data_4_chiffres(int data);

    void serial_test_sinus_to_pc(void);
};

extern RS232 rs232;

#endif //LIAISON_SERIE