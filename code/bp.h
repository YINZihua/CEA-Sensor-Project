#ifndef BP
#define BP

#include "constant.h"
#include "variable.h"
#include "Arduino.h"

class BoutonPoussoir 
{
  public :
    BoutonPoussoir();

    void  bouton_init(void);

    bool  bouton_if_pushed(int bouton);

    bool  bouton_if_any_pushed(void);


    void   bouton_get_potentiometre(void);

    int   bouton_multilevel_potentiometre(int nb_level);

    int   bouton_menu_index(int index_max);

    bool  bouton_potentiometre_if_moved(void);
    
    int   bouton_potentiometre_get_actu_last_diff(void);

    void  bouton_update_val_poten_last(void);
    
    int   bouton_potentiometre_moving_direction(void);

};

extern BoutonPoussoir bp;

#endif //BP