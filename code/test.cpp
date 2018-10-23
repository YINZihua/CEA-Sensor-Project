#include "test.h"
#include "Arduino.h"

/***********************************************************************************************
 * 
 * 
 *                      module de test du fonctionnement
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

  Test::Test()
  {

  }

  void Test::signal_test(void)
  {
    digitalWrite(13,HIGH);
    delayMicroseconds(10);
    digitalWrite(13,LOW);
  }
