#include "main.h";

void setup() {
  setupBoundaryModule();
  setupMovementModule();
  setupObstacleModule();
}

void loop() {
    // Move forward for 5 seconds
    moveForward(0.0);
    delay(5000);
    
    //Move backwards for 5 seconds
    moveBackward(0.0); 
    delay(5000);

    //turn right for 5 seconds
    turnRight(0.0); 
    delay(5000);

    //turn left for 5 seconds
    turnLeft(0.0); 
    delay(5000);
}