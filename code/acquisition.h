#ifndef ACQUISITION
#define ACQUISITION

#include "constant.h"
#include "variable.h"
#include "Arduino.h"


class Acquisition 
{
  public : 
    // Constructeur
      Acquisition();

    // functions for configurations

      void acquisition_config(void);
      
      void acquisition_config_nb_channel(void);
      
      void acquisition_config_ratio_echan(void);

      void acquisition_config_channel(void);

    // Apres cette fonction, les premiers channels de nombre 'chanel_nb' vont etre actives
    // et ils sont initialises en channels d'entree analogue
      void acquisition_config_channel_connexion_default(int channel_nb);

      void acquisition_config_channel_connexion_user_setting(void);

      void acquisition_config_channel_connexion_user_setting_single_channel(int channel);

      void acquisition_config_channel_user_setting_capteur_type(int channel);

      void acquisition_config_channel_user_setting_connexion_type(int channel);

      void acquisition_config_channel_statut_actual(void);

    // functions for data acquisition  
    
      
      int acquisition_lecture_i2c(int addr_channel);
      
      void acquisition_lecture_data(void);

    // functions for data acquisition test

  	    void acquisition_test_data(void);
};

extern Acquisition acqui;

#endif 
// ACQUISITION