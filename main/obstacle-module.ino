/**
 * This module sets global flags that pertains to obstactle detection
 * 
*/
#include "Arduino.h"
#include "stdio.h"
#include "main.h"
#include <EZDist.h>
#include "Adafruit_VL53L1X.h"


// Our system has two modes for obstacle detection because the time-of-flight sensor occasionally fails to initalize.
// The two modes are TIME_OF_FLIGHT_AND_ULTRASONIC_SENSORS_DETECTION_MODE and ANALOG_OBSTACLE_DETECTION_AND_ULTRASONIC_SENSORS_DETECTION_MODE
// Before running the system, we select the desired obstacle detection mode.
int  obstacleDetectionMode = TIME_OF_FLIGHT_AND_ULTRASONIC_SENSORS_DETECTION_MODE;


// Obstacle detection flags for TIME_OF_FLIGHT_AND_ULTRASONIC_SENSORS_DETECTION_MODE
bool isCloseObstacleDetected = false;
bool isFarObstacleDetected = false;

// Obstacle detection flags for the ANALOG_OBSTACLE_DETECTION_AND_ULTRASONIC_SENSORS_DETECTION_MODE
bool didAnalogDistanceSensorOnlyDetectedObstacle= false;
bool didUltrasonicSensorOnlyDetectedObstacle = false;

//Global ultrasonic sensors classes
EZDist LeftUltraSonic(LEFT_ULTRA_SONIC_TRIGGER_PIN, LEFT_ULTRA_SONIC_ECHO_PIN);
EZDist RightUltraSonic(RIGHT_ULTRA_SONIC_TRIGGER_PIN, RIGHT_ULTRA_SONIC_ECHO_PIN);

//Global time-of-flight sensor class
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(TIME_OF_FLIGHT_XSHUT_PIN, TIME_OF_FLIGHT_IRQ_PIN);


