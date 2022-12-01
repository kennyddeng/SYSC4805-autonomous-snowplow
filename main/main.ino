#include "main.h"

// The initial state of the system
int currentState = NORMAL_STATE;

/**
* This function sets up the system
*/
void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("Serial Monitor initialized...");

  //Set the supporting modules
  setUpObstacleModule();
  setupBoundaryModule();
  setupMovementModule();

  watchdogEnable(100);//Enable the watchdog time for 100ms  
}

/*
* This function controls the system's behavior
*/
void loop() {    
  watchdogReset();//Reset the watchdog timer

  checkObstacle();//Check for obstacle, updating the obstacle system flags
  checkBoundary();//Check for boundaries, updating the boundary sytem flags

  updateState();//Based on the updated system flags, update the state

  Serial.println("Current State: " + String(currentState));
  
  // Update the vehicle behaviour based on the current state
  switch (currentState) {
      case (NORMAL_STATE):
        moveForward();
        break;

      case (OBSTACLE_CLOSE_DETECTED_STATE):
        moveBackwardsAndTurnLeft();
        break;

      case (OBSTACLE_FAR_DETECTED_STATE):
        turnLeft();
        break;

      case (BOUNDARY_DETECTED_STATE):
        moveBackwardsAndTurnLeft();
        break;
  }
  
}


/**
* Update the state based on the obstacle and boundary flags
*/
void updateState() {
  if(isCloseObstacleDetected){
    currentState = OBSTACLE_CLOSE_DETECTED_STATE;    
  }
  
  else if(isFarObstacleDetected){
    currentState = OBSTACLE_FAR_DETECTED_STATE;
  }

  else if (isBoundaryDetected) {
    currentState = BOUNDARY_DETECTED_STATE;
  } 

  else{
    currentState = NORMAL_STATE;
  }
}
