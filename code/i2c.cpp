#include "i2c.h"
#include <Wire.h>
#include "Arduino.h"
#include "variable.h"
#include "constant.h"


/***********************************************************************************************
 * 
 * 
 *                      module du contrôle du Bus I2C
 * 
 *          auteur : YIN Zihua
 *          nom du projet : Réalisation de capteur du champ magnétique
 *          NO. de version du programme: 
 *          date du release : 
 * 
 *          description de fonctionnement :
 * 
 * 
 * ********************************************************************************************/
    //constructeur de la classe I2C_BUs
    I2C_Bus::I2C_Bus()
    {
        
    }

/******************************************************************************
 * 
 * 
 * code pour bus i2c
 * 
 * 
 * ***************************************************************************/

    //initialisation de la connexion i2c, il faut encore essayer une version sans l'adresse ADS1015_ADDR_PIN_GND,
    // ou une version globale au niveau de peripheriques ???
        void I2C_Bus::i2c_init(void)
        {
            int channel_index;
            for(channel_index = 0; channel_index < acquisition_nb_channel; channel_index++){
                    Wire.begin(acquisition_channel_i2c_addr[channel_index]);
            }
        }

    //cette fonction ecrit une trame de data d'un longeur fini
        void I2C_Bus::i2c_write_string(int dev_addr, char* data_addr, int length_data)
        {
            int index;

            Wire.beginTransmission(dev_addr);
            for(index = 0; index < length_data; index++){
                Wire.write(*data_addr);
                data_addr++;
            }
            Wire.endTransmission();
        }

    //cette fonction lit les donnees transmises sur un SDA de i2c d'un longeur fini
        int I2C_Bus::i2c_read_trame_string(int dev_addr, int read_request, int length_data)
        {
            //0 : declaration d'une variable permettant une lecture de multi-octet
                int index = 0;

            //1 : lancer la transmission
                Wire.beginTransmission(dev_addr);
                Wire.write(read_request);
                Wire.endTransmission();

            //2 : recuperation de donnees
                Wire.requestFrom(dev_addr, length_data);
                while(Wire.available()){
                    i2c_buffer[index] = Wire.read();
                    index++;
                }

            //3 : fin de fonction, retourner la longueur de tableau occupe
                return index;
        }
    
