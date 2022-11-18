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
* Enable vehicle movement
*/
void enableMovement(){
    digitalWrite(LEFT_SIDE_ENABLE_PIN, HIGH);
    digitalWrite(RIGHT_SIDE_ENABLE_PIN, HIGH);
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
    digitalWrite(LEFT_SIDE_ENABLE_PIN, LOW);
    digitalWrite(RIGHT_SIDE_ENABLE_PIN, LOW);
}




/**
* Turn the vehicle right
*/
void turnRight(){
  enableMovement();
  
  // Set left side forward
  digitalWrite(LEFT_SIDE_DIRECTION_PIN, HIGH);

  // Set left side backwards
  digitalWrite(RIGHT_SIDE_DIRECTION_PIN, LOW);
}

/**
* Move the vehicle forward
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
