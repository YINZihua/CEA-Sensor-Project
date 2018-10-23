#include "configuration.h"
#include "Arduino.h"

/***********************************************************************************************
 * 
 * 
 *                      module du contrôle des configurations
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
  Configuration::Configuration()
  {

  }

  void Configuration::configuration_feature(void)
  {    
    //0 : declaration et initialisation des variables pour determiner les configurations
      //0.1 : l'indice de l'onglet
        //config_index =  0 >> validation des configurations
        //                1 >> Serial Port
        //                2 >> LCD
        //                3 >> SD Card
        //                4 >> Acquisition des donnees
        int config_index = 1;

      //0.2 : le maximum de l'indice des configurations
        int config_index_max = 4;

      //0.3 : l'operation sur le menu de configurations
        int operation = OP_NO_OPERATION;

      //0.4 : validation de configurations
        int valid_config = 0;

    //1 : mise a jour de l'affichage sur LCD
      lcd.clear();
      affi.affi_carac("config mode",0,0);
      affi.affi_carac("capture stopped",0,1);
      delay(2000);
      lcd.clear();

    //2 : modification sur les configurations 
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0){
        //2.1 : accès aux différents onglets
          if(bp.bouton_if_pushed(BP_ENTER)){
            switch(config_index){
              case 0:{
                valid_config = 1;
                break;
              }
              case 1:{
                rs232.serial_config();
                break;
              }
              case 2:{
                affi.affi_config();
                break;
              }
              case 3:{
                mysd.sd_config();
                break;
              }
              case 4:{
                acqui.acquisition_config();
                break;
              }
              default:break;
            }
          }
          else config_index = configu.configuration_shift_index_potentiometre(config_index_max);

        //2.2 : affichage d'onglet
          lcd.clear();
          switch(config_index){
            case 0:{
              affi.affi_carac("Valid",0,0);
              affi.affi_carac("Config Features",0,1);
              break;
            }
            case 1 :{
              affi.affi_carac("Serial Port",0,0);
              break;
            }
            case 2 :{
              affi.affi_carac("LCD",0,0);
              break;
            }
            case 3 :{
              affi.affi_carac("SD Card",0,0);
              break;
            }
            case 4 :{
              affi.affi_carac("Acquisition",0,0);
              break;
            }
          }
          delay(50);
      }
    
    //3 : indication de l'enregistrement
      lcd.clear();
      affi.affi_carac("Config Saved",0,0);
      delay(1500);
    
    //4 : si l'affichage est en mode "affichage apres un appui"
      if((ctrl_mode & MODE_AFFI_LCD_PERM) == 0){
        affichage_time_counter = millis();
        affichage_statut = AFFICHAGE_ACQUISITION_ALLUME;
      }

    //5 : apres la configuration, on lancera l'affichage d'acquisition de toute facon
      lcd.clear();
      // affi.affi_carac("val mesure",0,0);

      
    //re-initialisation de bus i2c en fonction des configurations des channels
      i2c.i2c_init();

    //set up for sensors transform values
      cap.cap_coef_uT_V_setup();

      while(bp.bouton_if_pushed(BP_ENTER));
  }


  void Configuration::configuration_on_default(void)
  {
    //Serial Port
      rs232.serial_config_on_default();

    //Affichage
      affi.affi_config_on_default();

    //SD Card
      mysd.sd_usage_cancel();

    //Acquisition
      // acqui.acquisition_default
  }

  int Configuration::configuration_shift_index_potentiometre(int index_max)
  {
    return bp.bouton_menu_index(index_max);
  }
