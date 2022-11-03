/**
 * This modules provides functionality for vehicle movement
 * 
*/

int frontRightWheelPin = 0;
int topLeftWheelPin = 0;
int tRightWheelPin = 0;
int topRightWheelPin = 0;

int DUTY_CYLE = 1;

void setUpMovementModule(){
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

    float freq = 1000;
    float temp_period  = 1000000.0/freq;
    // float duty=0.4;

    PWM->PWM_CH_NUM[0].PWM_CPRD = temp_period-1; //Set PWM freq 1MHz/(60000) = 66.667Hz
    PWM->PWM_CH_NUM[0].PWM_CDTY = (temp_period* DUTY_CYLE)-1; // Set PWM duty cycle
    PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel
}


/**
 * Set up the right side PWM
 * 
 * The input pin is PC3, physical pin 60,
*/
void setUpRightSidePWM(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID36; // Enable Clock to PWM module
    PIOC->PIO_ABSR |= PIO_PC3B_PWMH0; // Assign C3 to PWM module (Periph_B)
    PIOC->PIO_PDR |= PIO_PDR_P3; // Release C3 from the PIO module
    REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84);//Set PWM clock 1MHz (Mck/84)
    PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPRE_CLKA // Set the clock source as CLKA
    | PWM_CMR_CPOL; //Set output polarity be high.

    setRightSidePWNFequency(1000);
}


/**
 * Set the right side PWN frequency
*/
void setLeftSidePWNFequency(float frequency, float duty){
    float temp_period  = 1000000.0/frequency;

    PWM->PWM_CH_NUM[0].PWM_CPRD = temp_period-1; //Set PWM freq 1MHz/(60000) = 66.667Hz
    PWM->PWM_CH_NUM[0].PWM_CDTY = (temp_period * duty)-1; // Set PWM duty cycle
    PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel
}

/**
 * Set the right side PWN frequency
*/
void setRightSidePWNFequency(float frequency, float duty){
    float temp_period  = 1000000.0/frequency;

    PWM->PWM_CH_NUM[0].PWM_CPRD = temp_period-1; //Set PWM freq 1MHz/(60000) = 66.667Hz
    PWM->PWM_CH_NUM[0].PWM_CDTY = (temp_period * duty)-1; // Set PWM duty cycle
    PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel
}




void turnLeft(float turnAngle ){
}

void turnRight(float turnAngle ){
    
}

void moveForward(float turnAngle ){
    
}

void moveBackward(float turnAngle ){
    
}