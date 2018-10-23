#include "sd_card.h"
#include "variable.h"
#include "Arduino.h"
//#include <SPI.h>
//#include <SD.h>

/***********************************************************************************************
 * 
 * 
 *                      module du contrôle de la carte SD
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

  mySD::mySD()
  {
    
  }

  void mySD::sd_config(void)
  {
    //0 : declaration et initialisation des variables pour determiner l'utilisation de la carte SD
      //0.1 : l'indice de la configuration visee
        //sous_config_index_lcd = 0 >> NO USE SD
        //                        1 >> USE SD CARD
        int sous_config_index_sd = 0;

      //0.2 : le maximum de l'indice des configurations du lcd
        int config_index_max = 1;

      //0.3 : validation des configurations
        int valid_config = 0;

    //1 : modifications des configurations de SD Card
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0){
        //1.1 : determination d'operation sur le menu par les appuis de boutons

        //1.2 : operation sur les onglets
          if(bp.bouton_if_pushed(BP_ENTER)){
            switch(sous_config_index_sd){
              case 0:{
//                if (!SD.begin(4)) {
//                  Serial.println("initialization failed!");
//                  while (1);
//                }
                mysd.sd_usage_cancel();
                break;
              }
              case 1:{
                mysd.sd_usage_set_up();
                break;
              }
              default:break;
            }
            valid_config = 1;
          }
          else sous_config_index_sd = configu.configuration_shift_index_potentiometre(config_index_max);
          

        //1.3 : affichage des onglets
          lcd.clear();
          switch(sous_config_index_sd){
            case 0:{
              affi.affi_carac("SD Use",0,0);
              break;
            }
            case 1:{
              affi.affi_carac("SD No Use",0,0);
              break;
            }
            default:break;
          }
          delay(50);
      }
      while(bp.bouton_if_pushed(BP_ENTER));

  }

  //commencer le stockage des mesurés
  void mySD::sd_usage_set_up(void)
  {
    mode.mode_set_up(MODE_SD_STOCKAGE);
//    myFile = SD.open(PATH_SD,FILE_WRITE);
  }

  //arrêter le stockage
  void mySD::sd_usage_cancel(void)
  {
//    if(myFile){
      mode.mode_cancel(MODE_SD_STOCKAGE);
//      myFile.close();
//    }
  }

  // cette fonction écrit dans le fichier ouvert la valeur mesuré du champ magnétique [0,1µT]
  // et l'information temporelle de cette mesure
  void mySD::sd_write_val_time(int val_mes, int val_time)
  {
    //0 : la première colone est la valeur mesuré, se sépare des caractères suivantes
    //    par un saut de 
//      myFile.print(val_mes);
//      myFile.print("\t");
//    //1 : l'écriture de la valeur de temps
//      myFile.println(val_time);
  }
