#include "acquisition.h"
#include "Arduino.h"

/***********************************************************************************************
 * 
 * 
 *                      module de l'acquisition de données
 * 
 *          auteur : YIN Zihua
 *          nom du projet : Réalisation de capteur du champ magnétique
 *          NO. de version du programme : 1.4
 *          date du release : 2018/05/29
 * 
 *          description de fonctionnement :
 * 
 * 
 * ********************************************************************************************/
  //constructeur de la classe 'Acquisition'
  Acquisition::Acquisition(void)
  {

  }
 

/********************************************************************************
 ********************                                    ************************
 ********************   la configuration d'acquisition   ************************
 ********************                                    ************************
 *******************************************************************************/

  //cette fonction permet de réaliser la configuration de système
  void Acquisition::acquisition_config(void)
  {
    //0 : declaration et initialisation des variables pour determiner les configurations de l'acquisition des données
      //0.1 : l'indice des configurations, on affiche le nom de cette configuration et c'est sur laquelle l'opération est pratiquée
        //sous_config_index_lcd = 0 >> valid
        //                        1 >> nb de channels
        //                        2 >> ratio
        //                        3 >> channels config
        //initialisée à 'nb de channels'
        int sous_config_index_acqui = 1;

      //0.2 : le maximum de l'indice des configurations dans ce menu
        int config_index_max = 3;

      //0.3 : l'operation sur les onglets de configurations
        int operation = OP_NO_OPERATION;

      //0.4 : validation des configurations
        int valid_config = 0;
        
    //1 : modification des configurations de l'acquisition
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0){
        //1.1 : 
          if(bp.bouton_if_pushed(BP_ENTER)){
            switch(sous_config_index_acqui){
              case 0:{
                valid_config = 1;
                break;
              }
              case 1:{
                acqui.acquisition_config_nb_channel();
                break;
              }
              case 2:{
                acqui.acquisition_config_ratio_echan();
                break;
              }
              case 3:{
                acqui.acquisition_config_channel();
                break;
              }
              default:break;
            }
          }
          else sous_config_index_acqui = configu.configuration_shift_index_potentiometre(config_index_max);

        //1.3 : affichage des onglets
          lcd.clear();
          switch(sous_config_index_acqui){
            case 0 :{
              affi.affi_carac("Valid",0,0);
              affi.affi_carac("Acquisition",0,1);
              break;
            }
            case 1:{
              affi.affi_carac("Nb of Channels",0,0);
              affi.affi_2_nb(acquisition_nb_channel,0,1);
              affi.affi_carac("channels",4,1);
              break;
            }
            case 2:{
              affi.affi_carac("Ratio d'Echan",0,0);
              break;
            }
            case 3:{
              affi.affi_carac("Channels Config",0,0);
            }
            default:break;
          }
          delay(50);
      }
     while(bp.bouton_if_pushed(BP_ENTER));
  }

  void Acquisition::acquisition_config_nb_channel(void)
  {
    //0 : déclaration et initialisation des variables
      int val;
      int division = 1024/CHANNEL_MAX;

    //1 : affichage des caractères  
      lcd.clear();
      affi.affi_carac("acquisition of",0,0);
      affi.affi_carac("channels", 4,1);
      
    //2 : saisir la valeur désirée par le potentiomètre  
      while(bp.bouton_if_pushed(BP_ENTER));
      while(!(bp.bouton_if_pushed(BP_ENTER))){
        //2.1 : lecture de la valeur sur potentiomètre  
          val = analogRead(PIN_POTENTIOMETRE);

        //2.2 : calcul de l'indice de channel 
          acquisition_nb_channel = (val / division) + 1;

        //2.3 : affichage de l'indice du channel choisi
          affi.affi_2_nb(acquisition_nb_channel, 0,1);
      }

    //3 : rendre par défaut l'état des channels   
      acqui.acquisition_config_channel_connexion_default(acquisition_nb_channel);

    //4 : fin de fonction en attendant qu'aucune bouton soit appuyé
      while(bp.bouton_if_pushed(BP_ENTER));
  }

  void Acquisition::acquisition_config_ratio_echan(void)
  {
    //actually no decision for the control of vitesse
    affi.affi_carac("nothing to do",0,0);
    delay(2000);
  }

  void Acquisition::acquisition_config_channel()
  {
    //0 : declaration et initialisation des variables pour determiner 
    //    les configurations des channels d'acquisitions des datas
      //0.1 : l'indice de la configuration visee
        //sous_config_index_lcd = 0 >> valid
        //                        1 >> initialisation
        //                        2 >> user setting
        //                        3 >> channel statuts
        int sous_config_index_acqui_channel = 1;

      //0.2 : le maximum de l'indice des configurations du lcd
        int config_index_max = 3;

      //0.3 : l'operation sur le menu de configurations
        int operation = OP_NO_OPERATION;

      //0.4 : validation des configurations
        int valid_config = 0;
        
    //1 : modification des configurations des channels d'acquisition
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0){
        
        
        //1.2 : operation sur les onglets 
          if(bp.bouton_if_pushed(BP_ENTER)){
            switch(sous_config_index_acqui_channel){
              case 0 :{
                valid_config = 1;
                break;
              }
              case 1:{
                acqui.acquisition_config_channel_connexion_default(acquisition_nb_channel);
                break;
              }
              case 2:{
                acqui.acquisition_config_channel_connexion_user_setting();
                break;
              }
              case 3:{
                acqui.acquisition_config_channel_statut_actual();
                break;
              }
            }
          }
          else sous_config_index_acqui_channel = configu.configuration_shift_index_potentiometre(config_index_max);
        
        //1.3 : affichage des onglets
          lcd.clear();
          switch(sous_config_index_acqui_channel){
            case 0 : {
              affi.affi_carac("Valid",0,0);
              affi.affi_carac("Channel Config",0,1);
              break;
            }
            case 1 : {
              affi.affi_carac("Connex (Default)",0,0);
              break;
            }
            case 2 : {
              affi.affi_carac("Connex User Set",0,0);
              break;
            }
            case 3 : {
              affi.affi_carac("Actual Statut",0,0);
              break;
            }
            default: break;
          }
          delay(50);
      }
      while(bp.bouton_if_pushed(BP_ENTER));
  }

  //apres cette fonction, les premiers channels de nombre 'channel_nb' vont etre actives
  //et ils sont initialises en channels d'entree analogue
  void Acquisition::acquisition_config_channel_connexion_default(int channel_nb)
  {
    lcd.clear();
    affi.affi_carac("Setting...",0,0);

    //acquisition_nb_channel = 1;


    acquisition_channel_i2c_addr[0] = ADS1015_ADDR_PIN_GND;
    i2c.i2c_channel_config_dev(0,I2C_DEV_ADS1015);
    acquisition_channel_i2c_adc_cfig_reg[0] = i2c.i2c_ads1015_cfig_reg_value(ADS1015_CFIG_REG_OS_SINGLE_CONV_START,
                                                                        ADS1015_CFIG_REG_MUX_AIN0_AIN1,
                                                                        ADS1015_CFIG_REG_PGA_FSR_2048,
                                                                        ADS1015_CFIG_REG_MODE_CONV_SINGLE,
                                                                        ADS1015_CFIG_REG_DR_1600,
                                                                        ADS1015_CFIG_REG_COMP_MODE_TRAD,
                                                                        ADS1015_CFIG_REG_COMP_POL_LOW,
                                                                        ADS1015_CFIG_REG_COMP_LAT_NO_LATCH,
                                                                        ADS1015_CFIG_REG_COMP_QUE_DISABLE_COMP);
    acquisition_channel_capteur[0] = CAP_STEFAN_MAYER;
    
    delay(1000);
  }

  void Acquisition::acquisition_config_channel_connexion_user_setting(void)
  {
    //0 : declaration et initialisation des variables pour determiner les ports analog
      //0.1 : l'indice de la configuration visee
        //sous_config_index_lcd = 0 >> valid
        //                        1 >> channel 0#
        //                        2 >> channel 1#
        //                        3 >> channel 2# 
        //                        4 >> ...
        int sous_config_index_acqui_user_setting = 1;

      //0.2 : le maximum de l'indice des configurations du lcd
        int config_index_max = acquisition_nb_channel;

      //0.3 : l'operation sur le menu de configurations
        int operation = OP_NO_OPERATION;

      //0.4 : validation des configurations
        int valid_config = 0;
    
    //1 : modifications
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0){
        

        //1.2 : operations sur les onglets
          if(bp.bouton_if_pushed(BP_ENTER)){
            //1.2.1 : validation des configuration sur les channels
            if(sous_config_index_acqui_user_setting == 0)valid_config = 1;
            else acqui.acquisition_config_channel_connexion_user_setting_single_channel(sous_config_index_acqui_user_setting - 1);
          }
          else sous_config_index_acqui_user_setting = bp.bouton_multilevel_potentiometre(config_index_max + 1);


        //1.3 : affichages des onglets
          lcd.clear();
          if(sous_config_index_acqui_user_setting == 0){
            affi.affi_carac("Valid",0,0);
            affi.affi_carac("Connex User Set",0,1);
          }
          else {
            affi.affi_carac("Channel ",0,0);
            affi.affi_2_nb(sous_config_index_acqui_user_setting - 1,8,0);
          }
          delay(50);
      }
      while(bp.bouton_if_pushed(BP_ENTER));
  }

  void Acquisition::acquisition_config_channel_connexion_user_setting_single_channel(int channel)
  {
    //0 : declaration et initialisation des variables pour determiner les ports analog
      //0.1 : l'indice de la configuration visee
        //sous_config_index_lcd = 0 >> valid
        //                        1 >> type connexion
        //                        2 >> type capteur
        int sous_config_index_acqui_user_setting_single_channel = 1;

      //0.2 : le maximum de l'indice des configurations du lcd
        int config_index_max = 2;

      //0.3 : l'operation sur le menu de configurations
        int operation = OP_NO_OPERATION;

      //0.4 : validation des configurations
        int valid_config = 0;
    
    //1 : modifications
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0){
        

        //1.2 : operations sur les onglets
          if(bp.bouton_if_pushed(BP_ENTER)){
            //1.2.1 : des configuration sur ce channel
              switch(sous_config_index_acqui_user_setting_single_channel){
              case 0:{
                valid_config = 1;
                break;
              }
              case 1:{
                i2c.i2c_channel_config(channel);
                break;
              }
              case 2:{
                acqui.acquisition_config_channel_user_setting_capteur_type(channel);
                break;
              }
              default: break;
            }
          }
          else sous_config_index_acqui_user_setting_single_channel = configu.configuration_shift_index_potentiometre(config_index_max);
          

        //1.3 : affichages des onglets
          lcd.clear();
          switch(sous_config_index_acqui_user_setting_single_channel){
            case 0 :{
              affi.affi_carac("Valid",0,0);
              affi.affi_carac("Channel Setting",0,1);
              break;
            }
            case 1 : {
              affi.affi_carac("I2C Config",0,0);
              break;
            }
            case 2 : { 
              affi.affi_carac("Capteur",0,0);
              break;
            }
            default : break;
          }
          delay(50);
      }
      while(bp.bouton_if_pushed(BP_ENTER));
  }

  void Acquisition::acquisition_config_channel_user_setting_capteur_type(int channel)
  {
    //0 : declaration et initialisation des variables pour determiner le type de capteur
      //0.1 : l'indice de la configuration visee
        //sous_config_index_lcd = 0 >> Stefan Mayer
        //                        1 >> AFF755B
        //                        2 >> AA747
        int sous_config_index_acqui_user_setting_type_capteur = 0;

      //0.2 : le maximum de l'indice des configurations du lcd
        int config_index_max = 2;

      //0.3 : l'operation sur le menu de configurations
        int operation = OP_NO_OPERATION;

      //0.4 : validation des configurations
        int valid_config = 0;
    
    //1 : modifications
      while(bp.bouton_if_pushed(BP_ENTER));
      // while(bp.bouton_if_pushed(BP_ENTER));/
      while(valid_config == 0){
        //1.2 : operations sur les onglets
          if(bp.bouton_if_pushed(BP_ENTER)){
            switch(sous_config_index_acqui_user_setting_type_capteur){
              case 0:{
                acquisition_channel_capteur[channel] = CAP_STEFAN_MAYER;
                valid_config = 1;
                break;
              }
              case 1:{
                acquisition_channel_capteur[channel] = CAP_AFF755B;
                valid_config = 1;
                break;
              }
              default: break;
            }
          }
          else sous_config_index_acqui_user_setting_type_capteur = configu.configuration_shift_index_potentiometre(config_index_max);

        //1.3 : affichage d'onglets
          lcd.clear();
          switch(sous_config_index_acqui_user_setting_type_capteur){
            case 0:{
              affi.affi_carac("STEFAN MAYER",0,0);
              break;
            }
            case 1:{
              affi.affi_carac("AFF755B",0,0);
              break;
            }
            case 2 : {
              affi.affi_carac("AA747",0,0);
              break;
            }
            default:break;
          }
          delay(50);
      }  
      while(bp.bouton_if_pushed(BP_ENTER)); 
  }


  void Acquisition::acquisition_config_channel_statut_actual(void)
  {
    //0 : declaration et initialisation permettant la visualisation des statuts des channels
      //index_channel = 0 >> onglet de validation
      //                1 >> channel 0#
      //                2 >> channel 1#
      //                ...
      int index_channel = 0;
      int page = 0;
      int operation = OP_NO_OPERATION;
      int valid = 0;

    //1 : visualisation
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid == 0){

        //1.2 : operation sur les onglets
          // if(bp.bouton_if_pushed(BP_ENTER))  valid = 1;
          // else index_channel = bp.bouton_multilevel_potentiometre(acquisition_nb_channel);
          

          if(bp.bouton_if_pushed(BP_ENTER)){
            while(bp.bouton_if_pushed(BP_ENTER));
            if(index_channel == 0 ) valid = 1;
            else page = maths.incrementation_modulo(page, 2);
          }
          else index_channel = bp.bouton_multilevel_potentiometre(acquisition_nb_channel + 1);

        //1.3 : affichage des infos du channel
          //1.3.1 : onglet de validation
            lcd.clear();
            if(index_channel == 0){
              affi.affi_carac("Valid",0,0);
              affi.affi_carac("Statut Actual",0,1);
            }
          //1.3.2 : onglets des channels d'acquisition
            else{
                affi.affi_carac("Channel ",0,0);
                affi.affi_2_nb((index_channel - 1), 9,0);
              //1.3.2.1 : s'il est page 0#
                if(page == 0){
                    affi.affi_carac("I2C",0,1);
                    affi.affi_carac("Addr",4,1);
                    affi.affi_6_nb(acquisition_channel_i2c_addr[index_channel - 1], 9,1);
                
                }
              //1.3.2.2 : s'il est page 1#
                else if(page == 1){
                  switch(acquisition_channel_capteur[index_channel - 1]){
                    case CAP_AFF755B : {
                      affi.affi_carac("CAP AFF755B",0,1);
                      break;
                    }
                    case CAP_STEFAN_MAYER :{
                      affi.affi_carac("CAP STEFAN MAYER",0,1);
                      break;
                    }
                    default : break;
                  }
                }
              //1.3.2.3 : page 2# >> intervalle mesurable du champ magnétique
            }
  	      delay(50);
      }    
      while(bp.bouton_if_pushed(BP_ENTER));
  }