/**
* Set up the obstacle detection module
*/
void setUpObstacleModule(){
  //Set up analog distance sensor pin
   pinMode(VMA330_IR_OBSTACLE_OUT_PIN, INPUT);

  // Set up time-of-flight distance sensor
  Serial.println(F("Adafruit VL53L1X sensor demo")); //Remove later

  Wire.begin();
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
* Returns true if the given distance is within the specified the range
*/
bool isDistanceInRange(int minDistance, int maxDistance, int givenDistance){  
  return givenDistance>minDistance && givenDistance<maxDistance;
}

/**
*  Update flags based on the obstacle detection inputs
*/
void checkObstacle(){  
    int leftDistanceInCm = LeftUltraSonic.cm(); // From the left ultrasonic sensor
    int rightDistanceInCm = RightUltraSonic.cm();// From the right ultrasonic sensor
    int centerDistanceInCm = vl53.distance() / 10 ;// From the time-of-flight sensor
    vl53.clearInterrupt(); //Clear the interrupt
    
    switch(obstacleDetectionMode){
      
       //Use the analog-distance detection if the time-of-flight and ultrasonic sonic  sensor is NOT working
      case (ANALOG_OBSTACLE_DETECTION_AND_ULTRASONIC_SENSORS_DETECTION_MODE ): 
            bool isAnalogDistanceSensorSet = digitalRead(VMA330_IR_OBSTACLE_OUT_PIN) == 0;
            didAnalogDistanceSensorOnlyDetectedObstacle =  isAnalogDistanceSensorSet && leftDistanceInCm> OBSTACLE_CLOSE_DISTANCE_TRIGGER && rightDistanceInCm> OBSTACLE_CLOSE_DISTANCE_TRIGGER;
           
            didUltrasonicSensorOnlyDetectedObstacle =  !isAnalogDistanceSensorSet && (isDistanceInRange(MIN_ACCEPTABLE_DISTANCE,OBSTACLE_CLOSE_DISTANCE_TRIGGER,leftDistanceInCm) || (isDistanceInRange(MIN_ACCEPTABLE_DISTANCE,OBSTACLE_CLOSE_DISTANCE_TRIGGER,rightDistanceInCm));

             // didUltrasonicSensorOnlyDetectedObstacle =  !isAnalogDistanceSensorSet && ((leftDistanceInCm>MIN_ACCEPTABLE_DISTANCE && leftDistanceInCm < OBSTACLE_CLOSE_DISTANCE_TRIGGER) || (rightDistanceInCm>MIN_ACCEPTABLE_DISTANCE && rightDistanceInCm < OBSTACLE_CLOSE_DISTANCE_TRIGGER));

      
      break;

      //Use the ultrasonic sensors and time-of-flight sensor
      case(TIME_OF_FLIGHT_AND_ULTRASONIC_SENSORS_DETECTION_MODE):
                    printf(" Left Distance: \r %d cm; Center Distance: \r %d cm; Right Distance: \r %d cm \n", leftDistanceInCm, centerDistanceInCm, rightDistanceInCm);

        // Check if the snowplow is close to an obstacle
        if( isDistanceInRange(MIN_ACCEPTABLE_DISTANCE,OBSTACLE_CLOSE_DISTANCE_TRIGGER,centerDistanceInCm)||
            isDistanceInRange(MIN_ACCEPTABLE_DISTANCE,OBSTACLE_CLOSE_DISTANCE_TRIGGER,leftDistanceInCm) ||
            isDistanceInRange(MIN_ACCEPTABLE_DISTANCE,OBSTACLE_CLOSE_DISTANCE_TRIGGER,rightDistanceInCm)
         ){
            // printf("CLOSE - Left Distance: \r %d cm; Center Distance: \r %d cm; Right Distance: \r %d cm \n", leftDistanceInCm, centerDistanceInCm, rightDistanceInCm);

           isCloseObstacleDetected = true;
           isFarObstacleDetected = false;
         }
        
         // Check if the snowplaw is far from an obstacle and the obstacle should be avoided
         else if (isDistanceInRange(OBSTACLE_CLOSE_DISTANCE_TRIGGER,OBSTACLE_FAR_DISTANCE_TRIGGER,centerDistanceInCm) ||
            isDistanceInRange(OBSTACLE_CLOSE_DISTANCE_TRIGGER,OBSTACLE_FAR_DISTANCE_TRIGGER,leftDistanceInCm) ||
            isDistanceInRange(OBSTACLE_CLOSE_DISTANCE_TRIGGER,OBSTACLE_FAR_DISTANCE_TRIGGER,rightDistanceInCm)
         ){
              //  printf("FAR - Left Distance: \r %d cm; Center Distance: \r %d cm; Right Distance: \r %d cm \n", leftDistanceInCm, centerDistanceInCm, rightDistanceInCm);

                isFarObstacleDetected = true;
                isCloseObstacleDetected = false;
         }else{
            isCloseObstacleDetected = false;
            isFarObstacleDetected = false;
         }
    

        // if(centerDistanceInCm>MIN_ACCEPTABLE_DISTANCE || leftDistanceInCm>MIN_ACCEPTABLE_DISTANCE || rightDistanceInCm > MIN_ACCEPTABLE_DISTANCE){
        //     printf("Left Distance: \r %d cm; Center Distance: \r %d cm; Right Distance: \r %d cm \n", leftDistanceInCm, centerDistanceInCm, rightDistanceInCm);

        //     if(centerDistanceInCm < OBSTACLE_CLOSE_DISTANCE_TRIGGER || leftDistanceInCm < OBSTACLE_CLOSE_DISTANCE_TRIGGER || rightDistanceInCm < OBSTACLE_CLOSE_DISTANCE_TRIGGER){
        //       isCloseObstacleDetected = true;
        //     }else{

        //       isCloseObstacleDetected = false;

        //       if(centerDistanceInCm < OBSTACLE_FAR_DISTANCE_TRIGGER || leftDistanceInCm < OBSTACLE_FAR_DISTANCE_TRIGGER ||  rightDistanceInCm < OBSTACLE_FAR_DISTANCE_TRIGGER){
        //         isFarObstacleDetected = true;
        //       }else{
        //                         isFarObstacleDetected = false;

        //       } 
        //      }
        //     }
          

      break;
    }

 }

