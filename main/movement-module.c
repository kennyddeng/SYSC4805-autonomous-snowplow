/**
 * This module provides functionality for vehicle movement
 * 
*/

#include "Arduino.h"
#include "main.h"

/**
*  Set up the movement module
*/
void setupMovementModule(){
    // configure output direction pin :
    pinMode(LEFT_SIDE_DIRECTION_PIN, OUTPUT);
    pinMode(RIGHT_SIDE_DIRECTION_PIN, OUTPUT);  

    setUpLeftSidePWM();
    setUpRightSidePWM();
}

/**
* Set up the left side PWM
* 
* The input pin is C3, physical pin 35,
*/
void setUpLeftSidePWM(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID36; // Enable Clock to PWM module
    PIOC->PIO_ABSR |= PIO_PC3B_PWMH0; // Assign C3 to PWM module (Periph_B)
    PIOC->PIO_PDR |= PIO_PDR_P3; // Release C3 from the PIO module
    REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84);//Set PWM clock 1MHz (Mck/84)
    PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPRE_CLKA // Set the clock source as CLKA
    | PWM_CMR_CPOL; //Set output polarity be high.

    // The vehicle starts with 0 duty cycle: should not move
    setLeftSidePWNDuty(0);
}


/**
* Set up the right side PWM
* 
* The input pin is B25, which is Arduino Pin 2
*/
void setUpRightSidePWM(){
    PMC->PMC_PCER0 |= PMC_PCER0_PID27;//TC0 power ON - Timer Counter 0 channel 0
    PIOB->PIO_PDR |= PIO_PDR_P25; // The pin is no more driven by GPIO
    PIOB->PIO_ABSR |= PIO_PB25B_TIOA0;// B Assign B25 to alternative periph_B (TIOA0):
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 //MCK/2 = 42 MHz,
    | TC_CMR_WAVE //Waveform mode
    | TC_CMR_WAVSEL_UP_RC //Count UP mode till RC
    | TC_CMR_ACPA_CLEAR //Clear TIOA0 on RA compare match
    | TC_CMR_ACPC_SET; // Set TIOA0 on RC compare match
    
    // The vehicle starts with 0 duty cycle: should not move
    setRightSidePWNDuty(0);
}


/**
* Set the right side PWN frequency
*/
void setLeftSidePWNDuty(float duty){
    float temp_period  = 1000000.0/PWM_FREQUENCY;

    PWM->PWM_CH_NUM[0].PWM_CPRD = temp_period-1; //Set PWM freq 1MHz/(60000) = 66.667Hz
    PWM->PWM_CH_NUM[0].PWM_CDTY = (temp_period * duty)-1; // Set PWM duty cycle
    PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel
}

/**
* Set the right side PWN frequency
*/
void setRightSidePWNDuty(float duty){
    float temp_period  = 1000000.0/PWM_FREQUENCY;

    TC0->TC_CHANNEL[0].TC_RC =  temp_period-1; //Set the frequency to 66.667Hz (Period 60 ms)
    TC0->TC_CHANNEL[0].TC_RA = (temp_period * duty)-1;; //Set the duty cycle (Pulse of 10 usec)
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG //Software trigger TC0 channel 0 counter
    | TC_CCR_CLKEN;//and enable
}


/**
* Turn the vehicle left
*/
void turnLeft(float turnAngle ){
  setLeftSidePWNDuty(0.5);
  setRightSidePWNDuty(1);
}

/**
* Turn the vehicle right
*/
void turnRight(float turnAngle ){
  setLeftSidePWNDuty(1);
  setRightSidePWNDuty(0.5);
}

/**
* Move the vehicle forward
*/
void moveForward(float turnAngle ){
    digitalWrite(LEFT_SIDE_DIRECTION_PIN, HIGH);
    digitalWrite(RIGHT_SIDE_DIRECTION_PIN, HIGH);

    setLeftSidePWNDuty(1);
    setRightSidePWNDuty(1);    
}

/**
* Move the vehicle backwards
*/
void moveBackward(float turnAngle ){
    digitalWrite(LEFT_SIDE_DIRECTION_PIN, LOW);
    digitalWrite(RIGHT_SIDE_DIRECTION_PIN, LOW);

    setLeftSidePWNDuty(1);
    setRightSidePWNDuty(1);
}
