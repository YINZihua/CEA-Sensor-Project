#include "affichage.h"
#include "Arduino.h"

/***********************************************************************************************
 * 
 * 
 *                      module de l'affichage sur l'écran LCD
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

  LiquidCry::LiquidCry()
  {

  }

  void LiquidCry::affi_init_animation(void)
  {
    lcd.begin(16, 2);

    affi.affi_init_title( 400);
    affi.affi_init_title( 400);
    affi.affi_init_title( 400);
    affi.affi_init_title( 400);
    affi.affi_init_title( 2000);
  }

  void LiquidCry::affi_init_title(int delay_affi_ms)
  {
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM CAP MAGNET");
    lcd.setCursor(0, 1);
    lcd.print("CEA SACLAY");
    delay(delay_affi_ms);
    lcd.clear();
    delay(200);
  }

  void LiquidCry::affi_config(void)
  {
    //0 : declaration et initialisation des variables pour determiner les configurations de LCD
      //0.1 : l'indice de la configuration visee
        //sous_config_index_lcd = 0 >> affichage permanente
        //                        1 >> affichage d'un seul coup apres d'appui d'un bouton
        int sous_config_index_lcd = 0;

      //0.2 : le maximum de l'indice des configurations du lcd
        int config_index_max = 1;

      //0.3 : l'operation sur le menu de configurations
        int operation = OP_NO_OPERATION;

      //0.4 : validation des configurations
        int valid_config = 0;
        
    //1 : modification des configurations de LCD
      while(bp.bouton_if_pushed(BP_ENTER));
      while(valid_config == 0){
        //1.1 : determination d'operation sur le menu par les appuis de boutons

        //1.2 : operation sur les onglets
          if(bp.bouton_if_pushed(BP_ENTER)){
            switch(sous_config_index_lcd){
              case 0:{
                affi.affi_mode_permanent_set_up();
                break;
              }
              case 1:{
                affi.affi_mode_affi_apres_bouton();
                break;
              }
              default:break;
            }
            valid_config = 1;
          }
          else sous_config_index_lcd = configu.configuration_shift_index_potentiometre(config_index_max);
          

        //1.3 : affichage des onglets   
          lcd.clear();
          switch(sous_config_index_lcd){
            case 0:{
              affi.affi_carac("Affi Permanente",0,0);
              break;
            }
            case 1:{
              affi.affi_carac("Affi Apres Appui",0,0);
              break;
            }
          }
          delay(50);
      } 
      while(bp.bouton_if_pushed(BP_ENTER));
  }

  void LiquidCry::affi_config_on_default(void)
  {
    affi.affi_mode_affi_apres_bouton();
  }

  void LiquidCry::affi_mode_permanent_set_up(void)
  {
    mode.mode_set_up(MODE_AFFI_LCD_PERM);
  }

  void LiquidCry::affi_mode_affi_apres_bouton(void)
  {
    mode.mode_cancel(MODE_AFFI_LCD_PERM);
  }

  void LiquidCry::affi_acquisition(void)
  {
    //0 : determination et initialisation des variables pour determiner l'affichage
      int poten_moving = POTEN_DONT_MOVE;

    //0 : determination de l'etat des boutons
    

      poten_moving = bp.bouton_potentiometre_moving_direction();
      

    //1 : determination de l'etat d'affichage
      //1.1 : traitement de l'affichage quand l'ecran eteint (changement de channel affiche, changement de l'etat d'affichage)
        if(affichage_statut == AFFICHAGE_ACQUISITION_ETEINT){
          //1.1.1 : si l'etat de lcd est de "affichage apres un appui"
            if(!(mode.mode_if_used(MODE_AFFI_LCD_PERM))){
              //1.1.1.1 : si un des deux boutons de directions est appuye
                if(poten_moving != POTEN_DONT_MOVE){
                  //1.1.1.1.1 : on va alors allumer l'ecran
                    affichage_statut = AFFICHAGE_ACQUISITION_ALLUME;
                    affi.affi_carac("val mesure",0,0);
                  //1.1.1.1.2 : on lance encore un compteur pour limiter la duree d'affichage en 5 sec
                    affichage_time_counter = millis();
                }
            }
          //1.1.2 : si l'etat de lcd est de "affichage permanente"
            else if(mode.mode_if_used(MODE_AFFI_LCD_PERM)){
              affichage_statut = AFFICHAGE_ACQUISITION_ALLUME;
            }
        }


      //1.2 : traitement de l'affichage quand l'ecran allume (changement de channel affiche, changement de l'etat d'affichage)
        else if(affichage_statut == AFFICHAGE_ACQUISITION_ALLUME){
          //1.2.1 : si les deux boutons de directions ne sont pas appuyes
            if(poten_moving == POTEN_DONT_MOVE){
              //1.2.1.1 : si on est en mode "affichage apres un appui"
                // if((ctrl_mode & MODE_AFFI_LCD_PERM) == 0){
                if(!(mode.mode_if_used(MODE_AFFI_LCD_PERM))){
                  //1.2.1.1.1 : si le temps d'affichage limite est atteint
                    if((millis() - affichage_time_counter) >= 5000){
                      //1.2.1.1.1.1 : on s'arrete a afficher les valeurs et initialiser le compteur du temps 
                        affichage_time_counter = 0;
                        affichage_statut = AFFICHAGE_ACQUISITION_ETEINT;
                        affi.affi_back_light_eteint();
                    }   
                  //1.2.1.1.2 : rien a fait si le temps limite d'affichage n'est pas atteint                                 
                }
            }
          //1.2.2 : si un des deux boutons est appuye
            else{
              //1.2.2.1 : si l'ecran est en mode "affichage apres un appui"
                if(!(mode.mode_if_used(MODE_AFFI_LCD_PERM))){
                  //1.2.2.1.1 : on reinitialise le compteur
                    affichage_time_counter = millis(); 
                }
              //1.2.2.2. : on change la channel dont la valeur mesure va etre illustree
                affichage_acquisition_channel = bp.bouton_multilevel_potentiometre(acquisition_nb_channel);
            }
        }

    //2 : mis à jour de l'affichage
      if(affichage_statut == AFFICHAGE_ACQUISITION_ALLUME){
        affi.affi_carac("CHANNEL",0,0);
        affi.affi_2_nb(affichage_acquisition_channel,7,0);
        affi.affi_carac("#",10,0);

        affi.affi_magnetic_field_100nT(acquisition_data_100nT[affichage_acquisition_channel], 0 ,1);
        affi.affi_carac("uT",14,1);
        affi.affi_back_light_allume();
      }
      //on ne fait pas lcd.clear ici pour affichage_statut == ETEINT puisqu'il prend trop du temps pour clear() l'ecran chaque fois quand on rentre ici
  }

  void LiquidCry::affi_back_light_allume(void)
  {
    if(digitalRead(LCD_BACKLIGHT) == LOW) digitalWrite(LCD_BACKLIGHT, HIGH);
  }

  void LiquidCry::affi_back_light_eteint(void)
  {
    lcd.clear();
    if(digitalRead(LCD_BACKLIGHT) == HIGH) digitalWrite(LCD_BACKLIGHT,LOW);
  }

  void LiquidCry::affi_carac(String carac, int cursor_col, int cursor_rang)
  {
    lcd.setCursor(cursor_col, cursor_rang);
    lcd.print(carac);
  }

  bool LiquidCry::affi_2_nb(int data, int cursor_col, int cursor_rang)
  {
    lcd.setCursor(cursor_col, cursor_rang);
    if (data >= 0){
      lcd.print("+");
      if(data <= 99){ 
        if (data < 10)   lcd.print(0);
        lcd.print(data);
        return true;
      }
      else {
        lcd.print(99);
        lcd.print("*");
        return false;
      }
    }
    else{
      lcd.print("-");
      if(data >= -99){
        if(data > -10)    lcd.print(0);
        lcd.print(-data);
        return true;
      }
      else {
        lcd.print(99);
        lcd.print("*");
        return false;
      }
    }
  }

  bool LiquidCry::affi_4_nb(int data, int cursor_col, int cursor_rang)
  {
    lcd.setCursor(cursor_col, cursor_rang);
    if (data >= 0){
      lcd.print("+");
      if(data <= 9999){ 
        if (data < 1000) lcd.print(0);
        if (data < 100)  lcd.print(0);
        if (data < 10)   lcd.print(0);
        lcd.print(data);
        return true;
      }
      else {
        lcd.print(9999);
        lcd.print("*");
        return false;
      }
    }
    else{ //data < 0
      lcd.print("-");
      if(data >= -9999){
        if(data > -1000)  lcd.print(0);
        if(data > -100)   lcd.print(0);
        if(data > -10)    lcd.print(0);
        lcd.print(-data);
        return true;
      }
      else {
        lcd.print(9999);
        lcd.print("*");
        return false;
      }
    }
  }

  // cette fonction permet d'afficher un nombre de 6 chiffres
  bool LiquidCry::affi_6_nb(long data, int cursor_col, int cursor_rang)
  {
    lcd.setCursor(cursor_col, cursor_rang);
    if (data >= 0){
      lcd.print("+");
      if(data <= 999999){ 
        if (data < 100000) lcd.print(0);
        if (data < 10000)  lcd.print(0);
        if (data < 1000) lcd.print(0);
        if (data < 100)  lcd.print(0);
        if (data < 10)   lcd.print(0);
        lcd.print(data);
        return true;
      }
      else {
        lcd.print(999999);
        lcd.print("*");
        return false;
      }
    }
    else{
      lcd.print("-");
      if(data >= -999999){
        if(data > -100000)lcd.print(0);
        if(data > -10000) lcd.print(0);
        if(data > -1000)  lcd.print(0);
        if(data > -100)   lcd.print(0);
        if(data > -10)    lcd.print(0);
        lcd.print(-data);
        return true;
      }
      else {
        lcd.print(999999);
        lcd.print("*");
        return false;
      }
    }
  }

  // 'data' est une valeur qui représente le champ magnétique en [0,1µT] et ne passe pas à (9999,9µT) ou (9,9999mT)
  void LiquidCry::affi_magnetic_field_100nT(long data, int cursor_col, int cursor_rang)
  {
    lcd.setCursor(cursor_col, cursor_rang);
    if (data >= 0){
      lcd.print("+");
      if(data <= 99999){ 
        if (data < 10000)  lcd.print(0);
        if (data < 1000) lcd.print(0);
        if (data < 100)  lcd.print(0);

        lcd.print(data/10);
        lcd.print(".");
        lcd.print(data%10);
        return true;
      }
      else {
        lcd.print(999999);
        lcd.print("*");
        return false;
      }
    }
    else{
      lcd.print("-");
      if(data >= -99999){
        if(data > -10000) lcd.print(0);
        if(data > -1000)  lcd.print(0);
        if(data > -100)   lcd.print(0);

        lcd.print((-data)/10);
        lcd.print(".");
        lcd.print((-data)%10);
        
        return true;
      }
      else {
        lcd.print(999999);
        lcd.print("*");
        return false;
      }
    }
  }

  void LiquidCry::affi_binary(long data, int data_length, int cursor_col, int cursor_rang)
  {
    lcd.setCursor(cursor_col, cursor_rang);
    int indice;
    for(indice = data_length - 1; indice >= 0; indice--){
      if(data | (1<<indice)) lcd.print(1);
      else lcd.print(0);
    }
  }


  void LiquidCry::affi_nTesla(long data, int cursor_col, int cursor_rang)
  {
    affi.affi_6_nb(data, cursor_col, cursor_rang);
  }