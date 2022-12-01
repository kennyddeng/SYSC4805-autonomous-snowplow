/**
 * This module provides functionality for vehicle movement
 * 
*/

#include "Arduino.h"
#include "main.h"

/**
*  This function sets up the movement module
*/
void setupMovementModule(){
    // configure output direction pin :
    pinMode(LEFT_SIDE_DIRECTION_PIN, OUTPUT);
    pinMode(LEFT_SIDE_ENABLE_PIN, OUTPUT);

    pinMode(RIGHT_SIDE_DIRECTION_PIN, OUTPUT);  
    pinMode(RIGHT_SIDE_ENABLE_PIN, OUTPUT);
}

/**
* This function turns the vehicle left
*/
void turnLeft(){
  enableMovement();

  // Set left side backwards
  digitalWrite(LEFT_SIDE_DIRECTION_PIN, LOW);

  // Set left side forwards
  digitalWrite(RIGHT_SIDE_DIRECTION_PIN, HIGH);
}

/**
* This function stops the vehicle
*/
void stop(){
    analogWrite(LEFT_SIDE_ENABLE_PIN, LOW);
    analogWrite(RIGHT_SIDE_ENABLE_PIN, LOW);
}

/**
* This function enable normal vehicle movement
*/
void enableMovement(){
    analogWrite(RIGHT_SIDE_ENABLE_PIN, NORMAL_MAX_SPEED);
    analogWrite(LEFT_SIDE_ENABLE_PIN, NORMAL_MAX_SPEED);
}

/**
* This function turns the vehicle right
*/
void turnRight(){
  enableMovement();
  
  digitalWrite(LEFT_SIDE_DIRECTION_PIN, HIGH);
  digitalWrite(RIGHT_SIDE_DIRECTION_PIN, LOW);
}

/**
* This function moves the vehicle forwards
*/
void moveForward(){
    enableMovement();

    digitalWrite(LEFT_SIDE_DIRECTION_PIN, HIGH);
    digitalWrite(RIGHT_SIDE_DIRECTION_PIN, HIGH);    
}

/**
* This function moves the vehicle backwards
*/
void moveBackward(){
    enableMovement();

    digitalWrite(LEFT_SIDE_DIRECTION_PIN, LOW);
    digitalWrite(RIGHT_SIDE_DIRECTION_PIN, LOW);    
}

/**
* This function moves the vehicle backwards while turning left
*/
void moveBackwardsAndTurnLeft(){
  // Update the direction for each side via direction pin
  digitalWrite(LEFT_SIDE_DIRECTION_PIN, LOW);
  digitalWrite(RIGHT_SIDE_DIRECTION_PIN, HIGH);

  //Update the speed for each side via enable pins
  analogWrite(RIGHT_SIDE_ENABLE_PIN, RIGHT_SIDE_BACKWARDS_TURN_SPEED);
  analogWrite(LEFT_SIDE_ENABLE_PIN, LEFT_SIDE_BACKWARDS_TURN_SPEED);
}
