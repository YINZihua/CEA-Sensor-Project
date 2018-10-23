#include "variable.h"
#include "LiquidCrystal.h"
#include "Arduino.h"

/***********                                                     ***************
 *********** definition et initialisation des variables globales ***************
***********                                                     ***************/
//initialisation de la classe LCD


//initialisation de variables 
int val;

/*  declaration et initialisation de la variable pour le controle de mode
*  int 16 bits in Arduino UNO
*  **** **** **** ****
*  from left to right, 15 bit to 0 bit
*
*  les fonctions de chaque bit:
*  bit 0 >>  0, serial port ferme  (no serialing data to pc)
*            1, serial port ouvert (serialing data to pc)
*  bit 1 >>  0, LCD affichage apres un appui de bouton
*            1, LCD en mode permanent
*  bit 2 >>  0, SD carte non utilise
*            1, SD carte utilise
*  bit 3 >>  0, en mode normal
*            1, en mode de configuration 
*/
char ctrl_mode = 0; 

//declaration et initialisation du module SD
//------------------------------------------------des codes a ajouter
//unsigned char sd_activation = 0; // 0 for non_actived , 1 for actived


//declaration et initialisation des variables par rapport a l'acquisition
char acquisition_nb_channel = 1;
int ratio_acqui = 0;
// int channel_actu = 0;

//declaration et initialisation des variables comme registre de datas et de control
//des channels d'acquisition
//datas recues
    signed int acquisition_data_100nT[CHANNEL_MAX] ={0};

//type de channel : CHANNEL_ANALOG
//                  CHANNEL_I2C
//                  ... (extended interface for the next generation)
    // unsigned char acquisition_channel_type[CHANNEL_MAX]={0};
//pin des channels analogs connecte sur Arduino
    // int acquisition_channel_analog_pin[CHANNEL_MAX]={0};
//available pins for analog connections
//  CHANNEL_ANALOG_PORT_AVAILABLE
//  CHANNEL_ANALOG_PORT_NO_AVAILABLE
    // unsigned char acquisition_channel_analog_port_availablity[6] = {    CHANNEL_ANALOG_PORT_AVAILABLE,
    //                                                                     CHANNEL_ANALOG_PORT_AVAILABLE,
    //                                                                     CHANNEL_ANALOG_PORT_AVAILABLE,
    //                                                                     CHANNEL_ANALOG_PORT_AVAILABLE,
    //                                                                     CHANNEL_ANALOG_PORT_AVAILABLE,
    //                                                                     CHANNEL_ANALOG_PORT_AVAILABLE};
    // unsigned char channel_analog_port_availablity = 6;
//address des channels i2c 
    char acquisition_channel_i2c_addr[CHANNEL_MAX]={0};
//materiel ADC des channels i2c
    long acquisition_channel_i2c_dev = 0;
//definition of the connection type of the channel i2c source
    int acquisition_channel_i2c_adc_cfig_reg[CHANNEL_MAX] = {0};
//type de capteur appliqué sur ce channel
    unsigned char acquisition_channel_capteur[CHANNEL_MAX] = {CAP_UNKNOWN};

    signed long acquisition_channel_capteur_coef_10nT_100uV[CHANNEL_MAX] = {0};
    signed long acquisition_channel_capteur_offset_100uV[CHANNEL_MAX] = {0};

//declaration et initialisation des variables pour l'affichage sur LCD
    // LiquidCrystal lcd(6, 5, 3, 2, 1, 0);
    LiquidCrystal lcd(6,5,3,2,16,17); //pin17 >> A3, pin16 >> A2
    //lcd(rs, en, d4, d5, d6, d7);

    unsigned char affichage_acquisition_channel = 0;
    char affichage_statut = AFFICHAGE_ACQUISITION_ETEINT; 
    long affichage_time_counter = 0;//si counter > 5000 [ms], affichage_statut devient 0


//declaration et initialisation d'un buffer pour la recuperation des donnees I2C
    char i2c_buffer[I2C_BUFFER_LENGTH] = {0};

//variable globale pour la valeur reçue par le potentiomètre
    int val_poten_actu = 0;
    int val_poten_last = 0;

    
