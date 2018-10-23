#ifndef AFFI_LIQUID_CRYSTAL
#define AFFI_LIQUID_CRYSTAL

#include "variable.h"
#include "constant.h"
#include "Arduino.h"

class LiquidCry
{
  public :
    LiquidCry();

    void affi_init_animation(void);

    void affi_init_title(int delay_affi_ms);

    void affi_config(void);

    void affi_config_on_default(void);

    void affi_mode_permanent_set_up(void);

    void affi_mode_affi_apres_bouton(void);

    void affi_acquisition(void);

    void affi_back_light_allume(void);

    void affi_back_light_eteint(void);

    void affi_carac(String carac, int cursor_col, int cursor_rang);

    bool affi_2_nb(int data, int cursor_col, int cursor_rang);

    bool affi_4_nb(int data, int cursor_col, int cursor_rang);

    bool affi_6_nb(long data, int cursor_col, int cursor_rang);

    void affi_magnetic_field_100nT(long data, int cursor_col, int cursor_rang);
    
    void affi_binary(long data, int data_length, int cursor_col, int cursor_rang);

    void affi_nTesla(long data, int cursor_col, int cursor_rang);
};

extern LiquidCry affi;

#endif //AFFI_LIQUID_CRYSTALs