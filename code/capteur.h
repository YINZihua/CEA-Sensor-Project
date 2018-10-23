#ifndef CAPTEUR_CHAMP_MAGNETIQUE
#define CAPTEUR_CHAMP_MAGNETIQUE

#include "constant.h"
#include "variable.h"
#include "Arduino.h"

class CAPTEUR{
    public : 
        //constructeur de la classe
            CAPTEUR();
        
        //initialisation en découvrant les coefficients de conversion de chaque voie
            //coef_uT_mV * mV = uT 
            void cap_coef_uT_V_setup(void);

            void cap_coef_uT_V_setup_single_channel(int channel);

        //application du capteur aff755b
            int cap_coef_uV_uT_setup_cap_aff755b(int channel);

        //application du capteur Stefan Mayer
            int cap_coef_uT_V_setup_cap_stefan_mayer(void);


        //conversion vers l'intensité de champ magnétique
            int cap_100uV_to_100nT(int channel, int val_100uV);

};

extern CAPTEUR cap;

#endif //CAPTEUR_CHAMP_MAGNETIQUE
