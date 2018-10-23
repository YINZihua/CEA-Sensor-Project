#include "capteur.h"
#include "Arduino.h"


 
/***********************************************************************************************
 * 
 * 
 *                      module du contrôle du système des capteurs du champ magnétique
 * 
 *          auteur : YIN Zihua
 *          nom du projet : Réalisation de capteur du champ magnétique
 *          NO. de version du programme: 
 *          date du release : 
 * 
 *          description de fonctionnement :
 *                  1. pour l'enregistrement du ratio de conversion de capteur, on apprécie l'unité [µV/100µT]
 *                     à destionation d'avoir la meilleure précision du résultat
 * 
 * 
 * ********************************************************************************************/

/****************************************************************************
 * 
 * 
 * code pour capteur
 * 
 * 
 * *************************************************************************/

CAPTEUR::CAPTEUR()
{

}

void CAPTEUR::cap_coef_uT_V_setup(void)
{
    int channel;
    for(channel = 0; channel < acquisition_nb_channel; channel++){
        cap.cap_coef_uT_V_setup_single_channel(channel);
    }
}

void CAPTEUR::cap_coef_uT_V_setup_single_channel(int channel)
{
    switch(acquisition_channel_capteur[channel]){
        case CAP_AFF755B : {
            acquisition_channel_capteur_coef_uV_100uT[channel] = cap.cap_coef_uV_uT_setup_cap_aff755b(channel); 
            break;
        }
        case CAP_STEFAN_MAYER : {
            acquisition_channel_capteur_coef_uV_100uT[channel] = cap.cap_coef_uT_V_setup_cap_stefan_mayer();
            break;
        }
        default : break;
    }
}



/****************************************************************************
 * 
 * 
 * code pour capteur  AFF755B
 * 
 * 
 * *************************************************************************/ 
    // en utilisant cette fonction, on doit fournir au capteur un courant d'ordre 200mA, 0mA, -200mA, 
    // pour les différents points de mesures. 
    int CAPTEUR::cap_coef_uV_uT_setup_cap_aff755b(int channel)
    {
        // 0 : déclaration et initialisation des variables pour la mesure de coefficient
            // 0.1 : l'indice du point mesuré 
                // point_mesure = 0 >> valid
                //                1 >> max
                //                2 >> min
                //                3 >> offset
                int point_mesure = 0;
            // 0.2 : le maxium de l'indice des points mesurés
                #define point_index_max 3
            // 0.3 : la transition du point mesuré
                int operation = OP_NO_OPERATION;
            // 0.4 : validation des points
                int valid_mesure = 0;

            // 0.5 : coef_uV_100uT représente la tension sortie en uV si on effctue un champ magnétique d'ordre 100 uTesla
                signed long coef_uV_100uT = 0;
            // 0.6 : offset de la caracteristique de sortie en fonction du champ effectué [uV]
                signed long offset = 0;            
            // 0.7 : valeurs mesurées intermédiaires [uV]
                signed long max_mes = 0;
                signed long min_mes = 0;
                signed long off_mes = 0;

        // 1 : fonction de la mesure
            while(bp.bouton_if_pushed(BP_ENTER));
            while(valid_mesure == 0){
                // 1.1 : transition des points mesurés
                    if(bp.bouton_if_pushed(BP_ENTER)){
                        switch(point_mesure){
                            case 0:{
                                valid_mesure = 1;
                                break;
                            }
                            case 1:{
                                max_mes = i2c.i2c_acquisition(channel, ACQUISITION_UNITE_UV);
                                break;
                            }
                            case 2:{
                                min_mes = i2c.i2c_acquisition(channel, ACQUISITION_UNITE_UV);
                                break;
                            }
                            case 3:{
                                off_mes = i2c.i2c_acquisition(channel, ACQUISITION_UNITE_UV);
                                break;
                            }
                            default : break;
                        }
                    }

                // 1.2 : illustration de la valeur mesurée
                    lcd.clear();
                    switch(point_mesure){
                        case 0 :{
                            affi.affi_carac("VALID",0,0);
                            break;
                        }
                        case 1 :{
                            affi.affi_carac("MAX=",0,0);
                            lcd.print(max_mes);
                            break;
                        }
                        case 2 :{
                            affi.affi_carac("MIN=",0,0);
                            lcd.print(min_mes);
                            break;
                        }
                        case 3 :{
                            affi.affi_carac("OFF=",0,0);
                            lcd.print(off_mes);
                            break;
                        }
                        default : break;
                    }
            }

        // 2 : calcul final du coefficient
            signed long tab_uT[3] = {87800, -87800, 0}; // doit avoir une fonction pour calibrer l'intensité du champ généré ???
            signed long tab_uV[3] = {max_mes, min_mes, off_mes};
            maths.regression_lineaire_3pts(&tab_uT[0], &tab_uV[3], &coef_uV_100uT, &offset);
            acquisition_channel_capteur_coef_uV_100uT[channel] = coef_uV_100uT;
            acquisition_channel_capteur_offset[channel] = offset;

        return 0;
    }
    


/****************************************************************************
 * 
 * 
 * code pour capteur Stefan Mayer
 * 
 * 
 * *************************************************************************/
    int CAPTEUR::cap_coef_uT_V_setup_cap_stefan_mayer(void)
    {
        return 50;
    }




/****************************************************************************
 * 
 * 
 * code pour la conversion de data
 * 
 * 
 * *************************************************************************/
    // cette fonction rentre la valeur de l'intensité du champ magnétique en [100nT]
        int CAPTEUR::cap_100uV_to_100nT(int channel, int val_100uV)
        {
            return ((val_100uV * acquisition_channel_capteur_coef_10nT_100uV[channel])/10);
        }

