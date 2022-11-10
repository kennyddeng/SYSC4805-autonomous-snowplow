#include "main.h"

int currentState = NORMAL_STATE;

void setup() {
  setupBoundaryModule();
  setupMovementModule();
  setupObstacleModule();
}

void loop() {

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