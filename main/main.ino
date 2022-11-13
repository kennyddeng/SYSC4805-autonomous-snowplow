#include "main.h"

int currentState = NORMAL_STATE;
extern bool isBoundaryDetected;

void setup() {
  setupBoundaryModule();
  setupMovementModule();
  setupObstacleModule();

  Serial.begin(9600);

}

void loop() {


  //Boundary Flag & Obstacle flag set => turn
  // if not, straight
  // checkBoundary();

  updateState();

  Serial.println(currentState);

  switch(currentState) {

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
void updateState(){
  if(isBoundaryDetected){
    currentState = BOUNDARY_DETECTED_STATE;
  }else{
    currentState = NORMAL_STATE;
  }

}
