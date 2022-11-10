/**
 * This module sets global flags that pertains to boundary detection
 * 
*/
#include "Arduino.h"
#include "main.h"

void setupBoundaryModule(){
}
void setup() {
  // put your setup code here, to run once:

// create a flag so everytime a boundary is detected the flag goes 1, if not it is 0

// pins configuration
// motor configuration

  pinMode(5,OUTPUT);
  pinMode(6,INPUT);
  Serial.begin(9600);

//int val = 0;
//int val2 = 0;
}


void loop() {
  // put your main code here, to run repeatedly:
  //val = digitalRead(5); // IR 1 sensor output pin connected  
 // va12 = digitalRead(6); // IR 2 sensor output pin connected  
 // bool detect(int pin){
  if(digitalRead(6) == LOW){
    digitalWrite(5,HIGH);
    delay(15);}
  else{
    digitalWrite(5,LOW);
    delay(15);
}

  
  }

/*


void forward(){


}

void backward(){

  }
void left(){
  
  
  }  
  

void right(){
  
  
  }  

void stop(){
  
  
  
  }
}
*/

}
