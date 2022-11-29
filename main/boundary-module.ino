/**
 * This module sets global flags that pertains to boundary detection
 * 
*/
#include "Arduino.h"
#include "stdio.h"
#include "main.h"

bool isBoundaryDetected = false;

/**
* Setup the boundary detection module
*/
void setupBoundaryModule(){
  pinMode(LEFT_LINE_DETECTION_OUT_PIN,INPUT);
  pinMode(CENTER_LINE_DETECTION_OUT_PIN,INPUT);
  pinMode(RIGHT_LINE_DETECTION_OUT_PIN,INPUT);
}

/**
* Returns true if the boundary is true
*/
bool boundaryDetected(){
      Serial.println( String(analogRead(LEFT_LINE_DETECTION_OUT_PIN))+ " | " +String(analogRead(RIGHT_LINE_DETECTION_OUT_PIN)) + " | "+ String(analogRead(CENTER_LINE_DETECTION_OUT_PIN)));

    // Check if any of the line detection pins are greater than the minimum detected analog value
    return (analogRead(LEFT_LINE_DETECTION_OUT_PIN) > DETECTED_MINIMUM_BOUNDARY_ANALOG_VALUE ||
              analogRead(RIGHT_LINE_DETECTION_OUT_PIN) > DETECTED_MINIMUM_BOUNDARY_ANALOG_VALUE || 
              analogRead(CENTER_LINE_DETECTION_OUT_PIN) > DETECTED_MINIMUM_BOUNDARY_ANALOG_VALUE);
}

/**
* Update associated flags based on boundary detection
*/
void checkBoundary() {
    if(boundaryDetected()){
      isBoundaryDetected = true;
    }
    else{
      isBoundaryDetected = false;
    }
}
