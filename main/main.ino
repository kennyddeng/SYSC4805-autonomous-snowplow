#include "main.h"

void watchdogSetup(){}

int currentState = NORMAL_STATE;
extern bool isObstacleDetected;
extern bool isBoundaryDetected;

void setup() {
  setupBoundaryModule();
  setupMovementModule();
  setUpObstacleModule();

  Serial.begin(9600);
  watchdogEnable(100);  
}

void loop() {
  // Reset the watchdog timer
  watchdogReset();

  // Update the state
  updateState();

  Serial.println(currentState);

  switch (currentState) {
    case (NORMAL_STATE):
      moveForward();
      break;

    case (OBSTACLE_DETECTED_STATE):
      turnLeft();
      break;


    case (BOUNDARY_DETECTED_STATE):
      turnLeft();
      break;
  }
}


/**
* Update the state based on the obstacle and boundary flags
*/
void updateState() {
  if(isObstacleDetected){
    currentState = OBSTACLE_DETECTED_STATE;
  }else{
    currentState = NORMAL_STATE;
  }
  if (isBoundaryDetected) {
    currentState = BOUNDARY_DETECTED_STATE;
  } else {
    currentState = NORMAL_STATE;
  }
}