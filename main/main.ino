#include "main.h"

int currentState = NORMAL_STATE;

void setup() {
  setupBoundaryModule();
  setupMovementModule();
  setupObstacleModule();
}

void loop() {


  //Boundary Flag & Obstacle flag set => turn
  // if not, straight
  if( checkBoundary()){
    currentState = BOUNDARY_DETECTED_STATE;
  }else{
    currentState = NORMAL_STATE
  }



  // checkObstacle();

  switch(currentState) {

      case (NORMAL_STATE):{
        moveForward();
      }

      case (OBSTACLE_DETECTED_STATE):{
        turnLeft();
      }

      case (BOUNDARY_DETECTED_STATE):{
        turnLeft();
      }
  }

}