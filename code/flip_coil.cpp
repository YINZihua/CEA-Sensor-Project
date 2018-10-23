#include "flip_coil.h"
#include "Arduino.h"
/***********************************************************************************************
 * 
 * 
 *                      module du contrôle de la bobine Flip Coil
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
Pulse::Pulse()
{

}

void Pulse::init_timer(void)
{
  //initialize Timer1

  //disable global interrupts
  cli();

  //initialization of time control registers
  TCCR1A = 0;//set entire TCCR1A register to 0/ TCCR >> Timer/Counter Control Register
  TCCR1B = 0;//same for TCCR1B

  //set compare match register to desired timer count:
  //16 bits register (OCR1AH & OCR1AL)
          //OCR1A = 1;
  OCR1A = 16000;//1kHz
  //turn on CTC mode / WGM[13..10] = 0100 >>  mode CTC;
  //                                          TOP = OCR1A;
  //                                          Update of OCR1x at immediate;
  //                                          TOV1 Flag Set on MAX
  TCCR1B |= (1 << WGM12);
  //set CS10 bit for no prescaler / runs at clock speed
  TCCR1B |= (1 << CS10);
  //enable timer compare interrupt :
  TIMSK1 |= (1 << OCIE1A);

  //enable global interrupts
  sei();

  //initialisation du port de la pulse sortie
  pinMode(SORTI_CONTROL_FLIP_COIL,OUTPUT);
}

void Pulse::init_timer_17kHz(void)
{
  //initialize Timer1

  //disable global interrupts
  cli();

  //initialization of time control registers
  TCCR1A = 0;//set entire TCCR1A register to 0/ TCCR >> Timer/Counter Control Register
  TCCR1B = 0;//same for TCCR1B

  //set compare match register to desired timer count:
  //16 bits register (OCR1AH & OCR1AL)
          //OCR1A = 1;
  OCR1A = 941;
  //turn on CTC mode / WGM[13..10] = 0100 >>  mode CTC;
  //                                          TOP = OCR1A;
  //                                          Update of OCR1x at immediate;
  //                                          TOV1 Flag Set on MAX
  TCCR1B |= (1 << WGM12);
  //set CS10 bit for no prescaler / runs at clock speed
  TCCR1B |= (1 << CS10);
  //enable timer compare interrupt :
  TIMSK1 |= (1 << OCIE1A);

  //enable global interrupts
  sei();

  //initialisation du port de la pulse sortie
  pinMode(SORTI_CONTROL_FLIP_COIL,OUTPUT);
}

  // pour le flip coil de aff755b
ISR(TIMER1_COMPA_vect)
{ 
  PORTB |= 0x02;
  delayMicroseconds(2); // en effet, il fournit une implusion pendant une µsec
  PORTB &= (~(0x02)); 
}
