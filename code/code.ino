#include "constant.h"
#include "variable.h"

void setup() {
  // la transmission en série doit toujours ouverte pour que le logiciel puisse transférer les messages d'erreur
      Serial.begin(9600);
      
  //0 : initialisation de boutons
  bp.bouton_init();
  i2c.i2c_init();

  // //1 : i6nitialisation de l'afficheur
  pinMode(LCD_BACKLIGHT, OUTPUT);
  lcd.begin(16, 2);
  affi.affi_back_light_allume();
  affi.affi_init_animation();

  //2 : configuration globale du systeme
  configu.configuration_feature();

  //3 :premiere affichage de la valeur mesuree
  // lcd.clear();
  // affi.affi_carac("val mesure",0,0);

  //4 : initialisation des donnees en mode test
  acqui.acquisition_test_data();

  //5 : initialisation du timer permettant a generer une pulsation de 17kHz (I2C)
  pulse.init_timer_17kHz();
}

void loop() {
  //0 : si bouton 'enter' est appuyé,
  if (bp.bouton_if_pushed(BP_ENTER)) {
    while (bp.bouton_if_pushed(BP_ENTER));
    //0.1 : on entre dans le mode de configuration, au même temps, l'acquisition du champ magnétique est arrêtée
    affi.affi_back_light_allume();
    configu.configuration_feature();
  }
  //1 : sinon, le systeme deroule normalement
  else if (!(ctrl_mode & MODE_CONFIGURATION)) {
    //1.1 : lancement d'une acquisition sur les channels activés
    acqui.acquisition_lecture_data();
    //1.2 : affichage des valeurs acquises
    affi.affi_acquisition();
  }
}
