/**
 * This module sets global flags that pertains to boundary detection
 * 
*/
#include "Arduino.h"
#include "main.h"



int isObstacleDetected = 0;

void setupBoundaryModule(){
  // pinMode(5,OUTPUT);

  pinMode(LEFT_LINE_DETECTION_OUT_PIN,INPUT);
  pinMode(CENTER_LINE_DETECTION_OUT_PIN,INPUT);
  pinMode(RIGHT_LINE_DETECTION_OUT_PIN,INPUT);

  Serial.begin(9600);
}



void checkBoundary() {
    // Boundary detection
    bool isBoundaryDetected(){
    if(digitalRead(LEFT_LINE_DETECTION_OUT_PIN) == LOW){
      isBoundaryDetected = TRUE;
    }
    else{
      isBoundaryDetected = false;
      delay(15);
    }
}
}

bool isBoundaryDetected(){
    return (digitalRead(LEFT_LINE_DETECTION_OUT_PIN) == LOW && RIGHT_LINE_DETECTION_OUT_PIN) == LOW && CENTER_LINE_DETECTION_OUT_PIN) == LOW)
}

