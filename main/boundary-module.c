/**
 * This module sets global flags that pertains to boundary detection based on that the flag gets raised upon detection
 * 
*/
#include "Arduino.h"
#include "stdio.h"
#include "main.h"

bool isBoundaryDetected = false;


void setupBoundaryModule(){
  //pin configurations for the three cases. left, right and center.
  pinMode(LEFT_LINE_DETECTION_OUT_PIN,INPUT_PULLUP);
  pinMode(CENTER_LINE_DETECTION_OUT_PIN,INPUT_PULLUP);
  pinMode(RIGHT_LINE_DETECTION_OUT_PIN,INPUT_PULLUP);


// adding the interrupts for the checkBoundary
  attachInterrupt(LEFT_LINE_DETECTION_OUT_PIN, checkBoundary, CHANGE);
  attachInterrupt(CENTER_LINE_DETECTION_OUT_PIN, checkBoundary, CHANGE);
  attachInterrupt(RIGHT_LINE_DETECTION_OUT_PIN, checkBoundary, CHANGE);
}

// enabling the flags if the boundary is detected
bool boundaryDetected(){
    return (digitalRead(LEFT_LINE_DETECTION_OUT_PIN) == LOW || digitalRead(RIGHT_LINE_DETECTION_OUT_PIN) == LOW || digitalRead(CENTER_LINE_DETECTION_OUT_PIN) == LOW);
}

void checkBoundary() {

    // Boundary detection checker
    if(boundaryDetected()){
      isBoundaryDetected = true;
    }
    // condition where the boundary is not visible
    else{
      isBoundaryDetected = false;
    }
}
