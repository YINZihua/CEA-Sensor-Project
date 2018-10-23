#ifndef SD_CARD
#define SD_CARD

#include "constant.h"
#include "variable.h"
#include "Arduino.h"
//#include <SPI.h>
//#include <SD.h>



class mySD
{
  public :

    mySD();

    void sd_config(void);

    void sd_usage_set_up(void);

    void sd_usage_cancel(void);

    void sd_write_val_time(int val_mes, int val_time);
};

extern mySD mysd;

#endif //SD