/********************************************************************************
 ********************                                    ************************
 ********************    la deroulement d'acquisition    ************************
 ********************                                    ************************
 *******************************************************************************/


  //retourne la valeur mesurée du champ magnétique par une voix de transmission I2C
    signed int Acquisition::acquisition_lecture_i2c(int channel)
    {
      signed int val_mV = i2c.i2c_acquisition(channel, ACQUISITION_UNITE_MV);
      
      return val_100uV; 
    }

  // cette fonction lance un échantillonnage en balayant tous les channels activés
    void Acquisition::acquisition_lecture_data(void)
    {
      // 0 : déclaration d'une variable pour la balayage des channels
        int channel = 0;
        int val_100uV = 0;
      // 1 : balayage des channels
        for(channel = 0; channel < acquisition_nb_channel; channel ++)
        {
          // 1.1 : ce channel est du type numérique (I2C)
            val_100uV = acqui.acquisition_lecture_i2c(channel);
           

          // 1.2 : recalcul et stockage de valeur mesurée
            acquisition_data_100nT[channel] = cap.cap_100uV_to_100nT(channel, val_100uV);
        }
    }


/********************************************************************************
 ********************                                    ************************
 ********************       le test d'acquisition        ************************
 ********************                                    ************************
 *******************************************************************************/

  void Acquisition::acquisition_test_data(void)
  {
    int i;
    for(i = 0 ; i < CHANNEL_MAX ; i++){
      acquisition_data_100nT[i] = i;
    }
  }
  
