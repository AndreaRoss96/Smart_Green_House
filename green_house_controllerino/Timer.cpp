#include "Timer.h"
#include "Arduino.h"

/*Class managing Timer0*/

volatile bool timerFlag;

ISR(TIMER0_COMPA_vect){
  timerFlag = true;
}

Timer::Timer(){
  timerFlag = false;
}

/* period in ms */
void Timer::setupPeriod(int period){
  //TODO
  // disabling interrupt
  cli();

  TCCR0A = 0; // set entire TCCR1A register to 0
  TCCR0B = 0; // same for TCCR1B
  TCNT0  = 0; //initialize counter value to 0

  /*
   * set compare match register
   *
   * OCR1A = (16*2^20) / (100*PRESCALER) - 1 (must be < 65536)
   *
   * assuming a prescaler = 1024 => OCR1A = (16*2^10)* period/1000 (being in ms)
   */
  OCR0A = 16*1024*period;
  // turn on CTC mode
  TCCR0B |= (1 << WGM01);
  // Set CS11 for 8 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  // enabling interrupt
  sei();

}

void Timer::waitForNextTick(){
  /* wait for timer signal */
  while (!timerFlag){}
  timerFlag = false;

}

/**********************************************
la classe utilizza le flag del timer 0 in modo da non interferire con il timer 2 del
servomotore e con il timer la altsoftware serial
***********************************************/
