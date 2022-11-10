#ifndef MAIN_FILE_H    
#define MAIN_FILE_H   

  #ifdef __cplusplus
  extern "C"{
  #endif

    /********************START OF MOVEMENT MODULE SECTION********************/
      #define LEFT_SIDE_DIRECTION_PIN 50
      #define RIGHT_SIDE_DIRECTION_PIN 48

      //#define PWM_FREQUENCY  1000.0
      
      extern void setupMovementModule(void);

      void turnLeft(float duty);
      void turnRight(float duty);

      void moveForward(float turnAngle) ;
      void moveBackward(float turnAngle);
      /********************END OF MOVEMENT MODULE SECTION********************/


      /********************START OF OBSTACLE MODULE SECTION********************/
      #define OBSTACLE_AVOIDANCE_SENSOR_PIN 0
      #define TIME_OF_FLIGHT_DISTANCE_SENSOR_IRQ_PIN 2
      #define TIME_OF_FLIGHT_DISTANCE_SENSOR_XSHUT_PIN 3
      
      extern bool isObstacleDetected;
      extern void setUpObstacleModule(void);
      extern void setUpObstacleAvoidanceSensor(void);
      extern void setUpTimeOfFlightSensor(void);
      extern bool checkForObstacle(void);
      extern void loop(void);
      /********************END OF OBSTACLE MODULE SECTION********************/


      /********************START OF BOUNDARY MODULE SECTION********************/
      extern void setupBoundaryModule(void);
      extern int isBoundaryDetected;
      /********************END OF BOUNDARY MODULE SECTION********************/


    #ifdef __cplusplus
    } // extern "C"
    #endif

#endif