/******************************************************************************
 * 
 * 
 * code pour systeme de la configuration
 * 
 * 
 * ***************************************************************************/

        void I2C_Bus::i2c_channel_config(int channel)
        {
            //0 : declaration et initialisation pour determiner les configurations des channels I2C
                //0.1 : l'indice des onglets        1 >> ADS1015
                    //                              2 >> ADS1115
                    int sous_config_index_acqui_i2c = 0 ;
                //0.2 : le maximum de l'indice des configurations
                    int config_index_max = 1;

                //0.4 : validation de configurations
                    int valid_config = 0;
                
            //1 : modifications sur les configurations
                while(bp.bouton_if_pushed(BP_ENTER));
                while(valid_config == 0){
                    //1.1 : detection de bouton
                    
                    //1.2 : affichage d'onglet
                        lcd.clear();
                        switch(sous_config_index_acqui_i2c){
                            case 0 : {
                                affi.affi_carac("ADS1015",0,0);
                                break;
                            }
                            case 1 : {
                                affi.affi_carac("ADS1115",0,0);
                                break;
                            }
                            default : break;
                        }

                    //1.3 : operations sur les onglets
                        if(bp.bouton_if_pushed(BP_ENTER)){
                            switch(sous_config_index_acqui_i2c){
                                case 0 :{
                                    i2c.i2c_channel_config_ads1015(channel);
                                    valid_config = 1;
                                    break;
                                }
                                case 1 : {
                                    //???
                                    valid_config = 1;
                                    break;
                                }
                                default : break;
                            }
                        }
                        else sous_config_index_acqui_i2c = configu.configuration_shift_index_potentiometre(config_index_max);
                    
                        delay(50);
                }
                while(bp.bouton_if_pushed(BP_ENTER));            
        }

    //cette fonction permet de configuration un channel avec une connexion de source du type i2c,
    //apres toutes les choix de configuration, les changements seront mis à jour directement
        void I2C_Bus::i2c_channel_config_ads1015(int channel)
        {
            //0 : declaration et initialisation des variables pour determiner le type de connexion
                //0.1 : l'indice de la configuration visee
                    //sous_config_index_acqui_i2c_ads1015 = 0 >> valid
                    //                                      1 >> FSR
                    //                                      2 >> ADDR
                    //                                      3 >> SOURCE TYPE
                    //                                      4 >> data rate
                    int sous_config_index_acqui_i2c_ads1015 = 1;

                //0.2 : le maximum de l'indice des configurations du lcd
                    int config_index_max = 4;



                //0.4 : validation des configurations
                    int valid_config = 0;
                
                //0.5 : variables du registre de configuration
                    int ads1015_cfig_reg_fsr = 0, ads1015_dev_addr = 0, ads1015_cfig_reg_adc_source = 0, ads1015_cfig_reg_data_rate = 0;
                    int critere_de_config = 0;

            //1 : gestion d'onglets et des paramètres du registre de configuration
                while(bp.bouton_if_pushed(BP_ENTER));
                while(valid_config == 0){
                    //1.1 : detection de bouton

                    //1.2 : operations sur les onglets
                        //1.2.1 : entrance aux options d'onglets
                            if(bp.bouton_if_pushed(BP_ENTER)){
                                switch(sous_config_index_acqui_i2c_ads1015){
                                    //1.2.1.1 : accès pour finaliser cette configuration de i2c et en sortir
                                        case 0 :{
                                            //1.2.1.1.1 : en assurant que toutes les configurations sont prises
                                                if(critere_de_config == 0x0F)valid_config = 1;
                                            //1.2.1.1.1 : si toutes les config ne sont pas finies, on retourne au menu de config
                                                else {
                                                    lcd.clear();
                                                    affi.affi_carac("Not all config",0,0);
                                                    affi.affi_carac("are done!",0,0);
                                                    delay(1000);
                                                }
                                            break;
                                        }
                                    //1.2.1.2 : config pour déterminer la FSR de channel
                                        case 1 :{
                                            ads1015_cfig_reg_fsr = i2c.i2c_channel_config_ads1015_fsr();
                                            critere_de_config |= 0x01;
                                            break;
                                        }
                                    //1.2.1.3 : config pour déterminer l'adresse de I2C du channel
                                        case 2 :{
                                            ads1015_dev_addr = i2c.i2c_channel_config_ads1015_addr();
                                            critere_de_config |= 0x02;
                                            break;
                                        }
                                    //1.2.1.4 : config pour déterminer l'entrée du ADC associé
                                        case 3 :{
                                            ads1015_cfig_reg_adc_source = i2c.i2c_channel_config_ads1015_adc_src();
                                            critere_de_config |= 0x04;
                                            break;
                                        }
                                    //1.2.1.5 : config pour déterminer la fréquence d'échantillonnage du capteur associé au channel
                                        case 4 :{
                                            ads1015_cfig_reg_data_rate = i2c.i2c_channel_config_ads1015_data_rate();
                                            critere_de_config |= 0x08;
                                            break;
                                        }
                                        default : break;
                                }
                            }
                        //1.2.2 : changer l'onglet
                            else sous_config_index_acqui_i2c_ads1015 = configu.configuration_shift_index_potentiometre(config_index_max);
                            

                    //1.3 : affichage d'onglets
                        lcd.clear();
                        switch(sous_config_index_acqui_i2c_ads1015){
                            case 0 :{
                                affi.affi_carac("Valid",0,0);
                                affi.affi_carac("ADS1015",0,1);
                                break;
                            }
                            case 1 :{
                                affi.affi_carac("FSR",0,0);
                                break;
                            }
                            case 2 :{
                                affi.affi_carac("ADDR",0,0);
                                break;
                            }
                            case 3 :{
                                affi.affi_carac("ADC Source",0,0);
                                break;
                            }
                            case 4 :{
                                affi.affi_carac("Data Rate",0,0);
                                break;
                            }
                            default : break;
                        }
                        delay(50);
                }    
            
            //2 : initialisation de peripherique i2c de channel
                acquisition_channel_i2c_adc_cfig_reg[channel] = i2c.i2c_ads1015_cfig_reg_value( ADS1015_CFIG_REG_OS_SINGLE_CONV_START,
                                                                                                ads1015_cfig_reg_adc_source,
                                                                                                ads1015_cfig_reg_fsr,
                                                                                                ADS1015_CFIG_REG_MODE_CONV_SINGLE,
                                                                                                ads1015_cfig_reg_data_rate,
                                                                                                ADS1015_CFIG_REG_COMP_MODE_TRAD,
                                                                                                ADS1015_CFIG_REG_COMP_POL_LOW,
                                                                                                ADS1015_CFIG_REG_COMP_LAT_NO_LATCH,
                                                                                                ADS1015_CFIG_REG_COMP_QUE_DISABLE_COMP);
                acquisition_channel_i2c_addr[channel] = ads1015_dev_addr;
                i2c.i2c_channel_config_dev(channel, I2C_DEV_ADS1015);

                

                while(bp.bouton_if_pushed(BP_ENTER));
        }

        int I2C_Bus::i2c_channel_config_ads1015_fsr(void)
        {
            //0 : declaration et initialisation des variables pour determiner la FSR de ads1015 du channel
                //0.1 : l'indice de la configuraion
                    //sous_config_index_acqui_i2c_ads1015_fsr = 0 >> +/- 256 mV
                    //                                          1 >> +/- 512 mV
                    //                                          2 >> +/- 1024 mV
                    //                                          3 >> +/- 2048 mV
                    //                                          4 >> +/- 4096 mV
                    //                                          5 >> +/- 6144 mV
                    int sous_config_index_acqui_i2c_ads1015_fsr = 0;
                //0.2 : le maxium de l'indice des configurations 
                    int config_index_max = 5;

                //0.4 : validation de configuraions
                    int valid_config = 0;

                    int return_fsr = 0;
                
            //1 : modifications
                while(bp.bouton_if_pushed(BP_ENTER));
                while(valid_config == 0){
                    //1.1 : detection de bouton

                    //1.2 : operation sur les onglets
                        if(bp.bouton_if_pushed(BP_ENTER)){
                            switch(sous_config_index_acqui_i2c_ads1015_fsr){
                                case 0 :{
                                    return_fsr = ADS1015_CFIG_REG_PGA_FSR_0256;
                                    break;
                                }
                                case 1 :{
                                    return_fsr = ADS1015_CFIG_REG_PGA_FSR_0512;
                                    break;
                                }
                                case 2 :{
                                    return_fsr = ADS1015_CFIG_REG_PGA_FSR_1024;
                                    break;
                                }
                                case 3 :{
                                    return_fsr = ADS1015_CFIG_REG_PGA_FSR_2048;
                                    break;
                                }
                                case 4 :{
                                    return_fsr = ADS1015_CFIG_REG_PGA_FSR_4096;
                                    break;
                                }
                                case 5 :{
                                    return_fsr = ADS1015_CFIG_REG_PGA_FSR_6144;
                                    break;
                                }
                                default : break;
                            }
                            valid_config = 1;
                        }
                        else sous_config_index_acqui_i2c_ads1015_fsr = configu.configuration_shift_index_potentiometre(config_index_max);
                        
                    
                    //1.3 : affichage des onglets
                        lcd.clear();
                        switch(sous_config_index_acqui_i2c_ads1015_fsr){
                            case 0 : affi.affi_carac("FSR = 0256 mV",0,0); break;
                            case 1 : affi.affi_carac("FSR = 0512 mV",0,0); break;
                            case 2 : affi.affi_carac("FSR = 1024 mV",0,0); break;
                            case 3 : affi.affi_carac("FSR = 2048 mV",0,0); break;
                            case 4 : affi.affi_carac("FSR = 4096 mV",0,0); break;
                            case 5 : affi.affi_carac("FSR = 6144 mV",0,0); break;
                            default : break;
                        }
                        delay(50);
                }

                while(bp.bouton_if_pushed(BP_ENTER));
                return return_fsr;
        }

        //cette fonction retourne la valeur FSR en mV du channel ADC I2C du périphérique ADS1015 
        unsigned int I2C_Bus::i2c_channel_ads1015_fsr(int channel)
        {
            int cfig_reg = acquisition_channel_i2c_adc_cfig_reg[channel];
            cfig_reg = ((cfig_reg >> ADS1015_CFIG_REG_PGA_OFFSET) && B00000111);
            switch(cfig_reg){
                case B000: return 6144; break;
                case B001: return 4096; break;
                case B010: return 2048; break;
                case B011: return 1024; break;
                case B100: return 0512; break;
                case B101: 
                case B110: 
                case B111: return 0256; break;
                default  : return 2048; break;
            }
        }

        int I2C_Bus::i2c_channel_config_ads1015_addr(void)
        {
            //0 : declaration et initialisation des variables pour determiner la FSR de ads1015 du channel
                //0.1 : l'indice de la configuraion
                    //sous_config_index_acqui_i2c_ads1015_fsr = 0 >> PIN GND
                    //                                          1 >> PIN VDD
                    //                                          2 >> PIN SDA
                    //                                          3 >> PIN SCL
                    int sous_config_index_acqui_i2c_ads1015_addr = 0;
                //0.2 : le maxium de l'indice des configurations 
                    int config_index_max = 3;
                //0.3 : l'operation sur les onglets
                    int operation = OP_NO_OPERATION;
                //0.4 : validation de configuraions
                    int valid_config = 0;
                
                    int return_addr = 0;
            //1 : modifications
                while(bp.bouton_if_pushed(BP_ENTER));
                while(valid_config == 0){
                    //1.1 : detection de bouton

                    //1.2 : operation sur les onglets
                        if(bp.bouton_if_pushed(BP_ENTER)){
                            switch(sous_config_index_acqui_i2c_ads1015_addr){
                                case 0 :{
                                    return_addr = ADS1015_ADDR_PIN_GND;
                                    break;
                                }
                                case 1 :{
                                    return_addr = ADS1015_ADDR_PIN_VDD;
                                    break;
                                }
                                case 2 :{
                                    return_addr = ADS1015_ADDR_PIN_SDA;
                                    break;
                                }
                                case 3 :{
                                    return_addr = ADS1015_ADDR_PIN_SCL;
                                    break;
                                }
                                default : break;
                            }
                            valid_config = 1;
                        }
                        else if(operation != OP_NO_OPERATION){
                            sous_config_index_acqui_i2c_ads1015_addr = configu.configuration_shift_index_potentiometre(config_index_max);
                        }
                    
                    //1.3 : affichage des onglets
                        lcd.clear();
                        switch(sous_config_index_acqui_i2c_ads1015_addr){
                            case 0 : affi.affi_carac("ADDR PIN GND",0,0); break;
                            case 1 : affi.affi_carac("ADDR PIN VDD",0,0); break;
                            case 2 : affi.affi_carac("ADDR PIN SDA",0,0); break;
                            case 3 : affi.affi_carac("ADDR PIN SCL",0,0); break;
                            default : break;
                        }
                        delay(50);
                }
                while(bp.bouton_if_pushed(BP_ENTER));
                return return_addr;
        }
        
        int I2C_Bus::i2c_channel_config_ads1015_adc_src(void)
        {
            //0 : declaration et initialisation des variables pour determiner la FSR de ads1015 du channel
                //0.1 : l'indice de la configuraion
                    //sous_config_index_acqui_i2c_ads1015_adc_src = 0 >> AIN0 - AIN1
                    //                                              1 >> AIN0 - AIN3
                    //                                              2 >> AIN1 - AIN3
                    //                                              3 >> AIN2 - AIN3
                    //                                              4 >> AIN0
                    //                                              5 >> AIN1
                    //                                              6 >> AIN2
                    //                                              7 >> AIN3
                    int sous_config_index_acqui_i2c_ads1015_adc_src = 0;
                //0.2 : le maxium de l'indice des configurations 
                    int config_index_max = 7;

                //0.4 : validation de configuraions
                    int valid_config = 0;
                
                    int return_adc;

            //1 : modifications
                while(bp.bouton_if_pushed(BP_ENTER));
                while(valid_config == 0){
                    //1.1 : detection de bouton

                    //1.2 : operation sur les onglets
                        if(bp.bouton_if_pushed(BP_ENTER)){
                            switch(sous_config_index_acqui_i2c_ads1015_adc_src){
                                case 0 :{
                                    return_adc = ADS1015_CFIG_REG_MUX_AIN0_AIN1;
                                    break;
                                }
                                case 1 :{
                                    return_adc = ADS1015_CFIG_REG_MUX_AIN0_AIN3;
                                    break;
                                }
                                case 2 :{
                                    return_adc = ADS1015_CFIG_REG_MUX_AIN1_AIN3;
                                    break;
                                }
                                case 3 :{
                                    return_adc = ADS1015_CFIG_REG_MUX_AIN2_AIN3;
                                    break;
                                }
                                case 4 :{
                                    return_adc = ADS1015_CFIG_REG_MUX_AIN0_GND;
                                    break;
                                }
                                case 5 :{
                                    return_adc = ADS1015_CFIG_REG_MUX_AIN1_GND;
                                    break;
                                }
                                case 6 :{
                                    return_adc = ADS1015_CFIG_REG_MUX_AIN2_GND;
                                    break;
                                }
                                case 7 :{
                                    return_adc = ADS1015_CFIG_REG_MUX_AIN3_GND;
                                    break;
                                }
                                default : break;
                            }
                            valid_config = 1;
                        }
                        else sous_config_index_acqui_i2c_ads1015_adc_src = configu.configuration_shift_index_potentiometre(config_index_max);
                        
                    
                    //1.3 : affichage des onglets
                        lcd.clear();
                        affi.affi_carac("ADC Source",0,0);
                        switch(sous_config_index_acqui_i2c_ads1015_adc_src){
                            case 0 : affi.affi_carac("AIN0-AIN1",0,1); break;
                            case 1 : affi.affi_carac("AIN0-AIN3",0,1); break;
                            case 2 : affi.affi_carac("AIN1-AIN3",0,1); break;
                            case 3 : affi.affi_carac("AIN2-AIN3",0,1); break;
                            case 4 : affi.affi_carac("AIN0",0,1); break;
                            case 5 : affi.affi_carac("AIN1",0,1); break;
                            case 6 : affi.affi_carac("AIN2",0,1); break;
                            case 7 : affi.affi_carac("AIN3",0,1); break;
                            default : break;
                        }
                        delay(50);
                }
                while(bp.bouton_if_pushed(BP_ENTER));
                return return_adc;
        }

        int I2C_Bus::i2c_channel_config_ads1015_data_rate(void)
        {
            //0 : declaration et initialisation des variables pour determiner la data rate de ads1015 du channel
                //0.1 : l'indice de la configuraion
                    //sous_config_index_acqui_i2c_ads1015_fsr = 0 >> 0128 
                    //                                          1 >> 0250
                    //                                          2 >> 0490
                    //                                          3 >> 0920
                    //                                          4 >> 1600
                    //                                          5 >> 2400
                    //                                          6 >> 3300
                    int sous_config_index_acqui_i2c_ads1015_dr = 0;
                //0.2 : le maxium de l'indice des configurations 
                    int config_index_max = 6;


                //0.4 : validation de configuraions
                    int valid_config = 0;

                    int return_dr = 0;
                
            //1 : modifications
                while(bp.bouton_if_pushed(BP_ENTER));
                while(valid_config == 0){
                    //1.1 : detection de bouton

                    //1.2 : operation sur les onglets
                        if(bp.bouton_if_pushed(BP_ENTER)){
                            switch(sous_config_index_acqui_i2c_ads1015_dr){
                                case 0 :{
                                    return_dr = ADS1015_CFIG_REG_DR_0128;
                                    break;
                                }
                                case 1 :{
                                    return_dr = ADS1015_CFIG_REG_DR_0250;
                                    break;
                                }
                                case 2 :{
                                    return_dr = ADS1015_CFIG_REG_DR_0490;
                                    break;
                                }
                                case 3 :{
                                    return_dr = ADS1015_CFIG_REG_DR_0920;
                                    break;
                                }
                                case 4 :{
                                    return_dr = ADS1015_CFIG_REG_DR_1600;
                                    break;
                                }
                                case 5 :{
                                    return_dr = ADS1015_CFIG_REG_DR_2400;
                                    break;
                                }
                                case 6 :{
                                    return_dr = ADS1015_CFIG_REG_DR_3300;
                                    break;
                                }
                                default : break;
                            }
                            valid_config = 1;
                        }
                        else sous_config_index_acqui_i2c_ads1015_dr = configu.configuration_shift_index_potentiometre(config_index_max);
                        
                    
                    //1.3 : affichage des onglets
                        lcd.clear();
                        switch(sous_config_index_acqui_i2c_ads1015_dr){
                            case 0 : affi.affi_carac("Data Rate 0128",0,0); break;
                            case 1 : affi.affi_carac("Data Rate 0240",0,0); break;
                            case 2 : affi.affi_carac("Data Rate 0490",0,0); break;
                            case 3 : affi.affi_carac("Data Rate 0920",0,0); break;
                            case 4 : affi.affi_carac("Data Rate 1600",0,0); break;
                            case 5 : affi.affi_carac("Data Rate 2400",0,0); break;
                            case 6 : affi.affi_carac("Data Rate 3300",0,0); break;
                            default : break;
                        }
                        delay(50);
                }
                while(bp.bouton_if_pushed(BP_ENTER));
                return return_dr;
        }

        void I2C_Bus::i2c_channel_config_dev(char channel, char dev_id)
        {
            switch(dev_id){
                case I2C_DEV_ADS1115 : {// bit du channel = 1
                    acquisition_channel_i2c_dev |= (1 << channel);
                    break;
                }
                default : {//I2C_DEV_ADS1015  bit du channel = 0
                    acquisition_channel_i2c_dev &= (~(1 << channel));
                    break;
                }
            }
        }

        unsigned char I2C_Bus::i2c_channel_dev_id(char channel)
        {
            return ((acquisition_channel_i2c_dev & (1 << channel)) ? (I2C_DEV_ADS1115) : (I2C_DEV_ADS1015));
        }
