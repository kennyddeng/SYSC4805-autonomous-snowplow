/**
 * This module sets global flags that pertains to boundary detection
 * 
*/
#include "Arduino.h"
#include "main.h"



int isObstacleDetected = 0;

void setupBoundaryModule(){
  pinMode(5,OUTPUT);

  pinMode(LEFT_LINE_DETECTION_OUT_PIN,INPUT);
  pinMode(CENTER_LINE_DETECTION_OUT_PIN,INPUT);
  pinMode(RIGHT_LINE_DETECTION_OUT_PIN,INPUT);

  Serial.begin(9600);
}



void checkBoundary() {
    // Boundary detection
    if(digitalRead(6) == LOW){
      digitalWrite(5,HIGH);
      delay(15);
      isObstacleDetected = TRUE;
    }
    else{
      digitalWrite(5,LOW);
      isObstacleDetected = FALSE;
      delay(15);
    }
}
}

