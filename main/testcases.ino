#include "main.h"

/**
* Run the testcases
*/
void runTestcases(){
  testMoveForward();
  testMoveBackwardsAndTurnLeft();
}

void testMoveForward(){
  //Given
  moveForward();

  //Test 
  if(digitalRead(LEFT_SIDE_DIRECTION_PIN) == HIGH &&
  digitalRead(LEFT_SIDE_DIRECTION_PIN) == HIGH){
    Serial.println("The testMoveForward testcase passed");
  }else{
    Serial.println("The testMoveForward testcase FAILED");
  }
}

/*
* Test the moveBackwardsAndTurnLeft function sets the correct pin
*/
void testMoveBackwardsAndTurnLeft(){
  //Given 
  moveBackwardsAndTurnLeft();

  //Test
  if( digitalRead(LEFT_SIDE_DIRECTION_PIN) == LOW &&  digitalRead(RIGHT_SIDE_DIRECTION_PIN) == HIGH
      &&  analogRead(RIGHT_SIDE_ENABLE_PIN) ==  RIGHT_SIDE_BACKWARDS_TURN_SPEED
      && analogRead(LEFT_SIDE_ENABLE_PIN) ==  LEFT_SIDE_BACKWARDS_TURN_SPEED ){

      Serial.println("The testMoveBackwardsAndTurnLeft testcase passed");
  }else{
      Serial.println("The testMoveBackwardsAndTurnLeft testcase FAILED");

  }
}

