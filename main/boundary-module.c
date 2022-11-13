/**
 * This module sets global flags that pertains to boundary detection
 * 
*/
#include "Arduino.h"
#include "stdio.h"
#include "main.h"

bool isBoundaryDetected = false;

void setupBoundaryModule(){
  pinMode(LEFT_LINE_DETECTION_OUT_PIN,INPUT_PULLUP);
  pinMode(CENTER_LINE_DETECTION_OUT_PIN,INPUT_PULLUP);
  pinMode(RIGHT_LINE_DETECTION_OUT_PIN,INPUT_PULLUP);

  attachInterrupt(LEFT_LINE_DETECTION_OUT_PIN, checkBoundary, CHANGE);
  attachInterrupt(CENTER_LINE_DETECTION_OUT_PIN, checkBoundary, CHANGE);
  attachInterrupt(RIGHT_LINE_DETECTION_OUT_PIN, checkBoundary, CHANGE);
}

bool boundaryDetected(){
    return (digitalRead(LEFT_LINE_DETECTION_OUT_PIN) == LOW || digitalRead(RIGHT_LINE_DETECTION_OUT_PIN) == LOW || digitalRead(CENTER_LINE_DETECTION_OUT_PIN) == LOW);
}

void checkBoundary() {

    // Boundary detection
    if(boundaryDetected()){
      isBoundaryDetected = true;
    }
    else{
      isBoundaryDetected = false;
    }
}
