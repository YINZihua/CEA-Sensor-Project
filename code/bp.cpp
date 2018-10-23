#include "bp.h"
#include "Arduino.h"

/***********************************************************************************************
 * 
 * 
 *                      module de  l'interface de l'intéraction du système
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

  BoutonPoussoir::BoutonPoussoir()
  {
  }

  void BoutonPoussoir::bouton_init(void)
  {
    pinMode(BP_ENTER,INPUT);
    
    int poten_index;
    switch(PIN_POTENTIOMETRE){
      case A1 : poten_index = 1; break;
      case A2 : poten_index = 2; break;
      case A3 : poten_index = 3; break;
      case A4 : poten_index = 4; break;
      case A5 : poten_index = 5; break;
      default : poten_index = 0; break;
    }
  }

  bool BoutonPoussoir::bouton_if_pushed(int bouton)
  {
    return (digitalRead(bouton)==HIGH)?true:false;
  }

  bool BoutonPoussoir::bouton_if_any_pushed(void)
  {
    // return ( (bouton_if_pushed(BP_ENTER)) | (bouton_if_pushed(BP_LEFT)) | (bouton_if_pushed(BP_RIGHT)) );
    return ((bp.bouton_potentiometre_if_moved()) || (bouton_if_pushed(BP_ENTER)));
  }


  void BoutonPoussoir::bouton_get_potentiometre(void)
  {
    val_poten_actu = analogRead(PIN_POTENTIOMETRE);
  }

  //output : le nombre entier par rapport à la position pointée par le potentiomètre 
  //         0 ~ nb_level-1
  int BoutonPoussoir::bouton_multilevel_potentiometre(int nb_level)
  {
    bp.bouton_update_val_poten_last();
    bouton_get_potentiometre();
    return (int)(((long)val_poten_actu * (long)nb_level)/1024);
  }

  int BoutonPoussoir::bouton_menu_index(int index_max)
  {
    bp.bouton_update_val_poten_last();
    bp.bouton_get_potentiometre();
    return ((val_poten_actu / 60) % (index_max + 1));
  }

  bool BoutonPoussoir::bouton_potentiometre_if_moved(void)
  {
    bp.bouton_get_potentiometre();
    int diff = bp.bouton_potentiometre_get_actu_last_diff();
    if((diff > 10) || (diff < -10)){
      return true;
    }
    else return false;
  }

  int BoutonPoussoir::bouton_potentiometre_get_actu_last_diff(void)
  {
    return (val_poten_actu - val_poten_last);
  } 

  void BoutonPoussoir::bouton_update_val_poten_last(void)
  {
    val_poten_last = val_poten_actu;
  }

  int BoutonPoussoir::bouton_potentiometre_moving_direction(void)
  {    
    bp.bouton_get_potentiometre();
    int diff = bp.bouton_potentiometre_get_actu_last_diff();

    if(diff > 10){
      bp.bouton_update_val_poten_last();
      return POTEN_GO_RIGHT;
    }
    else if(diff < 0){
      bp.bouton_update_val_poten_last();
      return POTEN_GO_LEFT;
    }
    else if(diff == 0)  return POTEN_DONT_MOVE;
  }