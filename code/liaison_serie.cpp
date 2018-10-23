#include "liaison_serie.h"
#include "Arduino.h"

/***********************************************************************************************
 * 
 * 
 *                      module du port liaison série
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

  RS232::RS232()
  {

  }

  void RS232::serial_config(void)
  {
    
    //menu : 
    //  |Valid| |Activation| |Baudrate|

    //0 : declaration et initialisation des variables pour determiner la configuration
      //0.1 : l'indice de la configuration visee
        //sous_config_index = 0 >> validation de configurations
        //                    1 >> Serial Port Activation
        //                    2 >> Serial Port Baudrate
        int sous_config_index_serial = 1; 

      //0.2 : le maximum de l'indice des configurations
        // valid(0), activation(1), baudrate(2)
        int config_index_max = 2; 

      //0.3 : l'operation sur le menu de configurations
        //OP_NO_OPERATION >> menu ne bouge pas
        //OP_GO_RIGHT     >> menu tournement vers le droit (index = index + 1)
        int operation = OP_NO_OPERATION;

      //0.4 : validation de configuration
        //valid_config = 1 >> sortir de cette fonction
        //                    les modifications vont etre prises en compte 
        int valid_config = 0;
    
    //1 : modification des configurations de l'appareil
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0){
        //1.1 : determination d'operation sur le menu par les appuis de boutons

        //1.2 : operation sur les onglets
          if(bp.bouton_if_pushed(BP_ENTER)){
            switch(sous_config_index_serial){
              case 0:{
                valid_config = 1;
                break;
              }
              case 1:{
                rs232.serial_config_activation();
                break;
              }
              case 2:{
                rs232.serial_config_baudrate();
                break;
              }
              default:break;
            }
          }
          else sous_config_index_serial =  configu.configuration_shift_index_potentiometre(config_index_max);
          

        //1.3 : affichage de l'onglet
          lcd.clear();
          switch(sous_config_index_serial){
            case 0:{
              affi.affi_carac("Valid",0,0);
              affi.affi_carac("Serial Port",0,1);
              break;
            }
            case 1:{
              affi.affi_carac("Activation",0,0);
              break;
            }
            case 2:{
              affi.affi_carac("Baudrate",0,0);
              break;
            }
            default:break;
          }
          delay(50);
      }
      while(bp.bouton_if_pushed(BP_ENTER));
  }

  void RS232::serial_config_on_default(void)
  {
    rs232.serial_send_cancel();
  }

  void RS232::serial_config_baudrate(void)
  {
    Serial.begin(serial_data_ratio_setting());
    lcd.clear();
  }

  void RS232::serial_config_activation(void)
  {
    //menu : 
    //  |Y| |N|

    //0 : declaration et initialisation des variable pour detereminer les configurations 
      //0.1 : l'indice de la configuration visee
        //sous_config_index = 0 >> Yes for send
        //                    1 >> No  for send
        int sous_config_index_serial_activation = 0;  
        
      //0.2 : le maximum de l'indice des configurations
        int config_index_max = 1;

      //0.3 : l'operations sur le menu de configurations
        int operation = OP_NO_OPERATION;

      //0.4 : validation de configurations
        //valid = 1 >> sortir de cette fonction
        //             la modifications va etre prise en compte
        int valid_config = 0;

    //1 : modification de l'activation
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0 ){
        //1.1 : determination d'operation sur le menu par les appuis de boutons

        //1.2 : operation sur les onglets
          if(bp.bouton_if_pushed(BP_ENTER)){
            switch(sous_config_index_serial_activation){
              case 0:{
                rs232.serial_send_set_up();
                break;
              }
              case 1:{
                rs232.serial_send_cancel();
                break;
              }
              default:break;
            }
            valid_config = 1;
          }
          else sous_config_index_serial_activation = configu.configuration_shift_index_potentiometre(config_index_max);
          

        //1.3 : affichage des onglets
          lcd.clear();
          switch(sous_config_index_serial_activation){
            case 0:{
              affi.affi_carac("YES",0,0);
              break;
            }
            case 1:{
              affi.affi_carac("NO",0,0);
              break;
            }
          }
          delay(50);
      }
      while(bp.bouton_if_pushed(BP_ENTER));
  }

  void RS232::serial_send_set_up(void)
  {
    mode.mode_set_up(MODE_SEND_BY_SERIAL);
  }

  void RS232::serial_send_cancel(void)
  {
    mode.mode_cancel(MODE_SEND_BY_SERIAL);
  }

  long RS232::serial_data_ratio_setting(void)
  {
    //0 : declaration et initialisation de variables
      long val_ratio = 9600;

    //1 : affichage d'indication de la premiere ligne
      lcd.clear();
      affi.affi_carac("transmit ratio:",0,0);

    //2 : modification du baudrate de l'envoi
      while(bp.bouton_if_pushed(BP_ENTER));
      while (!(bp.bouton_if_pushed(BP_ENTER))) {
        if (analogRead(A0) < (1024 / 7))val_ratio = 9600;
        else if (analogRead(A0) < (2 * 1024 / 7))val_ratio = 14400;
        else if (analogRead(A0) < (3 * 1024 / 7))val_ratio = 19200;
        else if (analogRead(A0) < (4 * 1024 / 7))val_ratio = 28800;
        else if (analogRead(A0) < (5 * 1024 / 7))val_ratio = 38400;
        else if (analogRead(A0) < (6 * 1024 / 7))val_ratio = 57600;
        else val_ratio = 115200;
        affi.affi_6_nb(val_ratio, 10, 1);
      }
      
    //3 : attente d'une lache du bouton 
      while (bp.bouton_if_pushed(BP_ENTER)); //attente d'une lache

    return val_ratio;
  }

  void RS232::serial_streaming(void)
  {
    rs232.serial_data_starting();
    //serial_data_4_chiffres();// ??? what's for data
    rs232.serial_data_ending();
  }

  void RS232::serial_data_starting(void)
  {
    Serial.print("v");
  }

  void RS232::serial_data_ending(void)
  {
    Serial.print("\n");
  }

  void RS232::serial_data_4_chiffres(int data)
  {
    if (data < 1000)Serial.print(0);
    if (data < 100) Serial.print(0);
    if (data < 10)  Serial.print(0);
    Serial.print(data);  
  }

  void RS232::serial_test_sinus_to_pc(void)
  {
    int val_sinus = (int) (500 * sin(2 * PI * millis() / 1000) + 512);
    if (val_sinus < 1000)Serial.print(0);
    if (val_sinus < 100) Serial.print(0);
    if (val_sinus < 10)  Serial.print(0);
    Serial.print(val_sinus);
    Serial.print(" ");
    Serial.print("v");
  }
