/**
 * This module sets global flags that pertains to boundary detection.
 * This module uses the line follower to achieve its goals.
 * 
*/
#include "Arduino.h"
#include "stdio.h"
#include "main.h"

// The boundary detection flag that indicates whether an boundary has been detected.
// This variable is used to update the system's state and behaviour
bool isBoundaryDetected = false;

/**
* This function sets up the boundary detection module
*/
void setupBoundaryModule(){
  pinMode(LEFT_LINE_DETECTION_OUT_PIN,INPUT);
  pinMode(CENTER_LINE_DETECTION_OUT_PIN,INPUT);
  pinMode(RIGHT_LINE_DETECTION_OUT_PIN,INPUT);
}

/**
* This function returns true if the boundary is detected
*/
bool boundaryDetected(){
    Serial.println( "Boundary Readings: " + String(analogRead(LEFT_LINE_DETECTION_OUT_PIN))+ " | " +String(analogRead(RIGHT_LINE_DETECTION_OUT_PIN)) + " | "+ String(analogRead(CENTER_LINE_DETECTION_OUT_PIN)));

    // Check if any of the line detection pins are greater than the minimum detected analog value,
    // indicating that a line has been detected.
    return (analogRead(LEFT_LINE_DETECTION_OUT_PIN) > DETECTED_MINIMUM_BOUNDARY_ANALOG_VALUE ||
              analogRead(RIGHT_LINE_DETECTION_OUT_PIN) > DETECTED_MINIMUM_BOUNDARY_ANALOG_VALUE || 
              analogRead(CENTER_LINE_DETECTION_OUT_PIN) > DETECTED_MINIMUM_BOUNDARY_ANALOG_VALUE);
}

/**
* Update associated flags based on boundary detection
*/
void checkBoundary() {
    isBoundaryDetected = boundaryDetected();
}
