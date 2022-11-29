#include "main.h"

void watchdogSetup(){}

int currentState = NORMAL_STATE;
// extern bool isCloseObstacleDetected;
// extern bool isFarObstacleDetected;
// extern bool isBoundaryDetected;
// extern bool isVMA330OnlyDetectedObstacle;


void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("Serial Monitor initialized...");


  setUpObstacleModule();
  setupBoundaryModule();
  setupMovementModule();

    Serial.println("SET UP!!!!!!!!!!!!");

  watchdogEnable(10000);  
}

void loop() {    

    // Reset the watchdog timer
    watchdogReset();


    checkObstacle();
    checkBoundary();

  //   // Update the state
    updateState();

  Serial.println(currentState);



  switch (currentState) {
    case (NORMAL_STATE):
      moveForward();
      break;

    case (OBSTACLE_DETECTION_RESET_VEHICLE_POSISTION_STATE):
      moveBackward();
      delay(1000);
      turnLeft();
      delay(2250);

    break;

    case (OBSTACLE_CLOSE_DETECTED_STATE):
      moveBackward();
      break;

    case (OBSTACLE_FAR_DETECTED_STATE):
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
  if(didAnalogDistanceSensorOnlyDetectedObstacle || didUltrasonicSensorOnlyDetectedObstacle){    
    currentState = OBSTACLE_DETECTION_RESET_VEHICLE_POSISTION_STATE;

  } else if(isCloseObstacleDetected){
    currentState = OBSTACLE_CLOSE_DETECTED_STATE;

  }else if(isFarObstacleDetected){
    currentState = OBSTACLE_FAR_DETECTED_STATE;

  }
  else if (isBoundaryDetected) {
    currentState = BOUNDARY_DETECTED_STATE;

  } 
  else{
    currentState = NORMAL_STATE;
  }
}
