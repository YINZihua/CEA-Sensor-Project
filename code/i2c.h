#ifndef I2C_COMMUNICATION
#define I2C_COMMUNICATION

#include "constant.h"
#include "variable.h"
#include "Arduino.h"

class I2C_Bus
{
    public :
        //constructeur de la classe
            I2C_Bus();
        
        //code pour bus i2c
            void i2c_init(void);
            
            void i2c_write_string(int dev_addr, char* data_addr, int length_data);
            
            int i2c_read_string(int dev_addr, int read_request, int length_data);

        //code pour système de la configuration
            void i2c_channel_config(int channel);

            void i2c_channel_config_ads1015(int channel);

            int i2c_channel_config_ads1015_fsr(void);

            unsigned int i2c_channel_ads1015_fsr(int channel);

            int i2c_channel_config_ads1015_addr(void);

            int i2c_channel_config_ads1015_adc_src(void);
            
            int i2c_channel_config_ads1015_data_rate(void);

            void i2c_channel_config_dev(char channel, char dev_id);

            unsigned char i2c_channel_dev_id(char channel);

        //code pour système de l'acquisition
            
            //fonction d'appel d'écahntillonnage
                signed long i2c_acquisition(int channel, int unite);

            //fonction de lecture des trames i2c
                int i2c_read_trame(int channel);

            //fonctions de conversion 'trame_i2c' -> 'tension_100uV'
                signed long i2c_valeur_to_100uV(int trame_i2c, int channel);
            

        //code pour ADCs ads1015
            
            // recalculer la valeur à implémenter dans le registre
                int i2c_ads1015_cfig_reg_value(int OS, int MUX, int PGA, int MODEE,
                                                    int DR, int COMP_MODE, int COMP_POL,
                                                    int COMP_LAT, int COMP_QUE);

            // fonction de configuration pour le registre 'Config-Register' de module i2c
                void i2c_ads1015_cfig_reg_setup(int OS, int MUX, int PGA, int MODEE,
                                                    int DR, int COMP_MODE, int COMP_POL,
                                                    int COMP_LAT, int COMP_QUE, int channel);

            void i2c_ads1015_cfig_reg_send(int ads1015_addr, int ads1015_cfig_reg);

            int i2c_ads1015_read(int channel);
            
            //fonction de conversion 'trame_i2c' -> 'tension_100uV'
                signed long i2c_ads1015_valeur_to_100uV(unsigned char hi, unsigned char lo, int channel);
        
        //code pour ADCs ads1115

            int i2c_ads1115_read(int channel);
};

extern I2C_Bus i2c;

#endif //I2C_COMMUNICATION
