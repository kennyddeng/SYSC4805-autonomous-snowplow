/**
 * This module sets global flags that pertains to obstactle detection
 * 
*/
#include "Arduino.h"
#include "Adafruit_VL53L1X.h"
#include "main.h"

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(TIME_OF_FLIGHT_DISTANCE_SENSOR_IRQ_PIN, TIME_OF_FLIGHT_DISTANCE_SENSOR_XSHUT_PIN);

bool isObstacleDetected;

void setUpObstacleModule(){
    setUpObstacleAvoidanceSensor();
    setupTimeOfFlightDistanceSensor();

    startDetection();
}

void setUpObstacleAvoidanceSensor() {
    // set pin to input
    pinMode(OBSTACLE_AVOIDANCE_SENSOR_PIN, INPUT);
    // turn on pullup resistors
    digitalWrite(OBSTACLE_AVOIDANCE_SENSOR_PIN, HIGH);
}

void setUpTimeOfFlightDistanceSensor() {
    Serial.begin(115200);
    while (!Serial) delay(10);

    Serial.println(F("Adafruit VL53L1X sensor demo"));

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

    /*
    vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
    vl.VL53L1X_SetInterruptPolarity(0);
    */
}

bool checkForObstacle() {
    // detect for obstacles
        // if obstacle false
            // return false
        // else (obstacle exists)
            // return true

    // assume true, prove false
    bool obstacleState = true;


}

void loop() {
    if (isObstacleDetected == false) {
        // move forwards
        // constantly check range in front using tof
            // if range > 10 cm, good
            // else (range < 10cm OR out of range)
    } else { // obstacle in front of object
        // isObstacleDetected = true;
        // stop, turn 90 degrees (left or right)
        // need to ensure robot does not hit/contact obstacle while turning
        // detect for obstacles again
            // if no obstacles, loop (end of function)
            // isObstacleDetected = false;   
            // else there are obstacles
    }    
}

