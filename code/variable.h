#ifndef VAR
#define VAR

#include "constant.h"
#include "LiquidCrystal.h"
#include "Arduino.h"

#include "acquisition.h"
#include "bp.h"
#include "configuration.h"
#include "control_mode.h"
#include "flip_coil.h"
#include "affichage.h"
#include "liaison_serie.h"
#include "maths.h"
#include "sd_card.h"
#include "test.h"
#include "i2c.h"
#include "capteur.h"
#include "system_cap_cea.h"

/***********                                                     ***************
 *********** definition et initialisation des variables globales ***************
 ***********                                                     ***************/

    //1 : contrôle de modes du système, 4 modes à définir
        //mode1 : envoi de données vers PC par la liaison série
            //ouverture/fermeture 
            //MACRO : 'MODE_SNED_BY_SERIAL'
        //mode2 : affichage de données sur LCD
            //en mode permanente/5 sec après un appui de bouton
            //MACRO : 'MODE_AFFI_LCD_PERM'
        //mode3 : utilisation de la carte SD
            //utilisé/non
            //MACRO : MODE_SD_STOCKAGE
        //mode4 : configuration de système
            //en cours/non
            //MACRO : MODE_CONFIGURATION
        extern char ctrl_mode ; 

    //2 : le nombre de channels activés
        extern char acquisition_nb_channel ; //nombre de channels activés
    
    //3 : la vitesse d'acquisition configurable
        //varie entre 500Hz (500 SPS) et 10mHz (1 Sample per 100 sec) //not done yet
        extern int ratio_acquisition ;

    //4 : enregistrement des intensités mesurées par chaque channel activé
        extern signed int acquisition_data_100nT[CHANNEL_MAX];

    //8 : adresse du périphérique I2C connecté sur un channel
        //MACRO des adresses en fonction du périphérique:
        //  ADS1015 :
        //      ADS1015_ADDR_PIN_GND
        //      ADS1015_ADDR_PIN_VDD
        //      ADS1015_ADDR_PIN_SDA
        //      ADS1015_ADDR_PIN_SCL
        extern char acquisition_channel_i2c_addr[CHANNEL_MAX];
    
    //9 : périphériques I2C reconnus par système
        //MACRO des matériels :
        //  I2C_DEV_ADS1015 = 0
        //  I2C_DEV_ADS1115 = 1
        extern long acquisition_channel_i2c_dev;

    //10 : enregistrement de configuration des channels ADC connecté par I2C
        //en sachant que les valeurs de configuration sont identiques aux celles-effectuées
        //  sur les périphériques de chaque channel, on pourrait reconnaît facilement les paramètres intéressants
        //MACRO de configuration en fonction de périphérique et des configurations concrêtes : 
        //  ADS1015 :
        //      ADS1015_CFG_REG_...
        extern int acquisition_channel_i2c_adc_cfig_reg[CHANNEL_MAX];

    //11 : définir la type d capteur connecté avec ce channel
        //MACRO :   CAP_UNKNOW
        //          CAP_AFF755B
        //          CAP_AA747
        //          CAP_STEFAN_MAYER    
        extern unsigned char acquisition_channel_capteur[CHANNEL_MAX];


    //12 : utilisation standard de l'écran LCD
        extern LiquidCrystal lcd;

    //13 : définir le channel dont LCD illustre des données
        extern unsigned char affichage_acquisition_channel ;

   

    //15 :  définir le statut de l'écran
        //MACRO :   AFFICHAGE_ACQUISITION_ETEINT
        //          AFFICHAGE_ACQUISITION_ALLUME    
        extern char affichage_statut ; 
    
    //16 :  compteur du temps pour réaliser la fonction d'affichage en 5 sec après un appui des boutons
        extern long affichage_time_counter ;//si counter > 5000 [ms], affichage_statut devient 0



    //19 :  le buffer de la transmission I2C avec les ADC
        extern char i2c_buffer[I2C_BUFFER_LENGTH];

    //20 : type de capteur de chaque channel
        extern signed long acquisition_channel_capteur_coef_10nT_100uV[CHANNEL_MAX];
        extern signed long acquisition_channel_capteur_offset_100uV[CHANNEL_MAX];
    //21 : variable globale pour la valeur reçue par le potentiomètre
        extern int val_poten_actu;
        extern int val_poten_last;

#endif //VAR
