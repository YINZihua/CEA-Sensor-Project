#include "maths.h"
#include "Arduino.h"

/***********************************************************************************************
 * 
 * 
 *                      module de l'algorithme des calculs mathématiques
 * 
 *          auteur : YIN Zihua
 *          nom du projet : Réalisation de capteur du champ magnétique
 *          NO. de version du programme: 
 *          date du release : 
 * 
 *          description de fonctionnement :
 *            1. conversion du format de données
 *            2. regression linéaire d'ordre 1
 * 
 * 
 * ********************************************************************************************/

  Maths::Maths()
  {

  }
  
  int Maths::incrementation_modulo(int number, int modulo)
  {
    return (number == modulo - 1)?(0):(number + 1);
  }

  int Maths::decrementation_modulo(int number, int modulo)
  {
    return (number == 0)?(modulo - 1):(number - 1);
  }


  void Maths::regression_lineaire_3pts(long* x, long* y, long* pente, long* offset)
  {
    //calcul des moyens des points dont on cherche la regression
      signed long x_average = (*x + *(x+1) + *(x+2))/3;
      signed long y_average = (*y + *(y+1) + *(y+2))/3; 

    //calcul de la pente de régression linéaire d'ordre 1
      *pente = (*x - x_average) * (*y - y_average) + (*(x+1) - x_average) * (*(y+1) - y_average) + (*(x+2) - x_average) * (*(y+2) - y_average);
      *pente /=(*x - x_average) * (*x - x_average) + (*(x+1) - x_average) * (*(x+1) - x_average) + (*(x+2) - x_average) * (*(x+2) - x_average);

    //l'offset de la fonction de regression linéaire d'ordre 1  
      *offset = *(x+1); 
  }