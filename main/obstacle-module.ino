/**
 * This module sets global flags that pertains to obstactle detection.
 * This module configures and uses ultrasonic and time-of-flight sensors
 * to achieve its goal.
 * 
*/
#include "Arduino.h"
#include "stdio.h"
#include "main.h"
#include <EZDist.h>
#include "Adafruit_VL53L1X.h"

bool isCloseObstacleDetected = false;//The obstacle detection flag that indicates that the snowplow is close to an obstacle Obstacle detection flags
bool isFarObstacleDetected = false;//The obstacle detection flag that indicates that an obstacle is within the close and far distance thresholds.

EZDist LeftUltraSonic(LEFT_ULTRA_SONIC_TRIGGER_PIN, LEFT_ULTRA_SONIC_ECHO_PIN);//The left ultrasonic distance senso
EZDist RightUltraSonic(RIGHT_ULTRA_SONIC_TRIGGER_PIN, RIGHT_ULTRA_SONIC_ECHO_PIN);//The right ultrasonic distance sensor

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(TIME_OF_FLIGHT_XSHUT_PIN, TIME_OF_FLIGHT_IRQ_PIN);//The time-of-flight distance sensor

/**
* This function configures hardware components that enable the obstacle detection module.
*/
void setUpObstacleModule(){
  //Set up time-of-flight distance sensor
  Wire.begin();
  Serial.println("Wire.begin is  completing!");
  Serial.println(! vl53.begin(0x29, &Wire));
  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(vl53.vl_status);    
    while (1)       delay(10);
  }
  Serial.println(F("VL53L1X sensor OK!"));

  Serial.print(F("Sensor ID: 0x"));
  Serial.println(vl53.sensorID(), HEX);

  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(vl53.getTimingBudget());
}

/**
* This function returns true if the given distance is within the specified range
*/
bool isDistanceInRange(int minDistance, int maxDistance, int givenDistance){  
  return givenDistance>minDistance && givenDistance<maxDistance;
}

/**
* This function updates obstacle flags based on the obstacle-detection inputs
*/
void checkObstacle(){  
    //Gather distances from the ultrasonic sensors and time-of-flight sensor
    int leftDistanceInCm = LeftUltraSonic.cm(); // From the left ultrasonic sensor
    int rightDistanceInCm = RightUltraSonic.cm();// From the right ultrasonic sensor
    int centerDistanceInCm = vl53.distance() / 10 ;// From the time-of-flight sensor (converting from mm to cm)
    vl53.clearInterrupt(); //Clear the time-of-flight interrupt

    printf(" Left Distance: \r %d cm; Center Distance: \r %d cm; Right Distance: \r %d cm \n", leftDistanceInCm, centerDistanceInCm, rightDistanceInCm);

    // Check if the snowplow is close to an obstacle
    if( isDistanceInRange(MIN_ACCEPTABLE_DISTANCE,OBSTACLE_CLOSE_DISTANCE_TRIGGER,centerDistanceInCm)||
        isDistanceInRange(MIN_ACCEPTABLE_DISTANCE,OBSTACLE_CLOSE_DISTANCE_TRIGGER,leftDistanceInCm) ||
        isDistanceInRange(MIN_ACCEPTABLE_DISTANCE,OBSTACLE_CLOSE_DISTANCE_TRIGGER,rightDistanceInCm)
      ){
        isCloseObstacleDetected = true;
        isFarObstacleDetected = false;
      }
    
      // Check if the an obstacle is within the close and far distance thresholds
      else if (isDistanceInRange(OBSTACLE_CLOSE_DISTANCE_TRIGGER,OBSTACLE_FAR_DISTANCE_TRIGGER,centerDistanceInCm) ||
                isDistanceInRange(OBSTACLE_CLOSE_DISTANCE_TRIGGER,OBSTACLE_FAR_DISTANCE_TRIGGER,leftDistanceInCm) ||
                isDistanceInRange(OBSTACLE_CLOSE_DISTANCE_TRIGGER,OBSTACLE_FAR_DISTANCE_TRIGGER,rightDistanceInCm)
      ){
            isFarObstacleDetected = true;
            isCloseObstacleDetected = false;
      }
      
      else{
        isCloseObstacleDetected = false;
        isFarObstacleDetected = false;
      }
 }
