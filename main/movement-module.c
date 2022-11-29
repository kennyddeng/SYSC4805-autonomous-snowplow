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
    pinMode(LEFT_SIDE_ENABLE_PIN, OUTPUT);

    pinMode(RIGHT_SIDE_DIRECTION_PIN, OUTPUT);  
    pinMode(RIGHT_SIDE_ENABLE_PIN, OUTPUT);
}

/**
* Turn the vehicle left
*/
void turnLeft(){
  enableMovement();

  // Set left side backwards
  digitalWrite(LEFT_SIDE_DIRECTION_PIN, LOW);

  // Set left side forwards
  digitalWrite(RIGHT_SIDE_DIRECTION_PIN, HIGH);
}

/**
* Stop the vehicle
*/
void stop(){
    analogWrite(LEFT_SIDE_ENABLE_PIN, LOW);
    analogWrite(RIGHT_SIDE_ENABLE_PIN, LOW);
}

/**
* Enable vehicle movement
*/
void enableMovement(){
  
    analogWrite(RIGHT_SIDE_ENABLE_PIN, MAX_SPEED);
    analogWrite(LEFT_SIDE_ENABLE_PIN, MAX_SPEED);

}

/**
* Turn the vehicle right
*/
void turnRight(){
  enableMovement();
  
  digitalWrite(LEFT_SIDE_DIRECTION_PIN, HIGH);
  digitalWrite(RIGHT_SIDE_DIRECTION_PIN, LOW);
}

/**
* Move the vehicle forwards
*/
void moveForward(){
    enableMovement();

    digitalWrite(LEFT_SIDE_DIRECTION_PIN, HIGH);
    digitalWrite(RIGHT_SIDE_DIRECTION_PIN, HIGH);    
}

/**
* Move the vehicle backwards
*/
void moveBackward(){
    enableMovement();

    digitalWrite(LEFT_SIDE_DIRECTION_PIN, LOW);
    digitalWrite(RIGHT_SIDE_DIRECTION_PIN, LOW);    
}
