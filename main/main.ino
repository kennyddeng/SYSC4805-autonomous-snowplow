#include "main.h"


void watchdogSetup(){}

int currentState = NORMAL_STATE;
extern bool isBoundaryDetected;

// void watchdogSetup(){

// }

void setup() {



  setupBoundaryModule();
  setupMovementModule();
  setupObstacleModule();

  Serial.begin(9600);

	// WDT_Disable (WDT);

  watchdogEnable(5);  

}

void loop() {


  watchdogReset();


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
  if (isBoundaryDetected) {
    currentState = BOUNDARY_DETECTED_STATE;
  } else {
    currentState = NORMAL_STATE;
  }
}