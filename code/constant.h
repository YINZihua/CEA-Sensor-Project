#ifndef CONST
#define CONST

#include "LiquidCrystal.h"

/***********************                               *************************
 *********************** definitions des pre-processus *************************
 ***********************                               *************************/
//validation de configuration
    #define NonValid  0
    #define Valid     1

    #define PIN(X)   X

//mode index
    #define MODE_SEND_BY_SERIAL   0x00
    #define MODE_AFFI_LCD_PERM    0X01
    #define MODE_SD_STOCKAGE      0x02
    #define MODE_CONFIGURATION    0X04

//configuration de LCD
    #define LCD_LIGHT_OFF         0x00
    #define LCD_LIGHT_ON          0x01

//constantes de l'acquisation
    #define CHANNEL_MAX                         18
    #define CHANNEL_ERROR                       0X00
    #define CHANNEL_I2C                         0x01
    #define CHANNEL_USED                        0X02
    #define CHANNEL_NO_USED                     0x03
    #define CHANNEL_ANALOG_PORT_AVAILABLE       0x04
    #define CHANNEL_ANALOG_PORT_NO_AVAILABLE    0X05
    #define ACQUISITION_UNITE_MV                0X06
    #define ACQUISITION_UNITE_UV                0x07

//bouton operation
//  the values equals to the pin number of every bouton
    #define OP_NO_OPERATION     0x00
    #define OP_ENTER_CONFIG     PIN(8)
    #define OP_GO_LEFT          0xF0
    #define OP_GO_RIGHT         0xF1
    #define BP_ENTER            OP_ENTER_CONFIG
    #define BP_LEFT             OP_GO_LEFT
    #define BP_RIGHT            OP_GO_RIGHT
    #define BP_NO_PUSHED        0xFFFF

//declartion et initialisation de bouton poussoir
//la valeur du bouton poussoir est identique a son pin nombre sur la carte Arduino UNO




//declaration et initialisation des constantes pour l'affichage sur LCD
    #define AFFICHAGE_ACQUISITION_ETEINT 0 
    #define AFFICHAGE_ACQUISITION_ALLUME 1

//longueur du buffer i2c
    #define I2C_BUFFER_LENGTH 8

//I2C ADC device identifier
    #define DEVICE_ERROR            0x00
    #define I2C_DEV_ADS1015         0X01
    #define I2C_DEV_ADS1115         0X02

//parametres permettant de controler les ADCs sur Bus I2C
//parameters du circuit ADS1015
//parameters pour le registre de configuration de ADS1015

    //valeurs binaire d'adresse de périphérique ads1015
    #define ADS1015_ADDR_PIN_GND  B1001000
    #define ADS1015_ADDR_PIN_VDD  B1001001
    #define ADS1015_ADDR_PIN_SDA  B1001010
    #define ADS1015_ADDR_PIN_SCL  B1001011

    #define ADS1015_ADDR_PTR_CONV_REG 0x00
    #define ADS1015_ADDR_PTR_CFIG_REG 0x01
    #define ADS1015_ADDR_PTR_LOTH_REG 0x10
    #define ADS1015_ADDR_PTR_HITH_REG 0x11

    #define ADS1015_CFIG_REG_OS_OFFSET            15
    #define ADS1015_CFIG_REG_OS_SINGLE_CONV_START 0X01
    #define ADS1015_CFIG_REG_OS_CURRENT_CONV      0X00
    #define ADS1015_CFIG_REG_OS_NO_CURRENT_CONV   0X01

    #define ADS1015_CFIG_REG_MUX_OFFSET           12
    #define ADS1015_CFIG_REG_MUX_AIN0_AIN1        0X00
    #define ADS1015_CFIG_REG_MUX_AIN0_AIN3        0X01
    #define ADS1015_CFIG_REG_MUX_AIN1_AIN3        0x02
    #define ADS1015_CFIG_REG_MUX_AIN2_AIN3        0x03
    #define ADS1015_CFIG_REG_MUX_AIN0_GND         0x04
    #define ADS1015_CFIG_REG_MUX_AIN1_GND         0x05
    #define ADS1015_CFIG_REG_MUX_AIN2_GND         0x06
    #define ADS1015_CFIG_REG_MUX_AIN3_GND         0x07

    #define ADS1015_CFIG_REG_PGA_OFFSET       9
    #define ADS1015_CFIG_REG_PGA_FSR_6144         0x00
    #define ADS1015_CFIG_REG_PGA_FSR_4096         0x01
    #define ADS1015_CFIG_REG_PGA_FSR_2048         0x02
    #define ADS1015_CFIG_REG_PGA_FSR_1024         0x03
    #define ADS1015_CFIG_REG_PGA_FSR_0512         0x04
    #define ADS1015_CFIG_REG_PGA_FSR_0256         0x05

    #define ADS1015_CFIG_REG_MODE_OFFSET          8
    #define ADS1015_CFIG_REG_MODE_CONV_CONTINUE   0x00
    #define ADS1015_CFIG_REG_MODE_CONV_SINGLE     0X01

    #define ADS1015_CFIG_REG_DR_OFFSET            5
    #define ADS1015_CFIG_REG_DR_0128              0X00
    #define ADS1015_CFIG_REG_DR_0250              0X01
    #define ADS1015_CFIG_REG_DR_0490              0x02
    #define ADS1015_CFIG_REG_DR_0920              0x03                
    #define ADS1015_CFIG_REG_DR_1600              0x04
    #define ADS1015_CFIG_REG_DR_2400              0x05
    #define ADS1015_CFIG_REG_DR_3300              0x06

    #define ADS1015_CFIG_REG_COMP_MODE_OFFSET     4
    #define ADS1015_CFIG_REG_COMP_MODE_TRAD       0X00
    #define ADS1015_CFIG_REG_COMP_MODE_WIND       0X01

    #define ADS1015_CFIG_REG_COMP_POL_OFFSET      3
    #define ADS1015_CFIG_REG_COMP_POL_LOW         0X00
    #define ADS1015_CFIG_REG_COMP_POL_HIGH        0X01

    #define ADS1015_CFIG_REG_COMP_LAT_OFFSET      2
    #define ADS1015_CFIG_REG_COMP_LAT_NO_LATCH    0X00
    #define ADS1015_CFIG_REG_COMP_LAT_LATCH       0X01

    #define ADS1015_CFIG_REG_COMP_QUE_OFFSET          0
    #define ADS1015_CFIG_REG_COMP_QUE_ASSERT_AFT_ONE  0X00
    #define ADS1015_CFIG_REG_COMP_QUE_ASSERT_AFT_TWO  0X01
    #define ADS1015_CFIG_REG_COMP_QUE_ASSERT_AFT_FOUR 0X02
    #define ADS1015_CFIG_REG_COMP_QUE_DISABLE_COMP    0X03