/******************************************************************************
 * 
 * 
 * code pour systeme de l'acquisition
 * 
 * 1. conversion de valeur reçue en [mV] mesuré
 * 2. conversion de valeur reçue en [µV] mesuré
 * 3. fonction de lecture en retournant la tension mesurée dont l'unité est en fonction d'argument
 * 
 * ***************************************************************************/ 


        //this function returns the value of the mesured voltage in [100uV]
            signed long I2C_Bus::i2c_acquisition(int channel, int unite)
            {
                //0 : réception de la trame I2C
                    int trame_i2c = i2c.i2c_read_trame(channel);

                //1 : en déduir la valeur de la tension [100uV] sur ce capteur
                    signed long val_100uV = i2c.i2c_valeur_to_100uV(trame_i2c, channel);

                //2 : fin de fonction et on retourne la tension mesurée en [mV]
                    return val_100uV;
            }
            
        int I2C_Bus::i2c_read_trame(int channel)
        {
            // 0 : déclaration et intialisation de variable
                int trame_i2c = 0;
            // 1 : fonctions de lecture dédiée aux différents périphériques d'ADC
                switch(i2c.i2c_channel_dev_id(channel))
                {
                    case I2C_DEV_ADS1015:{
                        trame_i2c = i2c_ads1015_read(channel);
                        break;
                    }
                    case I2C_DEV_ADS1115:{
                        trame_i2c = i2c_ads1115_read(channel);
                        break;
                    }
                    default: break;
                }
            
            // 2 : retourner la trame I2C d'ADC
                return trame_i2c;
        }



        signed long I2C_Bus::i2c_valeur_to_100uV(int trame_i2c, int channel)
        {
            signed long val_uV = 0;
            switch(i2c.i2c_channel_dev_id(channel)){
                case I2C_DEV_ADS1015:{
                    val_uV = i2c.i2c_ads1015_valeur_to_100uV(((trame_i2c >> 8) & 0xFF), (trame_i2c & 0xFF), channel);
                    break;
                }
                case I2C_DEV_ADS1115:{
                    val_uV = 0;// faut compléter ???
                    break;
                }
                return val_uV;
            }
        }

