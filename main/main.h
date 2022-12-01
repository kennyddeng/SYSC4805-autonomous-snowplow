#ifndef MAIN_FILE_H    
#define MAIN_FILE_H   
  
  /**
  * Watchdog setup
  * Required definition to enable to watchdog functionality
  */
  void watchdogSetup(){}

  #ifdef __cplusplus
  extern "C"{
  #endif

    /********************START OF MAIN CONTROLLER MODULE SECTION********************/
      extern int currentState; //The current state of the system

      #define NORMAL_STATE 0 // The normal state
      #define OBSTACLE_CLOSE_DETECTED_STATE 1 //The state indicating that an obstacle is close
      #define OBSTACLE_FAR_DETECTED_STATE 2 //The state indicating that an obstacle is within the close and far distance threshold
      #define BOUNDARY_DETECTED_STATE 3 //The state indicating that a boundary was detected 
    /********************END OF MAIN CONTROLLER MODULE SECTION********************/


    /********************START OF BOUNDARY MODULE SECTION********************/
      #define DETECTED_MINIMUM_BOUNDARY_ANALOG_VALUE 600
    /********************END OF BOUNDARY MODULE SECTION********************/

    
    /********************START OF MOVEMENT MODULE SECTION********************/
      #define LEFT_SIDE_DIRECTION_PIN 50 //The direction pin for the left side wheels
      #define LEFT_SIDE_ENABLE_PIN 5 //The enable pin for the left side wheel
     
      #define RIGHT_SIDE_DIRECTION_PIN  49//The direction pin for the right side wheels
      #define RIGHT_SIDE_ENABLE_PIN 6//The enable pin for the right side wheels

      #define NORMAL_MAX_SPEED 140//The speed when moving forward, backwards, left, and right

      #define RIGHT_SIDE_BACKWARDS_TURN_SPEED 100//The speed when turning and moving backwards for the right side wheels
      #define LEFT_SIDE_BACKWARDS_TURN_SPEED 250//The speed when turning and moving backwards for the left side wheels
  
      void setupMovementModule(void);// Sets up the movement module

      void turnLeft();//Turns the snowplow left
      void turnRight();//Turns the snowplow right

      void moveForward();//Moves the snowplow forward
      void moveBackward();//Moves the snowplow backwards
      void moveBackwardsAndTurnLeft();//Move the snowplow backwards while turning left
    /********************END OF MOVEMENT MODULE SECTION********************/


    /********************START OF OBSTACLE MODULE SECTION********************/
      #define LEFT_ULTRA_SONIC_TRIGGER_PIN 12//The trigger pin for the left ultrasonic sensor
      #define LEFT_ULTRA_SONIC_ECHO_PIN 11//The echo pin for the left ultrasonic sensor

      #define RIGHT_ULTRA_SONIC_TRIGGER_PIN 10//The trigger pin for the right ultrasonic sensor
      #define RIGHT_ULTRA_SONIC_ECHO_PIN 9//The echo pin for the right ultrasonic sensor

      #define TIME_OF_FLIGHT_IRQ_PIN 2//The IRQ pin for the time of flight sensor
      #define TIME_OF_FLIGHT_XSHUT_PIN 3 //The XSHUT pin for the time of flight sensor

      #define VMA330_IR_OBSTACLE_OUT_PIN 4//The output pin for the VMA330 analog distance sensor
      
      #define OBSTACLE_CLOSE_DISTANCE_TRIGGER 20//The close obstacle distance threshold
      #define OBSTACLE_FAR_DISTANCE_TRIGGER 40//The far obstacle  distance threshold
      #define MIN_ACCEPTABLE_DISTANCE 3 //The minimum distance reading accepted from the sensors to avoid noises
      
      extern bool isCloseObstacleDetected; //The system flag that indicates an obstacle is close
      extern bool isFarObstacleDetected; //The system flag that indicates an obstacle is within the close and far threshold and should be avoided

      void setUpObstacleModule(void); //This function setup obstacle module 
      void checkObstacle(void);//This function update the obstacle detection flags based on the system's postion relative to an obstacle 
    /********************END OF OBSTACLE MODULE SECTION********************/


    /********************START OF BOUNDARY MODULE SECTION********************/
    #define LEFT_LINE_DETECTION_OUT_PIN A2//The left line detection out pin
    #define CENTER_LINE_DETECTION_OUT_PIN A3//The center line detection out pin
    #define RIGHT_LINE_DETECTION_OUT_PIN A4//The right line detection out pin
    
    extern bool isBoundaryDetected;//The system flag that indicates that a boundary has been detected

    void setupBoundaryModule(void);//This function sets up the boundary module
    void checkBoundary(void);//This function update the boundary flag based on whether a boundary is detected
    /********************END OF BOUNDARY MODULE SECTION********************/

    #ifdef __cplusplus
    } // extern "C"
    #endif

#endif