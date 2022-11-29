#ifndef MAIN_FILE_H    
#define MAIN_FILE_H   


  #ifdef __cplusplus
  extern "C"{
  #endif


    /********************START OF BOUNDARY MODULE SECTION********************/
      extern int currentState;

      #define NORMAL_STATE 0
      #define OBSTACLE_CLOSE_DETECTED_STATE 1
      #define OBSTACLE_FAR_DETECTED_STATE 2
     #define OBSTACLE_DETECTION_RESET_VEHICLE_POSISTION_STATE 3

     #define DETECTED_MINIMUM_BOUNDARY_ANALOG_VALUE 600


      #define BOUNDARY_DETECTED_STATE 4

    /********************END OF BOUNDARY MODULE SECTION********************/

    
    /********************START OF MOVEMENT MODULE SECTION********************/
      #define LEFT_SIDE_DIRECTION_PIN 50
      #define LEFT_SIDE_ENABLE_PIN A8
     
      #define RIGHT_SIDE_DIRECTION_PIN  49
      #define RIGHT_SIDE_ENABLE_PIN A9

      #define MAX_SPEED 140     

      void setupMovementModule(void);

      void turnLeft();
      void turnRight();

      void moveForward() ;
      void moveBackward();
    /********************END OF MOVEMENT MODULE SECTION********************/


    /********************START OF OBSTACLE MODULE SECTION********************/
      #define LEFT_ULTRA_SONIC_TRIGGER_PIN 12
      #define LEFT_ULTRA_SONIC_ECHO_PIN 11

      #define RIGHT_ULTRA_SONIC_TRIGGER_PIN 10
      #define RIGHT_ULTRA_SONIC_ECHO_PIN 9

      #define TIME_OF_FLIGHT_IRQ_PIN 2
      #define TIME_OF_FLIGHT_XSHUT_PIN 3

      #define VMA330_IR_OBSTACLE_OUT_PIN 4
      
      #define OBSTACLE_CLOSE_DISTANCE_TRIGGER 20
      #define OBSTACLE_FAR_DISTANCE_TRIGGER 40
      #define MIN_ACCEPTABLE_DISTANCE 3

      #define TIME_OF_FLIGHT_AND_ULTRASONIC_SENSORS_DETECTION_MODE 0
      #define ANALOG_OBSTACLE_DETECTION_AND_ULTRASONIC_SENSORS_DETECTION_MODE 1


      
      extern bool isCloseObstacleDetected;
      extern bool isFarObstacleDetected;
      extern bool didAnalogDistanceSensorOnlyDetectedObstacle;
      extern bool didUltrasonicSensorOnlyDetectedObstacle;

      void setUpObstacleModule(void);
      void checkObstacle(void);
    /********************END OF OBSTACLE MODULE SECTION********************/


    /********************START OF BOUNDARY MODULE SECTION********************/

    #define LEFT_LINE_DETECTION_OUT_PIN A2
    #define CENTER_LINE_DETECTION_OUT_PIN A3
    #define RIGHT_LINE_DETECTION_OUT_PIN A4
    
    
    extern bool isBoundaryDetected;

    void setupBoundaryModule(void);
    void checkBoundary(void);

    /********************END OF BOUNDARY MODULE SECTION********************/

    #ifdef __cplusplus
    } // extern "C"
    #endif

#endif