/******************************************************************************
 * 
 * 
 * code pour ADCs ads1015
 * 
 * 
 * ***************************************************************************/

    //cette fonction determine la valeur de registre pour un materiel ads1015 en fonction des parametres exiges
        int I2C_Bus::i2c_ads1015_cfig_reg_value(int OS, int MUX, int PGA, int MODEE,
                                                int DR, int COMP_MODE, int COMP_POL,
                                                int COMP_LAT, int COMP_QUE)
        {
            int cfig_reg = 0x00;
            cfig_reg += (OS << ADS1015_CFIG_REG_OS_OFFSET);
            cfig_reg += (MUX << ADS1015_CFIG_REG_MUX_OFFSET);
            cfig_reg += (PGA << ADS1015_CFIG_REG_PGA_OFFSET);
            cfig_reg += (MODEE << ADS1015_CFIG_REG_MODE_OFFSET); //si on nomme 'MODE', il ne complie pas, 'MODE'peut etre un keyword de Arduino
            cfig_reg += (DR << ADS1015_CFIG_REG_DR_OFFSET);
            cfig_reg += (COMP_MODE << ADS1015_CFIG_REG_COMP_MODE_OFFSET);
            cfig_reg += (COMP_POL << ADS1015_CFIG_REG_COMP_POL_OFFSET);
            cfig_reg += (COMP_LAT << ADS1015_CFIG_REG_COMP_LAT_OFFSET);
            cfig_reg += (COMP_QUE << ADS1015_CFIG_REG_COMP_QUE_OFFSET);
            return cfig_reg;      
        }

    //cette fonction met en stockage la valeur de registre d'un peripherique i2c d'apres une configuration de channel
        void I2C_Bus::i2c_ads1015_cfig_reg_setup(int OS, int MUX, int PGA, int MODEE,
                                                int DR, int COMP_MODE, int COMP_POL,
                                                int COMP_LAT, int COMP_QUE, int channel)
        {
            //0 : calcul de la valeur à stocker dans le registre
                int cfig_reg = i2c.i2c_ads1015_cfig_reg_value(OS, MUX, PGA, MODEE, DR, COMP_MODE, COMP_POL, COMP_LAT, COMP_QUE);
            //1 : enregsitrer cette valeur dans un registre local de la carte Arduino, permettant à savoir le statut de chaque channel i2c sans requête au matériel
                acquisition_channel_i2c_adc_cfig_reg[channel] = cfig_reg;            
        }

    //l'envoi de la valeur de registre de configuraiton d'un peripherique ads1015
    //cela permet également de lancer une nouvelle conversion en contexte "single-shot conversion" of ads1015
        void I2C_Bus::i2c_ads1015_cfig_reg_send(int ads1015_addr, int ads1015_cfig_reg)
        {
            //0 :  declaration et initialisation les trois octets transmises sur i2c :  
            //              adresse du registre de configuration sur ads1015
            //              octet en haut du registre
            //              octet en bas du registre
                char data[3];
                data[0] = ADS1015_ADDR_PTR_CFIG_REG;
                data[1] = (ads1015_cfig_reg >> 8);
                data[2] = (ads1015_cfig_reg);
            //1 : lancement de cette transmission
                i2c_write_string(ads1015_addr, data, 3);
        }


    //cette fonction lance une transmission de donnee sur un channel i2c de peripherique ads1015
    //les datas [mV] sont stockees dans le buffer de connexion i2c, on va les retirer et puis retourner 
    //à location de l'appel de cette fonction 
        int I2C_Bus::i2c_ads1015_read(int channel)
        {
            //0 : lancer une 'single-shot' conversion
                i2c.i2c_ads1015_cfig_reg_send(acquisition_channel_i2c_addr[channel], acquisition_channel_i2c_adc_cfig_reg[channel]);
            //1 : lecture de donnees recues apres la requete et stockage dans le buffer
                i2c.i2c_read_trame_string(acquisition_channel_i2c_addr[channel], ADS1015_ADDR_PTR_CONV_REG, ADS1015_READ_LENGTH);
            //2 : fin de fonction ainsi qu'un retour de cette valeur mesuré en code binair
                return ((((int)i2c_buffer[0]) << 8) + ((int)i2c_buffer[1]));
        }


    // fonction de conversion 'trame_i2c' -> 'tension_100uV'
            signed long I2C_Bus::i2c_ads1015_valeur_to_100uV(unsigned char hi, unsigned char lo, int channel)
            {
                // 0 : récupération de la valeur FSR du ADC sur ce channel
                    unsigned char fsr = i2c.i2c_channel_ads1015_fsr(channel);
                
                // 1 : valeur acquise de channel en 12 bit
                    int val_conv = ((((int)hi) << 4) + (((int)lo) >> 4)); 
                
                // 2 : détermination du signe 
                    val_conv = ((val_conv < 2048)?(val_conv):(val_conv - 4096));
                
                // 3 : calcul de la résolution de mesure en [µV]
                    //fsr = 6144 >> résolution = 3000[µV] = 3mV
                    //fsr = 0256 >> résolution = 0125[µV] = 0,125mV
                    long resolution = (fsr * 1000) / 2048;
                
                // 4 : calcul de résultat final
                    //fsr = 6144 >> val_uV = 3000 * val_i2c
                    //fsr = 0256 >> val-uV = 0125 * val_i2c;
                    long val_uV = val_conv * resolution;
                
                // 5 : retournement de la valeur conversée en [100uV]
                    return (val_uV/100);
            }
            
/******************************************************************************
 * 
 * 
 * code pour ADC ads1115  ???
 * 
 * 
 * ***************************************************************************/



        int I2C_Bus::i2c_ads1115_read(int channel)
        {
            //??? compléter
            return 0;
        }