//parameters pour le fonctionnement de mesure de ADS1015
    // #define ADS1015_FSR_6144                    ADS1015_CFIG_REG_PGA_FSR_6144
    // #define ADS1015_FSR_4096                    ADS1015_CFIG_REG_PGA_FSR_4096
    // #define ADS1015_FSR_2048                    ADS1015_CFIG_REG_PGA_FSR_2048
    // #define ADS1015_FSR_1024                    ADS1015_CFIG_REG_PGA_FSR_1024
    // #define ADS1015_FSR_0512                    ADS1015_CFIG_REG_PGA_FSR_0512
    // #define ADS1015_FSR_0256                    ADS1015_CFIG_REG_PGA_FSR_0256

    #define ADS1015_ADC_AIN0_AIN1               ADS1015_CFIG_REG_MUX_AIN0_AIN1
    #define ADS1015_ADC_AIN0_AIN3               ADS1015_CFIG_REG_MUX_AIN0_AIN3        
    #define ADS1015_ADC_AIN1_AIN3               ADS1015_CFIG_REG_MUX_AIN1_AIN3        
    #define ADS1015_ADC_AIN2_AIN3               ADS1015_CFIG_REG_MUX_AIN2_AIN3        
    #define ADS1015_ADC_AIN0_GND                ADS1015_CFIG_REG_MUX_AIN0_GND         
    #define ADS1015_ADC_AIN1_GND                ADS1015_CFIG_REG_MUX_AIN1_GND         
    #define ADS1015_ADC_AIN2_GND                ADS1015_CFIG_REG_MUX_AIN2_GND         
    #define ADS1015_ADC_AIN3_GND                ADS1015_CFIG_REG_MUX_AIN3_GND         

//parameters pour la transmission i2c de device ads1015
    #define ADS1015_READ_LENGTH         2


//capteur_id
    #define CAP_UNKNOWN         0X00
    #define CAP_AFF755B         0x01
    #define CAP_STEFAN_MAYER    0x02 

//capteur application
    #define PIN_AFF755B_FLIP_COIL 9

//AFF755B paramètres
    #define AFF755B_TEST_mA_to_uT(mA) ( (int) ( ( (long) mA * 439 ) / 1000 ) )     

//pin du potentiomètre
    #define PIN_POTENTIOMETRE   A0
    #define POTEN_GO_RIGHT      OP_GO_RIGHT
    #define POTEN_GO_LEFT       OP_GO_LEFT
    #define POTEN_DONT_MOVE     BP_NO_PUSHED

//lcd backlight control
    #define LCD_BACKLIGHT       7

//flip coil control
    #define SORTI_CONTROL_FLIP_COIL PIN_AFF755B_FLIP_COIL


//chemin pour le stockage sur SD
#define PATH_SD ("mesure_magnetic_field.txt")


//signe d'erreur
    #define ERROR_INT       0xFFFF
#endif 